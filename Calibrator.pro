#-------------------------------------------------
#
# Project created by QtCreator 2018-04-17T14:33:46
#
#-------------------------------------------------

QT       += core gui
QT       +=serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Calibrator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    interfacemodel.cpp \
    dcmodel.cpp \
    squmodel.cpp \
    sinmodel.cpp \
    edgemodel.cpp \
    markermodel.cpp \
    funwavemodel.cpp \
    pulsewidthmodel.cpp \
    overloadpulsemodel.cpp \
    dcdialog.cpp \
    squdialog.cpp \
    edgedialog.cpp \
    sindialog.cpp \
    pulsewidthdialog.cpp \
    funwavedialog.cpp \
    markerdialog.cpp \
    overloadpulsedialog.cpp \
    rescapmeasurementmodel.cpp \
    videotrigermodel.cpp \
    videotrigerdialog.cpp \
    rescapmeasurementdialog.cpp \
    resthread.cpp \
    capthread.cpp

HEADERS  += mainwindow.h \
    interfacemodel.h \
    dcmodel.h \
    squmodel.h \
    sinmodel.h \
    edgemodel.h \
    markermodel.h \
    funwavemodel.h \
    pulsewidthmodel.h \
    overloadpulsemodel.h \
    dcdialog.h \
    squdialog.h \
    edgedialog.h \
    sindialog.h \
    pulsewidthdialog.h \
    funwavedialog.h \
    markerdialog.h \
    overloadpulsedialog.h \
    rescapmeasurementmodel.h \
    videotrigermodel.h \
    videotrigerdialog.h \
    rescapmeasurementdialog.h \
    resthread.h \
    capthread.h

FORMS    += mainwindow.ui \
    dcdialog.ui \
    squdialog.ui \
    edgedialog.ui \
    sindialog.ui \
    pulsewidthdialog.ui \
    funwavedialog.ui \
    markerdialog.ui \
    overloadpulsedialog.ui \
    videotrigerdialog.ui \
    rescapmeasurementdialog.ui

RESOURCES += \
    resourcefile.qrc
INCLUDEPATH += $$PWD/../build-Calibrator-Desktop_Qt_5_6_2_MinGW_32bit-Debug/debug
DEPENDPATH += $$PWD/../build-Calibrator-Desktop_Qt_5_6_2_MinGW_32bit-Debug/debug
RC_ICONS=Icon/myico.ico
