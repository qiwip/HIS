#-------------------------------------------------
#
# Project created by QtCreator 2017-05-28T21:07:09
#
#-------------------------------------------------

QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HIS
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


SOURCES += main.cpp\
        widget.cpp \
    login.cpp \
    reg.cpp \
    view1.cpp \
    view2.cpp \
    view3.cpp \
    view4.cpp \
    view5.cpp \
    view6.cpp \
    doc_view1.cpp \
    doc_view2.cpp \
    view7.cpp \
    doc_manage.cpp \
    paintarea.cpp

HEADERS  += widget.h \
    login.h \
    reg.h \
    view1.h \
    view2.h \
    view3.h \
    view4.h \
    view5.h \
    view6.h \
    doc_view1.h \
    doc_view2.h \
    view7.h \
    doc_manage.h \
    paintarea.h

FORMS    += widget.ui \
    login.ui \
    reg.ui \
    view1.ui \
    view2.ui \
    view3.ui \
    view4.ui \
    view5.ui \
    view6.ui \
    doc_view1.ui \
    doc_view2.ui \
    view7.ui \
    doc_manage.ui

RESOURCES += \
    ../resource/resource.qrc
