#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <opencv2/opencv.hpp>
#include <QImage>
#include <vector>

using namespace std;
using namespace cv;

QImage Mat2QImage(cv::Mat const& src);
QImage FindGrains(QString src, int& total, vector<double>& lengths, vector<double>& widths,
                  vector<double>& areas);

#endif // ALGORITHM_H
