#ifndef NEOCROWDLIB_H
#define NEOCROWDLIB_H

#include "Detector/BaseDetector.h"
#include "Tracker/BaseTracker.h"
#include "NeoCrowdLib_global.h"
#include <QTimer>
#include <QString>
#include <opencv2/opencv.hpp>


using namespace std;

class NEOCROWDLIB_EXPORT NeoCrowdLib : public QObject
{
    Q_OBJECT

public:
    NeoCrowdLib();
    ~NeoCrowdLib();
    void ParseMedia(string inputPath, string areaString, string outputPath);

private:
    unique_ptr<BaseDetector> detector;
    unique_ptr<BaseTracker> tracker;
    DetectorType detectorType = DetectorType::Vibe;
    TrackerType trackerType = TrackerType::Centroid;
    cv::VideoCapture cap;
    unique_ptr<cv::VideoWriter> m_videoWriter;
    cv::Mat src_image;
    std::string m_inputPath;
    std::string m_outputPath;

private:
    bool useReid = false;

private:
    std::vector<std::vector<cv::Point>> get_contours(std::string str);
    void DealFrame();
};



#ifdef __cplusplus
extern "C" {
#endif

    NEOCROWDLIB_EXPORT void RunRecongizeService(const char* _inputPath, const char* _areaString, const char* _outputPath);

#ifdef __cplusplus
}
#endif

#endif // NEOCROWDLIB_H
