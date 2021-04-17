#ifndef BACKGROUNDSUBTRACT_H
#define BACKGROUNDSUBTRACT_H

#include "BaseDetector.h"
#include "vibe/vibe.hpp"

using namespace cv;

class BackgroundSubtract : public BaseDetector
{
public:
    BackgroundSubtract();
    void Init(cv::Mat &firstFrame) override;
    std::vector<cv::Rect> Update(cv::Mat* frame) override;

private:
    vibe::VIBE model;
    cv::Size minObjectSize;

};

#endif // BACKGROUNDSUBTRACT_H
