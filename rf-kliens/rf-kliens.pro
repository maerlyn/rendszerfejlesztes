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
    rfkliens.h \
    megallok_controller.h \
    utvonal_controller.h \
    buszok_controller.h \
    soforok_controller.h \
    jaratok_controller.h

SOURCES += main.cpp ../protobuf/rendszerfejlesztes.pb.cc networkhelper.cpp \
    rfkliens.cpp \
    megallok_controller.cpp \
    utvonal_controller.cpp \
    buszok_controller.cpp \
    soforok_controller.cpp \
    jaratok_controller.cpp
