#ifndef PEOPLEDETECTALGORITHM_H
#define PEOPLEDETECTALGORITHM_H


#include <fstream>
#include <iostream>
#include <cstdlib>
#include "BaseDetector.h"
#include <opencv2/core/utils/trace.hpp>

using namespace cv;
using namespace cv::dnn;
using namespace std;

class SSDMobileNetDetector : public BaseDetector
{
public:
    SSDMobileNetDetector();
    void Init(cv::Mat& firstFrame) override;
    std::vector<cv::Rect> Update(cv::Mat* frame) override;

private:
    string CLASSES[21] = { "background", "aeroplane", "bicycle", "bird", "boat",
                             "bottle", "bus", "car", "cat", "chair", "cow", "diningtable",
                             "dog", "horse", "motorbike", "person", "pottedplant", "sheep",
                             "sofa", "train", "tvmonitor" };
    Net net;
};

std::vector<Rect> PeopleDetectAlgorithm(Mat img);

#endif // PEOPLEDETECTALGORITHM_H
