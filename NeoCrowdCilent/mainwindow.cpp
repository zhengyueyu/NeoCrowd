#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <regex>

std::vector<std::vector<cv::Point>> get_contours(std::string str)
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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    image = new QImage();
    ui->areaEdit->setPlainText(QString("300,150,450,150,450,50,300,50"));
    connect(timer,SIGNAL(timeout()),this,SLOT(dealFrame()));
    connect(ui->open,SIGNAL(clicked()),this,SLOT(on_open_triggered()));
    connect(ui->close,SIGNAL(clicked()),this,SLOT(on_Stop_triggered()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Init()
{
    detector = CreateDetector(detectorType);
    tracker = CreateTracker(trackerType);
    detector->Init(src_image);

    tracker->SetArea(get_contours(ui->areaEdit->toPlainText().toStdString()));
    if(useReid)
    {
        reid = CreateReid();
        QObject::connect(reid, SIGNAL(ID_SIGNAL(int stamp, int id)), tracker, SLOT(Update(int stamp, int id)));
    }
    tracker->Init(src_image, std::move(detector), reid);
}

void MainWindow::on_open_triggered()
{
    on_close_triggered();

    cap.open(0);
    cap.read(src_image);
    Init();
    timer->start(1);
}

void MainWindow::on_close_triggered()
{
    timer->stop();
    cap.release();
    ui->CameraView->clear();
}

void MainWindow::dealFrame()
{
    bool success = cap.read(src_image);
    if(!success)
    {
        cap.release();
        timer->stop();
        return;
    }

    QImage qimage_src = MatImageToQt(src_image);
    QPixmap qpixmap_src = QPixmap::fromImage(qimage_src);
    QPixmap resize_qpixmap_src = qpixmap_src.scaled(ui->CameraView2->width(), ui->CameraView2->height(),Qt::KeepAspectRatio);
    ui->CameraView2->setPixmap(resize_qpixmap_src);


    Result result = tracker->Update(&src_image);
    QImage qimage_update = MatImageToQt(result.image);
    QPixmap qpixmap_update = QPixmap::fromImage(qimage_update);
    QPixmap resize_qpixmap_update = qpixmap_update.scaled(ui->CameraView->width(), ui->CameraView->height(),Qt::KeepAspectRatio);
    ui->CameraView->setPixmap(resize_qpixmap_update);


    QString count = QString::number(result.person_num);
    ui->PeopleLabel->setText("number: " + count);
    QString in = QString::number(result.person_count.in);
    QString out = QString::number(result.person_count.out);
    ui->in_out_label->setText("in:"+in+"\nout:"+out);
    time++;

}

void MainWindow::on_select_triggered()
{
    on_close_triggered();
    file = QFileDialog::getOpenFileName(
                this,
                "Select a Image",
                "/home/yy/",
                tr("video files(*.avi *.mp4 *.wmv *mpg);;images(*.png *.jpg *.jpeg *.bmp);;All files(*.*)"));
    cap.open(file.toStdString());
    cap.read(src_image);

    Init();

    timer->start(1);
}

void MainWindow::on_actionSSDMobileNet_triggered()
{
    detectorType = DetectorType::SSDMobileNet;
}

void MainWindow::on_actionYolov3_triggered()
{
    detectorType = DetectorType::YOLO;
}

void MainWindow::on_actionVbe_triggered()
{
    detectorType = DetectorType::Vibe;
}

void MainWindow::on_actionCentroid_Tracker_triggered()
{
    trackerType = TrackerType::Centroid;
}

void MainWindow::on_actionReid_toggled(bool arg1)
{
    useReid = arg1;
}
