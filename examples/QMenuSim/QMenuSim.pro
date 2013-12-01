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
    ../../source/guiCore/soft_timer.c \
    ../../source/guiCore/guiUtils.c \
    ../../source/guiCore/guiEvents.c \
    ../../source/guiCore/guiCore.c \
    ../../source/guiFonts/font_8x12.c \
    ../../source/guiForm/guiForm.c \
    ../../source/guiGraphics/guiGraphUtils.c \
    ../../source/guiGraphics/guiFontUtils.c \
    ../../source/guiWidgets/guiTextLabel.c \
    ../../source/guiWidgets/guiSpinEdit.c \
    ../../source/guiWidgets/guiListBox.c \
    gui_top/menu_top.c \
    gui_top/guiSetupForm.c \
    gui_top/guiMainForm.c
	

HEADERS  += mainwindow.h \
    ../common/pixeldisplay.h \
    ../../source/guiCore/soft_timer.h \
    ../../source/guiCore/guiUtils.h \
    ../../source/guiCore/guiEvents.h \
    ../../source/guiCore/guiCore.h \
    ../../source/guiFonts/guiFonts.h \
    ../../source/guiFonts/font_defs.h \
    ../../source/guiForm/guiForm.h \
    ../../source/guiGraphics/guiGraphUtils.h \
    ../../source/guiGraphics/guiGraphCommon.h \
    ../../source/guiGraphics/guiFontUtils.h \
    ../../source/guiWidgets/guiWidgetCommon.h \
    ../../source/guiWidgets/guiTextLabel.h \
    ../../source/guiWidgets/guiSpinEdit.h \
    ../../source/guiWidgets/guiListBox.h \
    gui_top/menu_top.h \
    gui_top/guiSetupForm.h \
    gui_top/guiMainForm.h \
    gui_top/guiConfig.h
	


FORMS    += mainwindow.ui

