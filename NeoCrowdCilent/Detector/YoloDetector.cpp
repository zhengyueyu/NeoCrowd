#include "YoloDetector.h"

YoloDetector::YoloDetector()
{
    detectorType = DetectorType::YOLO;
}

void YoloDetector::Init(cv::Mat &firstFrame)
{
    const string modelpath = "../../model/yolov3/yolov3.weights";
    const string cfgpath = "../../model/yolov3/yolov3.cfg";
    net = cv::dnn::readNet(modelpath, cfgpath);
}

std::vector<Rect> YoloDetector::Update(cv::Mat* frame)
{
    Mat img;
    resize(*frame, img, cv::Size(m_dim, m_dim));
    //    cv::Mat blob = cv::dnn::blobFromImage(img, 1.0, cv::Size(m_dim, m_dim), cv::Scalar(), true, false, CV_8U);
    //    net.setInput(blob, "", scalefactor, cv::Scalar());


    //    cv::Mat imInfo = (cv::Mat_<float>(1, 3) << m_dim, m_dim, 1.6f);
    //    net.setInput(imInfo, "data");

    std::vector<Rect> areas;
    //    std::vector<cv::Mat> outs;
    //    net.forward(outs, net.getUnconnectedOutLayersNames());

    //    for (size_t i = 0; i < outs.size(); ++i)
    //    {
    //        // Network produces output blob with a shape NxC where N is a number of
    //        // detected objects and C is a number of classes + 4 where the first 4
    //        // numbers are [center_x, center_y, width, height]
    //        float* data = (float*)outs[i].data;
    //        for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols)
    //        {
    //            cv::Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
    //            cv::Point classIdPoint;
    //            double confidence;
    //            cv::minMaxLoc(scores, nullptr, &confidence, nullptr, &classIdPoint);
    //            if (classIdPoint.x == person_idx && confidence > confidenceThreshold)
    //            {
    //                int centerX = (int)(data[0] * frame->cols);
    //                int centerY = (int)(data[1] * frame->rows);
    //                int width = (int)(data[2] * frame->cols);
    //                int height = (int)(data[3] * frame->rows);
    //                int xLeftBottom = centerX - width / 2;
    //                int yLeftBottom = centerY - height / 2;

    //                areas.push_back(Rect(xLeftBottom, yLeftBottom, width, height));
    //            }
    //        }
    //    }


    cv::Mat blob = cv::dnn::blobFromImage(img, scalefactor, cv::Size(m_dim, m_dim), cv::Scalar(104, 117, 123), true);
    net.setInput(blob, "data");
    cv::Mat detections = net.forward("detection_out");
    cv::Mat detectionMat(detections.size[2], detections.size[3], CV_32F, detections.ptr<float>());
    for (int i = 0; i < detectionMat.rows; i++)
    {
        float confidence = detectionMat.at<float>(i, 2);
        int idx = static_cast<int>(detectionMat.at<float>(i, 1));
        if (confidence > confidenceThreshold&& idx == person_idx)
        {
            int xLeftBottom = static_cast<int>(detectionMat.at<float>(i, 3) * static_cast<float>(img.cols));
            int yLeftBottom = static_cast<int>(detectionMat.at<float>(i, 4) * static_cast<float>(img.rows));
            int xRightTop = static_cast<int>(detectionMat.at<float>(i, 5) * static_cast<float>(img.cols));
            int yRightTop = static_cast<int>(detectionMat.at<float>(i, 6) * static_cast<float>(img.rows));
            areas.emplace_back(xLeftBottom, yLeftBottom, xRightTop - xLeftBottom, yRightTop - yLeftBottom);
        }
    }
    return areas;
}
