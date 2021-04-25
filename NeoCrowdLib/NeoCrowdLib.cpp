#include "NeoCrowdLib.h"
#include <regex>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>


void RunRecongizeService(const char* _inputPath, const char* _areaString, const char* _outputPath)
{
    string inputPath(_inputPath);
    string outputPath(_outputPath);
    string areaString(_areaString);
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
    cout << "finish"<<endl;
}


NeoCrowdLib::NeoCrowdLib()
{
    detector = CreateDetector(detectorType);
    tracker = CreateTracker(trackerType);
}


NeoCrowdLib::~NeoCrowdLib()
{

}

void NeoCrowdLib::ParseMedia(string inputPath, string areaString, string outputPath)
{
    m_inputPath = inputPath;
    m_outputPath = outputPath;
    cout << "Input path :" + inputPath << endl;
    cout << "outputPath :" + outputPath << endl;

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

    int ex = static_cast<int>(cap.get(CV_CAP_PROP_FOURCC));
    char EXT[] = {(char)(ex & 0XFF) , (char)((ex & 0XFF00) >> 8),(char)((ex & 0XFF0000) >> 16),(char)((ex & 0XFF000000) >> 24), 0};
    cout << "Input codec type: " << EXT << endl;

    cv::Size size = cv::Size(384, 288);
    m_videoWriter = make_unique<cv::VideoWriter>(m_outputPath, ex, cap.get(CV_CAP_PROP_FPS), size, true);

    DealFrame();
}


void NeoCrowdLib::DealFrame()
{
    while(cap.read(src_image))
    {
        Result result = tracker->Update(&src_image);
        m_videoWriter->write(result.image);
    }
    cap.release();
    m_videoWriter->release();
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
