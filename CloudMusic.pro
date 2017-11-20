#-------------------------------------------------
#
# Project created by QtCreator 2017-06-10T18:57:04
#
#-------------------------------------------------

QT       += core gui multimedia sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CloudMusic
TEMPLATE = app

RC_ICONS = Desktopico.ico

LIBS += $$PWD/libtag.a

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        MainWidget.cpp \
    FramelessAndAutoSize.cpp \
    TitleBar.cpp \
    MiddleWidget.cpp \
    MiddleWidgetLeftList.cpp \
    MiddleWidgetRightStack.cpp \
    BottomWidget.cpp \
    PlaySongInfoWidget.cpp \
    BaseStackChildWidget.cpp \
    TrayIconMenu.cpp \
    miniWidget.cpp \
    SongListFrame.cpp \
    PlayListItemStyle.cpp \
    SelectDirFrame.cpp \
    DataBase.cpp \
    ThreadFromObject.cpp \
    AnimationWidget.cpp

HEADERS  += MainWidget.h \
    FramelessAndAutoSize.h \
    TitleBar.h \
    MiddleWidget.h \
    MiddleWidgetLeftList.h \
    MiddleWidgetRightStack.h \
    BottomWidget.h \
    PlaySongInfoWidget.h \
    BaseStackChildWidget.h \
    TrayIconMenu.h \
    miniWidget.h \
    SongListFrame.h \
    PlayListItemStyle.h \
    SelectDirFrame.h \
    DataBase.h \
    ThreadFromObject.h \
    AnimationWidget.h

RESOURCES += \
    res.qrc
