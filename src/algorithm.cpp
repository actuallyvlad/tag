#include "algorithm.h"
#include <vector>

using namespace std;

QImage Mat2QImage(cv::Mat const& src)
{
     Mat temp; // make the same cv::Mat
     cvtColor(src, temp,CV_BGR2RGB); // cvtColor Makes a copt, that what i need
     QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
     dest.bits(); // enforce deep copy, see documentation
     // of QImage::QImage ( const uchar * data, int width, int height, Format format )
     return dest;
}

QImage FindGrains(QString src) {
    Point maxLoc;

    Mat im = imread(src.toStdString());
    Mat hsv;
    Mat channels[3];

    // bgr -> hsv
    cvtColor(im, hsv, CV_BGR2HSV);
    split(hsv, channels);

    // use v channel for processing
    Mat& ch = channels[1];

    // apply Otsu thresholding
    Mat bw;
    threshold(ch, bw, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

    // close small gaps
    Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(2, 2));
    Mat morph;
    morphologyEx(bw, morph, CV_MOP_CLOSE, kernel);

    // find connected components. we'll use each component as a mask for distance transformed image,
    // then extract the peak location and its strength. strength corresponds to the radius of the circle
    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    int thresh = 50;

    // Detect edges using canny
    Canny( morph, canny_output, thresh, thresh*2, 3 );

    findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    //Scalar colorRed = Scalar( 0, 0, 255 );
    //Scalar colorBlack = Scalar( 0, 0, 0 );
    Mat wh = morph.clone();
    wh.setTo(cv::Scalar(255,255,255));

    vector<Moments> mu(contours.size() );
    for (uint i = 0; i < contours.size(); ++i) {
        mu[i] = moments( contours[i], false );
        if (mu[i].m00 == 0.0) {
            continue;
        }
        //int x = int(mu[i].m10 / mu[i].m00);
        //int y = int(mu[i].m01 / mu[i].m00);

        drawContours(im, contours, i, Scalar(0, 0, 255), 1);
        //circle(im, Point(x, y), 1, Scalar(0, 255, 0), -1);
    }

    return Mat2QImage(im);
}
