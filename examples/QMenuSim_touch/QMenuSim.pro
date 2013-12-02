#-------------------------------------------------
#
# Project created by QtCreator 2013-11-15T11:14:14
#
#-------------------------------------------------

QT       += core gui

TARGET = QMenuSim
TEMPLATE = app

INCLUDEPATH = ./
INCLUDEPATH += ./gui_top/
INCLUDEPATH += ../common/
INCLUDEPATH += ../../source_touch/guiGraphics/


SOURCES += main.cpp\
		mainwindow.cpp \
	../common/pixeldisplay.cpp \
    gui_top/guiTop.c \
	../../source_touch/guiGraphics/guiGraphPrimitives.c \
	../../source_touch/guiGraphics/guiGraphHAL.c \
	../../source_touch/guiGraphics/guiGraphWidgets.c

HEADERS  += mainwindow.h \
    ../common/pixeldisplay.h \
    gui_top/guiTop.h \
	../../source_touch/guiGraphics/guiGraphPrimitives.h \
	../../source_touch/guiGraphics/guiGraphHAL.h \
	../../source_touch/guiGraphics/guiGraphWidgets.h
	


FORMS    += mainwindow.ui

