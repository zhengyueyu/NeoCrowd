#include "BaseTracker.h"


BaseTracker::BaseTracker(QObject *parent) : QObject(parent)
{

}


#include "Tracker/CentroidTracker.h"

BaseTracker* CreateTracker(TrackerType tt)
{
    BaseTracker* tracker;
    switch(tt)
    {
    case TrackerType::Centroid:
        tracker = new CentroidTracker();
        break;
    }
    return tracker;
}
