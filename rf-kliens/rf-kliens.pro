#-------------------------------------------------
#
# Project created by QtCreator 2012-02-20T18:42:08
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = rf-kliens
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -lprotobuf

HEADERS += ../protobuf/rendszerfejlesztes.pb.h networkhelper.h \
    rfkliens.h

SOURCES += main.cpp ../protobuf/rendszerfejlesztes.pb.cc networkhelper.cpp \
    rfkliens.cpp
