#ifndef BASETRACKER_H
#define BASETRACKER_H

#include <vector>
#include <QObject>
#include <opencv2/highgui.hpp>
#include <memory>
#include "Common/result_struct.h"
#include "Detector/BaseDetector.h"

class BaseTracker : public QObject
{
    Q_OBJECT

public:

    explicit BaseTracker(QObject *parent = nullptr);

    virtual void Init(cv::Mat frame, std::unique_ptr<BaseDetector> detector) = 0;

    virtual Result Update(cv::Mat* frame) = 0;

    void SetArea(std::vector<std::vector<cv::Point>> area)
    {
        m_area = area;
    }

protected:
    std::vector<std::vector<cv::Point>> m_area;
};

std::unique_ptr<BaseTracker> CreateTracker(TrackerType);

#endif // BASETRACKER_H
