#ifndef YOLODETECTOR_H
#define YOLODETECTOR_H

#include "BaseDetector.h"

using namespace std;
using namespace cv;

class YoloDetector : public BaseDetector
{
public:
    YoloDetector();
    void Init(cv::Mat &firstFrame) override;
    std::vector<cv::Rect> Update(cv::Mat* frame) override;
    
private:
    cv::dnn::Net net;
    const int m_dim = 608;
    const float scalefactor = 1.0f;
    const int person_idx = 0;
    const float confidenceThreshold = 0.6;
};
#endif // YOLODETECTOR_H
