#define TIMES_OF_REDETECT 5
#include "CentroidTracker.h"

CentroidTracker::CentroidTracker() : BaseTracker()
{
}

CentroidTracker::~CentroidTracker()
{
    for(unsigned i = 0; i < multitracker.size(); i++)
    {
        multitracker[i].tracker.release();
    }
}

void CentroidTracker::Init(cv::Mat frame, unique_ptr<BaseDetector> detector)
{
    _detector = move(detector);
    frame_num = 0;
}

void CentroidTracker::Add(Mat img, Rect box)
{
    Ptr<Tracker> t = TrackerKCF::create();
    t->init(img, box);
    SingleTracker st;
    st.tracker = t;
    st.newestRect = box;
    st.oldCentroid = Point2d(-1, -1);
    multitracker.push_back(st);
}

bool CentroidTracker::HasSamePerson(Rect rect)
{
    bool exist = false;
    for(auto t = multitracker.begin(); t != multitracker.end(); t++)
    {
        if(IsSamePerson(t, &rect))
        {
            exist = true;
            break;
        }
    }
    return exist;
}

int CentroidTracker::GetDistancePow2(Point2d a, Point2d b)
{
    return pow((a.x - b.x), 2) + pow((a.y - b.y), 2);
}

Result CentroidTracker::Update(Mat* img)
{
    cout << "frame " << ++frame_num << "===============================" << endl;
    src_img = *img;


    //Update the multitracker
    for (auto tracker_it = multitracker.begin(); tracker_it != multitracker.end(); tracker_it++)
    {
        Rect2d r;
        bool ok = tracker_it->tracker->update(src_img, r);
        if(ok)
        {
            tracker_it->newestRect = r;
            tracker_it->disapperTime = 0;
        }
        else
        {   cout << " failure" << endl;
            tracker_it->disapperTime++;
        }
    }



    vector<Rect> boxes;
    boxes = _detector->Update(&src_img);
    //detect if someone appears per TIMES_OF_REDETECT
    if (!(frame_num % TIMES_OF_REDETECT))
    {
        if (boxes.size() != 0)
            AddExcludeExist(src_img, boxes);
    }


    Mat draw_img = src_img;
    int num = 0;
    Result result;
    in = 0;
    out = 0;
    for (auto tracker = multitracker.begin(); tracker != multitracker.end();)
    {
        num++;

        //消失过久
        if (tracker->disapperTime >= maxDisapperTime)
        {
            tracker = multitracker.erase(tracker);
            if(tracker == multitracker.end())
                break;
        }


        Point newCentroid = GetCentroid(tracker->newestRect);
        //判断是否出画面
        if (newCentroid.x <= 0 || newCentroid.y <= 0 || newCentroid.x > (src_img.cols) || newCentroid.y > (src_img.rows))
        {
            tracker->tracker->clear();
            tracker = multitracker.erase(tracker);
            if(tracker == multitracker.end())
                break;
        }

        if (_detector->GetDetectorType() == DetectorType::Vibe && !(frame_num % TIMES_OF_REDETECT))
        {
            bool isExist = false;
            for(unsigned i = 0; i < boxes.size(); i++)
            {
                if(IsSamePerson(tracker, &boxes[i]))
                {
                    isExist = true;
                    break;
                }
            }
            if (!isExist)
            {
                tracker->tracker->clear();
                tracker = multitracker.erase(tracker);
                if(tracker == multitracker.end())
                    break;
            }
        }

        //计算进出人数
        if (tracker->oldCentroid.x != -1 && tracker->oldCentroid.y != -1)
        {
            if (pointPolygonTest(m_area[0], tracker->oldCentroid, true) > 0 && pointPolygonTest(m_area[0], newCentroid, true) <= 0)
            {
                ++out;
            }
            else if (pointPolygonTest(m_area[0], tracker->oldCentroid, true) < 0 && pointPolygonTest(m_area[0], newCentroid, true) >= 0)
            {
                ++in;
            }
        }


        //画矩形
        rectangle(draw_img, tracker->newestRect, Scalar(0, 225, 0), 2, 0);
        string label = format("id:%d (%.2f, %.2f)", tracker->id, tracker->newestRect.x, tracker->newestRect.y);
        putText(draw_img, label, Point(tracker->newestRect.x, tracker->newestRect.y - 4), FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 0), 1.5);

        //置换新状态
        tracker->oldCentroid = newCentroid;

        tracker++;
    }
    return GetResult(draw_img);
}


bool CentroidTracker::UpdateID(int stamp, int m_id)
{
    map<unsigned, SingleTracker*>::iterator it = stamp_tracker_map.find(stamp);
    if(it == stamp_tracker_map.end() || it->second->isReid)
        return false;
    it->second->id = m_id;
    it->second->isReid = true;
    return true;
}


Result CentroidTracker::GetResult(Mat draw_img)
{
    Result result;
    for(vector<SingleTracker>::iterator it = multitracker.begin(); it != multitracker.end(); it++)
    {
        Person_Info pi;
        pi.id = it->id;
        pi.left = it->newestRect.x;
        pi.top = it->newestRect.y;
        pi.width = it->newestRect.width;
        pi.height = it->newestRect.height;
        result.person_infos.push_back(pi);
    }

    result.image = draw_img;
    if (m_area.size() > 0) {
        cv::drawContours(result.image, m_area, 0, cv::Scalar(255, 255, 0), 2, cv::LINE_AA);
    }
    result.person_num = multitracker.size();
    result.person_count.in = in;
    result.person_count.out = out;
    return result;
}

Point CentroidTracker::GetCentroid(Rect rect)
{
    double tempx = rect.x + (rect.width / 2);
    double tempy = rect.y + (rect.height / 2);
    return Point(tempx, tempy);
}

void CentroidTracker::AddExcludeExist(Mat src_img, Rect box)
{
    if (HasSamePerson(box))
        return;
    Add(src_img, box);
}

void CentroidTracker::AddExcludeExist(Mat img, vector<Rect> boxes)
{
    for(unsigned i = 0; i < boxes.size(); i++)
    {
        AddExcludeExist(img, boxes[i]);
    }
}

double CentroidTracker::IsOverLap(Rect2d r1, Rect2d r2)
{
    double startx = min(r1.x, r2.x);
    double endx = max(r1.x + r1.width, r2.x + r2.width);
    double starty = min(r1.y, r2.y);
    double endy = max(r1.y + r1.height, r2.y + r2.height);

    double overlapWidth = r1.width + r2.width - (endx - startx);
    double overlapHeight = r1.height + r2.width - (endy - starty);
    float overlapPercent = 0;
    if(overlapWidth > 0 && overlapHeight > 0)
    {
        double overlapArea = overlapWidth * overlapHeight;
        overlapPercent = overlapArea / min(r1.area(), r2.area());
        std::cout << "OverlapPercent:" << overlapPercent << std::endl;
        std::cout << "GetOverLapArea:\n  r1.area:" << r1.area() << "  r2.area:" << r2.area() << "  Overlap:" << overlapArea <<std::endl;
    }

    return overlapPercent > 0.4;
}

bool CentroidTracker::IsSamePerson(vector<SingleTracker>::iterator it, cv::Rect* rect)
{
    Point2d newCentroid = GetCentroid(*rect);
    Rect existRect = (*it).newestRect;
    Point2d oldCentroid = GetCentroid(existRect);
    int distancePow2 = pow((newCentroid.x - oldCentroid.x), 2) + pow((newCentroid.y - oldCentroid.y), 2);
    if (distancePow2 < pow(maxDistance, 2) && IsOverLap(existRect, *rect))
        return true;
    return false;
}
