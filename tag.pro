#-------------------------------------------------
#
# Project created by QtCreator 2018-02-24T19:19:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tag
TEMPLATE = app
RC_ICONS = ./icons/tag.ico

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

VPATH += \
        src \
        headers \
        forms

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        algorithm.cpp \
        mygraphicsview.cpp

HEADERS += \
        mainwindow.h \
        algorithm.h \
        mygraphicsview.h

FORMS += \
        mainwindow.ui

INCLUDEPATH += D:\Programs\opencv\build\include

LIBS += D:\Programs\opencv\release\bin\libopencv_core340.dll
LIBS += D:\Programs\opencv\release\bin\libopencv_highgui340.dll
LIBS += D:\Programs\opencv\release\bin\libopencv_imgcodecs340.dll
LIBS += D:\Programs\opencv\release\bin\libopencv_imgproc340.dll
LIBS += D:\Programs\opencv\release\bin\libopencv_features2d340.dll
LIBS += D:\Programs\opencv\release\bin\libopencv_calib3d340.dll
