#ifndef CENTROIDTRACKER_H
#define CENTROIDTRACKER_H

#include <opencv2/tracking.hpp>
#include <vector>
#include <math.h>
#include <map>
#include <QTime>
#include "Detector/SSDMobileNetDetector.h"
#include "BaseTracker.h"
#include "Common/MatToQImage.h"

using namespace std;
using namespace cv;

typedef struct
{
    int disapperTime = 0;    //消失的帧数
    Point oldCentroid;     //每个tracker旧的质心位置
    Rect2d newestRect;
    Ptr<Tracker> tracker;
    unsigned int id;
    bool isReid = false;
}SingleTracker;

class CentroidTracker : public BaseTracker
{
    Q_OBJECT

public:
    CentroidTracker();
    ~CentroidTracker();

    void Init(cv::Mat frame, unique_ptr<BaseDetector> detector) override;
    Result Update(cv::Mat* frame) override;

    void Add(Mat img, Rect boxes);
    void AddExcludeExist(Mat img, Rect boxes);
    void AddExcludeExist(Mat img, vector<Rect> boxes);

public slots:
    bool UpdateID(int stamp, int id);



private:
    const int maxDistance = 25;
    const int maxDisapperTime = 10;

    int in = 0;
    int out = 0;

    unsigned long frame_num = 0;

    cv::Mat src_img;   //copy the mat from update func

    unique_ptr<BaseDetector> _detector = nullptr;

    Person_Count pc;

    vector<SingleTracker> multitracker;
    map<unsigned, SingleTracker*> stamp_tracker_map;

    Point GetCentroid(Rect rect);
    int GetDistancePow2(Point2d a, Point2d b);
    Result GetResult(cv::Mat draw_img);
    bool IsSamePerson(vector<SingleTracker>::iterator it, cv::Rect* rect);
    bool HasSamePerson(cv::Rect rect);
    double IsOverLap(Rect2d r1, Rect2d r2);
    vector<Ptr<Tracker>>::iterator DelTracker(vector<Ptr<Tracker>>::iterator it);
};

#endif // CENTROIDTRACKER_H
