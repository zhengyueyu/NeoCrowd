QT += gui

TEMPLATE = lib
DEFINES += NEOCROWDLIB_LIBRARY

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
    Common/MatToQImage.cpp \
    Detector/BackgroundSubtract.cpp \
    Detector/BaseDetector.cpp \
    Detector/SSDMobileNetDetector.cpp \
    Detector/YoloDetector.cpp \
    Detector/vibe/vibe.cpp \
    NeoCrowdLib.cpp \
    Tracker/BaseTracker.cpp \
    Tracker/CentroidTracker.cpp

HEADERS += \
    Common/Config.h \
    Common/MatToQImage.h \
    Common/result_struct.h \
    Detector/BackgroundSubtract.h \
    Detector/BaseDetector.h \
    Detector/SSDMobileNetDetector.h \
    Detector/YoloDetector.h \
    Detector/vibe/vibe.hpp \
    NeoCrowdLib_global.h \
    NeoCrowdLib.h \
    Tracker/BaseTracker.h \
    Tracker/CentroidTracker.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
