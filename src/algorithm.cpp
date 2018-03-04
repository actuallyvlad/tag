#include "algorithm.h"
#include "betterblobdetector.h"

RNG rng(12345);

const double PIX_TO_MM_RATIO = 0.1691;

/* Mat2QImage snippet is taken from
 * https://stackoverflow.com/a/17137998 (author: Marek R) */
QImage Mat2QImage(cv::Mat const& src)
{
     Mat temp;
     cvtColor(src, temp,CV_BGR2RGB);
     QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
     // enforce deep copy, see documentation
     // of QImage::QImage ( const uchar * data, int width, int height, Format format )
     dest.bits();
     return dest;
}

/* PrepareImage function is based on the answer from
 * http://answers.opencv.org/answers/56211/revisions/ (author: theodore) */
Mat PrepareImage(const Mat& in) {
    Mat blr;
    blur(in, blr, Size(4,4));

    Mat inv;
    subtract(Scalar::all(255), blr, inv);

    Mat erd;
    // Erode a bit
    Mat kernel = Mat::ones(3, 3, CV_8UC1);
    erode(inv, erd, kernel);
    // Noise removal
    // morphologyEx(bw, bw, MORPH_OPEN, kernel, Point(-1, -1), 2);

    // Perform the distance transform algorithm
    Mat dist;
    distanceTransform(erd, dist, CV_DIST_L2, 5);

    // Normalize the distance image for range = {0.0, 1.0}
    // so we can visualize and threshold it
    normalize(dist, dist, 0, 1., NORM_MINMAX);

    // Threshold to obtain the peaks
    threshold(dist, dist, .5, 1., CV_THRESH_BINARY);

    // Dilate a bit the dist image
    Mat kernel1 = Mat::ones(3, 3, CV_8UC1);
    dilate(dist, dist, kernel1, Point(-1, -1), 2);

    // Create the CV_8U version of the distance image
    // It is needed for findContours()
    Mat dist_8u;
    normalize(dist, dist, 0, 255, NORM_MINMAX, CV_8U);
    dist.convertTo(dist_8u, CV_8U);

    subtract(Scalar::all(255), dist_8u, dist_8u);

    return dist_8u;
}

QImage FindGrains(QString src, int& total, vector<double>& lengths, vector<double>& widths,
                  vector<double>& areas) {
    // Read image
    Mat im = imread(src.toStdString());

    Mat bw;
    cvtColor( im, bw, COLOR_BGR2GRAY );
    bw = bw > 208;
    threshold(bw, bw, 40, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

    // Setup SimpleBlobDetector parameters.
    SimpleBlobDetector::Params params;

    // Change thresholds
    params.minThreshold = 0;
    params.maxThreshold = 255;

    // Filter by Area.
    params.filterByArea = true;
    params.minArea = 120;
    params.maxArea = 420;

    // Filter by Circularity
    params.filterByCircularity = false;
    params.minCircularity = 0.3;

    // Filter by Convexity
    params.filterByConvexity = false;
    //params.minConvexity = 0.3;

    // Filter by Inertia
    params.filterByInertia = true;
    //params.minInertiaRatio = 0.2;
    params.maxInertiaRatio = 0.8;

    lengths.clear();
    widths.clear();
    areas.clear();
    total = 0;

    for(int i = 0; i < 20; ++i) {
        // Storage for blobs
        vector<KeyPoint> keypoints;

        // Set up detector with params
        Ptr<BetterBlobDetector> detector = BetterBlobDetector::create(params);

        // Detect blobs
        detector->detect( bw, keypoints );
        vector<vector<cv::Point> > contours = detector->getContours();

        for( uint i = 0; i < contours.size(); i++ )
        {
            Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
            // alternative - draw the fitting ellipse instead of a contour
            // ellipse( im, fitEllipse( Mat(contours[i]) ), color, 1, 8 );
            //
            // Draw a contour
            drawContours( im, contours, i, color, 1, 8, noArray(), 0, Point() );
            // Draw a contour index number
            putText(im, to_string(total + 1), cvPoint(keypoints[i].pt.x, keypoints[i].pt.y),
                FONT_ITALIC, 0.8, Scalar(0, 0, 255), 1, CV_AA);
            // Fit rectangle
            RotatedRect box = minAreaRect(Mat(contours[i]));
            if (box.size.width > box.size.height)
            {
                swap(box.size.width, box.size.height);
            }
            // Push back grain length
            lengths.push_back(box.size.height * PIX_TO_MM_RATIO);
            // Push back grain width
            widths.push_back(box.size.width * PIX_TO_MM_RATIO);
            // Push back grain area
            areas.push_back(contourArea(contours[i]) * PIX_TO_MM_RATIO * PIX_TO_MM_RATIO);

            drawContours( bw, contours, i, Scalar(255, 255, 255), CV_FILLED );

            total++;
        }

        bw = PrepareImage(bw);
    }

    return Mat2QImage(im);
}
