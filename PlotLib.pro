#-------------------------------------------------
#
# Project created by QtCreator 2012-02-19T15:11:16
#
#-------------------------------------------------


TARGET = PlotLib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += plcurveszone.cpp plsinglecurve.cpp

HEADERS += plcurveszone.h plsinglecurve.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
