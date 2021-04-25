#ifndef DEALAREASTRING_H
#define DEALAREASTRING_H
//
//
//处理area(string)参数，将其转换成多边形
//
//
#include <opencv2/highgui.hpp>
#include <cstdlib>
#include <string>

using namespace std;
using namespace cv;

int CutString(vector<string>& cutted, string temp);

vector<Point2d>* DealAreaString(string area);

#endif // DEALAREASTRING_H
