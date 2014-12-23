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


SOURCES += main.cpp\
		mainwindow.cpp \
	../common/pixeldisplay.cpp \
    gui_top/guiTop.c \
	../../source/guiGraphics/guiGraphPrimitives.c \
	../../source/guiGraphics/guiGraphWidgets.c \
	../../source/guiGraphics/font_h12.c \
	../../source/guiGraphics/guiGraphHAL.c \
	../../source/guiWidgets/guiTextLabel.c \
	../../source/guiWidgets/guiCheckBox.c \
	../../source/guiCore/guiCore.c \
    ../../source/guiGraphics/font_h32.c \
    ../../source/guiGraphics/font_h10_bold.c \
    ../../source/guiGraphics/font_h10.c \
    ../../source/guiGraphics/font_6x8_mono.c \
    ../../source/guiGraphics/widget_images.c \
    gui_top/guiMainForm.c \
    ../../source/guiWidgets/guiButton.c \
    ../../source/guiWidgets/guiPanel.c \
    gui_top/guiPanel1.c \
    gui_top/guiPanel2.c \
    ../../source/guiWidgets/guiRadioButton.c \
    ../../source/guiCore/guiCoreTimers.c \
    ../../source/guiCore/guiCoreMemory.c

HEADERS  += mainwindow.h \
    ../common/pixeldisplay.h \
    gui_top/guiTop.h \
	../../source/guiGraphics/guiGraphPrimitives.h \
	../../source/guiGraphics/guiGraphWidgets.h \
	../../source/guiGraphics/guiFonts.h \
	../../source/guiGraphics/guiGraphHAL.h \
	../../source/guiGraphics/guiImages.h \
	../../source/guiWidgets/guiTextLabel.h \
	../../source/guiWidgets/guiCheckBox.h \
	../../source/guiCore/guiEvents.h \
	../../source/guiCore/guiCore.h \
    gui_top/guiMainForm.h \
    ../../source/guiWidgets/guiButton.h \
    ../../source/guiWidgets/guiPanel.h \
    gui_top/guiPanel1.h \
    gui_top/guiPanel2.h \
    ../../source/guiWidgets/guiRadioButton.h \
    gui_top/guiConfig.h \
    ../../source/guiCore/guiWidgets.h \
    ../../source/guiCore/guiCoreTimers.h \
    ../../source/guiCore/guiCoreMemory.h
	


FORMS    += mainwindow.ui

