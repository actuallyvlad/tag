#ifndef BETTERBLOBDETECTOR_H
#define BETTERBLOBDETECTOR_H

#include <opencv2/opencv.hpp>
#include <vector>

/* This code is a modification of an improved SimpleBlobDetector,
 * which can be found in the link below:
 * https://stackoverflow.com/a/25152785
 *
 * The author of the original modification is Joel Teply */
class BetterBlobDetector : public cv::SimpleBlobDetector
{
public:

    BetterBlobDetector(const cv::SimpleBlobDetector::Params &parameters = cv::SimpleBlobDetector::Params());
    static cv::Ptr<BetterBlobDetector> create(const SimpleBlobDetector::Params& params= cv::SimpleBlobDetector::Params());
    const std::vector < std::vector<cv::Point> > getContours();
    virtual void detect( const cv::Mat& image, std::vector<cv::KeyPoint>& keypoints, const cv::Mat& mask=cv::Mat()) const;
protected:
    struct CV_EXPORTS Center
      {
          cv::Point2d location;
          double radius;
          double confidence;
    };

    Params params;
    virtual void findBlobs(const cv::Mat &image, const cv::Mat &binaryImage,
                           std::vector<Center> &centers, std::vector < std::vector<cv::Point> >&contours) const;

};

#endif // BETTERBLOBDETECTOR_H
