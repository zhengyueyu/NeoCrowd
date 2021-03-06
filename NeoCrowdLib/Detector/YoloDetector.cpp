#include "YoloDetector.h"

YoloDetector::YoloDetector()
{
    detectorType = DetectorType::YOLO;
}

void YoloDetector::Init(cv::Mat &firstFrame)
{
    const string modelpath = "../../model/yolov3.weights";
    const string cfgpath = "../../model/yolov3.cfg";
    net = cv::dnn::readNet(modelpath, cfgpath);
}

std::vector<Rect> YoloDetector::Update(cv::Mat* frame)
{
    Mat img;
    resize(*frame, img, cv::Size(m_dim, m_dim));
    cv::Mat blob = cv::dnn::blobFromImage(img, 1.0, cv::Size(m_dim, m_dim), cv::Scalar(), true, false, CV_8U);
    net.setInput(blob, "", scalefactor, cv::Scalar());
    cv::Mat imInfo = (cv::Mat_<float>(1, 3) << m_dim, m_dim, 1.6f);
    net.setInput(imInfo, "im_info");

    std::vector<Rect> areas;
    std::vector<cv::Mat> outs;
    net.forward(outs, net.getUnconnectedOutLayersNames());

    for (size_t i = 0; i < outs.size(); ++i)
    {
        // Network produces output blob with a shape NxC where N is a number of
        // detected objects and C is a number of classes + 4 where the first 4
        // numbers are [center_x, center_y, width, height]
        float* data = (float*)outs[i].data;
        for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols)
        {
            cv::Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
            cv::Point classIdPoint;
            double confidence;
            cv::minMaxLoc(scores, nullptr, &confidence, nullptr, &classIdPoint);
            if (classIdPoint.x == person_idx && confidence > confidenceThreshold)
            {
                int centerX = (int)(data[0] * frame->cols);
                int centerY = (int)(data[1] * frame->rows);
                int width = (int)(data[2] * frame->cols);
                int height = (int)(data[3] * frame->rows);
                int xLeftBottom = centerX - width / 2;
                int yLeftBottom = centerY - height / 2;

                areas.push_back(Rect(xLeftBottom, yLeftBottom, width, height));
            }
        }
    }
    return areas;
}
