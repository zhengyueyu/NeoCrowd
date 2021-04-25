/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *open;
    QAction *close;
    QAction *select;
    QAction *actionSSDMobileNet;
    QAction *actionYolov3;
    QAction *actionVbe;
    QAction *actionCentroid_Tracker;
    QAction *actionReid;
    QWidget *centralwidget;
    QLabel *CameraView;
    QLabel *PeopleLabel;
    QLabel *in_out_label;
    QLabel *label;
    QTextEdit *areaEdit;
    QLabel *CameraView2;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menuDetector_Type;
    QMenu *menuTracker_Type;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(735, 554);
        MainWindow->setToolTipDuration(-1);
        open = new QAction(MainWindow);
        open->setObjectName(QString::fromUtf8("open"));
        close = new QAction(MainWindow);
        close->setObjectName(QString::fromUtf8("close"));
        select = new QAction(MainWindow);
        select->setObjectName(QString::fromUtf8("select"));
        actionSSDMobileNet = new QAction(MainWindow);
        actionSSDMobileNet->setObjectName(QString::fromUtf8("actionSSDMobileNet"));
        actionYolov3 = new QAction(MainWindow);
        actionYolov3->setObjectName(QString::fromUtf8("actionYolov3"));
        actionVbe = new QAction(MainWindow);
        actionVbe->setObjectName(QString::fromUtf8("actionVbe"));
        actionCentroid_Tracker = new QAction(MainWindow);
        actionCentroid_Tracker->setObjectName(QString::fromUtf8("actionCentroid_Tracker"));
        actionReid = new QAction(MainWindow);
        actionReid->setObjectName(QString::fromUtf8("actionReid"));
        actionReid->setCheckable(true);
        actionReid->setChecked(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        CameraView = new QLabel(centralwidget);
        CameraView->setObjectName(QString::fromUtf8("CameraView"));
        CameraView->setGeometry(QRect(20, 30, 491, 441));
        PeopleLabel = new QLabel(centralwidget);
        PeopleLabel->setObjectName(QString::fromUtf8("PeopleLabel"));
        PeopleLabel->setGeometry(QRect(540, 30, 131, 41));
        in_out_label = new QLabel(centralwidget);
        in_out_label->setObjectName(QString::fromUtf8("in_out_label"));
        in_out_label->setGeometry(QRect(540, 70, 131, 51));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(540, 130, 67, 17));
        areaEdit = new QTextEdit(centralwidget);
        areaEdit->setObjectName(QString::fromUtf8("areaEdit"));
        areaEdit->setGeometry(QRect(540, 160, 161, 61));
        CameraView2 = new QLabel(centralwidget);
        CameraView2->setObjectName(QString::fromUtf8("CameraView2"));
        CameraView2->setGeometry(QRect(550, 350, 161, 131));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 735, 28));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menuDetector_Type = new QMenu(menu_3);
        menuDetector_Type->setObjectName(QString::fromUtf8("menuDetector_Type"));
        menuTracker_Type = new QMenu(menu_3);
        menuTracker_Type->setObjectName(QString::fromUtf8("menuTracker_Type"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menu->addAction(open);
        menu->addAction(close);
        menu_2->addAction(select);
        menu_3->addAction(menuDetector_Type->menuAction());
        menu_3->addAction(menuTracker_Type->menuAction());
        menu_3->addSeparator();
        menu_3->addAction(actionReid);
        menuDetector_Type->addAction(actionSSDMobileNet);
        menuDetector_Type->addAction(actionYolov3);
        menuDetector_Type->addAction(actionVbe);
        menuTracker_Type->addAction(actionCentroid_Tracker);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "PeopleRecognition", nullptr));
        open->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
        close->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255", nullptr));
        select->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        actionSSDMobileNet->setText(QCoreApplication::translate("MainWindow", "SSDMobileNet", nullptr));
        actionYolov3->setText(QCoreApplication::translate("MainWindow", "Yolov3", nullptr));
        actionVbe->setText(QCoreApplication::translate("MainWindow", "Vibe", nullptr));
        actionCentroid_Tracker->setText(QCoreApplication::translate("MainWindow", "Centroid Tracker", nullptr));
        actionReid->setText(QCoreApplication::translate("MainWindow", "Reid", nullptr));
        CameraView->setText(QString());
        PeopleLabel->setText(QCoreApplication::translate("MainWindow", "number\357\274\232", nullptr));
        in_out_label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>in:</p><p>out:</p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "area\357\274\232", nullptr));
        CameraView2->setText(QString());
        menu->setTitle(QCoreApplication::translate("MainWindow", "\346\221\204\345\203\217\345\244\264", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menu_3->setTitle(QCoreApplication::translate("MainWindow", "\351\200\211\351\241\271", nullptr));
        menuDetector_Type->setTitle(QCoreApplication::translate("MainWindow", "Detector Type", nullptr));
        menuTracker_Type->setTitle(QCoreApplication::translate("MainWindow", "Tracker Type", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
