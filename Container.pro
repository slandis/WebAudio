
#-------------------------------------------------
#
# Project created by QtCreator 2015-05-11T10:46:04
#
#-------------------------------------------------

QT       += core gui
QT       += webkitwidgets
QT	 += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -lasound
TARGET = container
TEMPLATE = app


SOURCES += main.cpp \
    	Container.cpp \
	Audio.cpp

HEADERS  += Container.h \
	    Audio.h
