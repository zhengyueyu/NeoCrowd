#include "BaseTracker.h"


BaseTracker::BaseTracker(QObject *parent) : QObject(parent)
{

}


#include "Tracker/CentroidTracker.h"

unique_ptr<BaseTracker> CreateTracker(TrackerType tt)
{
    unique_ptr<BaseTracker> tracker;
    switch(tt)
    {
    case TrackerType::Centroid:
        tracker = make_unique<CentroidTracker>();
        break;
    }
    return tracker;
}
