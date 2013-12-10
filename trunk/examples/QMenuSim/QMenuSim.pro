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
INCLUDEPATH += ../../source/guiWidgets/
INCLUDEPATH += ../../source/guiCore/
INCLUDEPATH += ../../source/guiGraphics/
INCLUDEPATH += ../../source/guiFonts/
INCLUDEPATH += ../../source/guiForm/

SOURCES += main.cpp\
		mainwindow.cpp \
    ../common/pixeldisplay.cpp \
    gui_top/guiTop.c \
    ../../source/guiGraphics/guiGraphHAL.c \
    ../../source/guiGraphics/guiGraphPrimitives.c \
    ../../source/guiGraphics/guiGraphWidgets.c \
    ../../source/guiWidgets/guiTextLabel.c \
    ../../source/guiWidgets/guiForm.c \
    ../../source/guiCore/guiCore.c \
    gui_top/guiMainForm.c \
    gui_top/guiSubForm1.c \
    ../../source/guiGraphics/font_6x8_mono.c \
    ../../source/guiGraphics/font_h12.c \
    ../../source/guiGraphics/font_h32.c \
    ../../source/guiGraphics/font_h10.c \
    ../../source/guiGraphics/font_h10_bold.c \
    ../../source/guiWidgets/guiCheckBox.c
	

HEADERS  += mainwindow.h \
    ../common/pixeldisplay.h \
    gui_top/guiTop.h \
    ../../source/guiGraphics/guiGraphHAL.h \
    ../../source/guiGraphics/guiGraphPrimitives.h \
    ../../source/guiGraphics/guiFonts.h \
    ../../source/guiWidgets/guiWidgets.h \
    ../../source/guiGraphics/guiGraphWidgets.h \
    ../../source/guiWidgets/guiTextLabel.h \
    ../../source/guiCore/guiEvents.h \
    ../../source/guiWidgets/guiForm.h \
    ../../source/guiCore/guiCore.h \
    gui_top/guiMainForm.h \
    gui_top/guiSubForm1.h \
    ../../source/guiWidgets/guiCheckBox.h
	


FORMS    += mainwindow.ui

