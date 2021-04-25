#ifndef BASETRACKER_H
#define BASETRACKER_H

#include <vector>
#include <QObject>
#include <opencv2/highgui.hpp>
#include <memory>
#include "result_struct.h"
#include "BaseDetector.h"
#include "NetworkReid.h"

class BaseTracker : public QObject
{
    Q_OBJECT

public:

    //explicit用于禁止“　BaseTracker a = 某个QObject的派生类　　而自动执行隐式转换”
    explicit BaseTracker(QObject *parent = nullptr);

    virtual void Init(cv::Mat frame, std::unique_ptr<BaseDetector> detector, NetworkReid* reid = nullptr) = 0;

    virtual Result Update(cv::Mat* frame) = 0;

    void SetArea(std::vector<std::vector<cv::Point>> area)
    {
        m_area = area;
    }

protected:
    std::vector<std::vector<cv::Point>> m_area;
};

BaseTracker* CreateTracker(TrackerType);

#endif // BASETRACKER_H
