#-------------------------------------------------
#
# Project created by QtCreator 2012-02-20T18:24:38
#
#-------------------------------------------------

QT       += core network sql

QT       -= gui

TARGET = rf-szerver
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -lprotobuf

SOURCES += main.cpp \
    rfszerver.cpp ../protobuf/rendszerfejlesztes.pb.cc

HEADERS += \
    rfszerver.h ../protobuf/rendszerfejlesztes.pb.h \
    connection.h
