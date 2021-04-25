#include "BackgroundSubtract.h"

BackgroundSubtract::BackgroundSubtract() : BaseDetector()
{
    detectorType = DetectorType::Vibe;
}

void BackgroundSubtract::Init(cv::Mat &firstFrame)
{
    minObjectSize.width = std::max(20, firstFrame.cols / 100);
    minObjectSize.height = minObjectSize.width;

    Mat img;
    cvtColor(firstFrame, img, CV_BGR2GRAY);

    int channel = 1;
    std::vector<int> params = { 20, 1, 20, 3, 16 };
    model = vibe::VIBE(channel, params[0], params[1], params[2], params[3], params[4]);
    model.init(img);
}

std::vector<cv::Rect> BackgroundSubtract::Update(cv::Mat* frame)
{
    Mat foreground;
    Mat newImg;
    cvtColor(*frame, newImg, CV_BGR2GRAY);
    model.update(newImg);
    foreground = model.getMask();

    //模糊处理
    medianBlur(foreground, foreground, 3);
    Mat dilateElement = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), cv::Point(-1, -1));
    dilate(foreground, foreground, dilateElement, cv::Point(-1, -1), 2);

    std::vector<Rect> boxes;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(foreground, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point());
    for (size_t i = 0; i < contours.size(); i++)
    {
        cv::Rect br = cv::boundingRect(contours[i]);
        if (br.width >= minObjectSize.width &&
                br.height >= minObjectSize.height)
        {
            boxes.push_back(br);
        }
    }
    return boxes;
}
