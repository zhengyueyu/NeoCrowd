#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QFileDialog>
#include "MatToQImage.h"
#include "Detector/SSDMobileNetDetector.h"
#include "Tracker/CentroidTracker.h"
#include "DealAreaString.h"
#include "NetworkReid.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace cv;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void Init();

    void dealFrame();

    void on_open_triggered();

    void on_close_triggered();

    void on_select_triggered();

    void on_actionSSDMobileNet_triggered();

    void on_actionYolov3_triggered();

    void on_actionVbe_triggered();

    void on_actionCentroid_Tracker_triggered();

    void on_actionReid_toggled(bool arg1);

private:
    QString file;
    Ui::MainWindow *ui;
    VideoCapture cap;
    Mat src_image;
    QTimer *timer;
    QImage *image;
    int time = 10;

    DetectorType detectorType = DetectorType::Vibe;
    TrackerType trackerType = TrackerType::Centroid;
    bool useReid = false;

    unique_ptr<BaseDetector> detector;
    BaseTracker* tracker;
    NetworkReid* reid = nullptr;
};


#endif // MAINWINDOW_H
