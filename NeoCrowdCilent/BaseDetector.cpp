#include "BaseDetector.h"
#include "Detector/BackgroundSubtract.h"
#include "Detector/SSDMobileNetDetector.h"
#include "Detector/YoloDetector.h"

BaseDetector::BaseDetector()
{

}

unique_ptr<BaseDetector> CreateDetector(DetectorType dt)
{
    unique_ptr<BaseDetector> detector;
    switch (dt) {
    case DetectorType::Vibe:
        detector = unique_ptr<BaseDetector>(new BackgroundSubtract());
        break;
    case DetectorType::YOLO:
        detector = unique_ptr<BaseDetector>(new YoloDetector());
        break;
    case DetectorType::SSDMobileNet:
        detector = unique_ptr<BaseDetector>(new SSDMobileNetDetector());
        break;
    }
    return detector;
}
