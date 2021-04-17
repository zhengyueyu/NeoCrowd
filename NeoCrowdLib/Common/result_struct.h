#ifndef RESULT_H
#define RESULT_H

#include <vector>
#include <opencv2/highgui.hpp>

enum DetectorType
{
    YOLO,
    SSDMobileNet,
    Vibe
};

enum TrackerType
{
    Centroid
};

typedef struct
{
    //每个人的ID
    int id = 0;

    //跟踪到的人体框位置
    float left = 0;
    float top = 0;
    float width = 0;
    float height = 0;

}Person_Info;

typedef struct
{
    unsigned int in = 0;
    unsigned int out = 0;
}Person_Count;

typedef struct
{
    //检测到的人体框数目
    unsigned int person_num = 0;

    //每个框的具体信息
    std::vector<Person_Info> person_infos;

    //进出区域的人流统计
    Person_Count person_count;

    //渲染后的图片，输入参数show=true时输出该字段
    cv::Mat image;

}Result;

#endif // RESULT_H
