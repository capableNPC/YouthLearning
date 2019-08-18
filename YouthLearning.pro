#-------------------------------------------------
#
# Project created by QtCreator 2019-08-12T09:50:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = YouthLearning
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        blmainwindow.cpp \
    filegenerate.cpp

HEADERS += \
        blmainwindow.h \
    filegenerate.h

FORMS +=

INCLUDEPATH += E:/l/CPP/quazip/include
LIBS += -LE:/l/CPP/quazip/lib -lquazip -LE:/l/CPP/quazip/lib -lzlib1
#需要将quazip.dll文件和zlib1.dll文件复制到程序的debug目录下。

RESOURCES += \
    qss.qrc \
    icon.qrc
