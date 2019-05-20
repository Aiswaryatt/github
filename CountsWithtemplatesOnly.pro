TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    updatepatches.cpp

INCLUDEPATH += "E:\opencv\install\include"

Release
{
LIBS += -LE:\opencv\lib    \
-llibopencv_world320 \
-llibopencv_tracking320
}

Debug
{
LIBS += -LE:\opencv\lib    \
-llibopencv_world320d \
-llibopencv_tracking320d
}

HEADERS += \
    updatepatches.h
