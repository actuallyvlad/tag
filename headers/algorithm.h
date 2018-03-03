#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <opencv2/opencv.hpp>
#include <QImage>

using namespace cv;

QImage Mat2QImage(cv::Mat const& src);
QImage FindGrains(QString src);


#endif // ALGORITHM_H
