#include "NeoCrowdLib.h"
#include <regex>
#include <qpixmap.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>


void RunRecongizeService(string inputPath, string areaString, string outputPath)
{
    if(access(inputPath.data(), F_OK) != 0)
    {
        cout << inputPath + " File Not Exist!" << endl;
        return;
    }
    if(access(outputPath.data(), F_OK) == 0)
    {
        std::remove(outputPath.data());
    }
    unique_ptr<NeoCrowdLib> ncl = make_unique<NeoCrowdLib>();
    ncl->ParseMedia(inputPath, areaString, outputPath);
}


NeoCrowdLib::NeoCrowdLib()
{
    detector = CreateDetector(detectorType);
    tracker = CreateTracker(trackerType);
    timer = new QTimer(this);
    image = new QImage();

    connect(timer,SIGNAL(timeout()),this,SLOT(dealFrame()));
}


NeoCrowdLib::~NeoCrowdLib()
{

}

void NeoCrowdLib::ParseMedia(string inputPath, string areaString, string outputPath)
{
    m_inputPath = inputPath;
    m_outputPath = outputPath;

    cap.open(inputPath);
    if(!cap.isOpened())
    {
        cout << "Open " + inputPath + "failed.";
        return;
    }
    cap.read(src_image);

    detector->Init(src_image);
    tracker->SetArea(get_contours(areaString));
    tracker->Init(src_image, std::move(detector));

    Size size = Size(cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT));
    m_videoWriter = make_unique<VideoWriter>(m_outputPath, CV_FOURCC('M', 'J', 'P', 'G'), cap.get(CV_CAP_PROP_FPS), size, true);

    timer->start(33);
}


void NeoCrowdLib::DealFrame()
{
    bool success = cap.read(src_image);
    if(!success)
    {
        cap.release();
        timer->stop();
        return;
    }

    Result result = tracker->Update(&src_image);
    m_videoWriter->write(result.image);
}


std::vector<std::vector<cv::Point>> NeoCrowdLib::get_contours(std::string str)
{
    if (str == "") return std::vector<std::vector<cv::Point>>();
    std::vector<cv::Point> points;
    std::regex ws_re(",");
    std::vector<std::string> v(std::sregex_token_iterator(str.begin(), str.end(), ws_re, -1), std::sregex_token_iterator());
    if (v.size() % 2 != 0) throw "Not a even number!";  // 非偶数
    if (v.size() < 6) throw "Cannot be a polygon!";  // 不构成多边形
    for (uint i = 0; i < v.size() / 2; ++i)
    {
        std::stringstream ss;
        ss << v.at(i * 2) << ' ' << v.at(i * 2 + 1);
        int x, y;
        ss >> x >> y;
        points.push_back(cv::Point(x, y));
    }
    std::vector<std::vector<cv::Point>> contours;
    contours.push_back(points);
    return contours;
}
