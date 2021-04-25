#ifndef MATTOQIMAGE_H
#define MATTOQIMAGE_H

#include <opencv2/opencv.hpp>
#include <QImage>

using namespace cv;

QImage MatImageToQt(const Mat &src);


#endif // MATTOQIMAGE_H
