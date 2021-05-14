#include "SSDMobileNetDetector.h"

SSDMobileNetDetector::SSDMobileNetDetector() : BaseDetector()
{
    detectorType = DetectorType::SSDMobileNet;
}

void SSDMobileNetDetector::Init(cv::Mat &firstFrame)
{
    const String modelTxt = "../../model/MobileNetSSD/MobileNetSSD_deploy.prototxt.txt";
    const String modelBin = "../../model/MobileNetSSD/MobileNetSSD_deploy.caffemodel";

    net = dnn::readNetFromCaffe(modelTxt, modelBin);
    if (net.empty())
    {
        std::cerr << "SSDMobileNetDetector: Can't load network by using the following files: " << std::endl;
        exit(-1);
    }
}

vector<Rect> SSDMobileNetDetector::Update(cv::Mat* img)
{
    //CV_TRACE_FUNCTION();

    if (img->empty())
    {
        std::cerr << "Picture detect: Can't read image." << std::endl;
        exit(-1);
    }

    Mat img2;
    resize(*img, img2, Size(300, 300));
    Mat inputBlob = blobFromImage(img2, 0.007843, Size(300, 300), Scalar(127.5, 127.5, 127.5), true);

    net.setInput(inputBlob, "data");
    Mat detection = net.forward("detection_out");
    Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());

    vector<Rect> boxes;
    float confidenceThreshold = 0.6;
    for (int i = 0; i < detectionMat.rows; i++)
    {
        float confidence = detectionMat.at<float>(i, 2);
        int idx = static_cast<int>(detectionMat.at<float>(i, 1));
        if ((confidence > confidenceThreshold) && idx == 15)
        {
            int xLeftBottom = static_cast<int>(detectionMat.at<float>(i, 3) * img->cols);
            int yLeftBottom = static_cast<int>(detectionMat.at<float>(i, 4) * img->rows);
            int xRightTop = static_cast<int>(detectionMat.at<float>(i, 5) * img->cols);
            int yRightTop = static_cast<int>(detectionMat.at<float>(i, 6) * img->rows);

            boxes.push_back(Rect((int)xLeftBottom, (int)yLeftBottom,
                (int)(xRightTop - xLeftBottom),
                (int)(yRightTop - yLeftBottom)));

            Rect r = boxes.back();
            cout << "(" << r.x << " " << r.y << " " << r.width << " " << r.height << ")  ";
            cout << CLASSES[idx] << ": " << confidence << endl;
        }
    }
    return boxes;
}
