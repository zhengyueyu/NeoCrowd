QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BaseDetector.cpp \
    BaseTracker.cpp \
    DealAreaString.cpp \
    Detector/BackgroundSubtract.cpp \
    Detector/SSDMobileNetDetector.cpp \
    Detector/YoloDetector.cpp \
    Detector/vibe/vibe.cpp \
    MatToQImage.cpp \
    NetworkReid.cpp \
    Tracker/CentroidTracker.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    BaseDetector.h \
    BaseTracker.h \
    DealAreaString.h \
    Detector/BackgroundSubtract.h \
    Detector/SSDMobileNetDetector.h \
    Detector/YoloDetector.h \
    Detector/vibe/vibe.hpp \
    MatToQImage.h \
    NetworkReid.h \
    Tracker/CentroidTracker.h \
    mainwindow.h \ \
    result_struct.h

FORMS += \
    mainwindow.ui

LIBS += /usr/local/lib/libopencv*


INCLUDEPATH += \
        /usr/local/include


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
