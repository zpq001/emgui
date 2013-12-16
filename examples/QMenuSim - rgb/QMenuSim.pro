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
INCLUDEPATH += ../../source/guiGraphics_2/


SOURCES += main.cpp\
		mainwindow.cpp \
	../common/pixeldisplay.cpp \
    gui_top/guiTop.c \
	../../source/guiGraphics_2/guiGraphPrimitives.c \
	../../source/guiGraphics_2/guiGraphWidgets.c \
	../../source/guiGraphics_2/font_h12.c \
	../../source/guiGraphics_2/guiGraphHAL.c \
	../../source/guiWidgets/guiTextLabel.c \
	../../source/guiWidgets/guiCheckBox.c \
	../../source/guiCore/guiCore.c \
    ../../source/guiGraphics_2/font_h32.c \
    ../../source/guiGraphics_2/font_h10_bold.c \
    ../../source/guiGraphics_2/font_h10.c \
    ../../source/guiGraphics_2/font_6x8_mono.c \
    ../../source/guiGraphics_2/widget_images.c \
    gui_top/guiMainForm.c \
    ../../source/guiWidgets/guiButton.c \
    ../../source/guiWidgets/guiPanel.c \
    gui_top/guiPanel1.c \
    gui_top/guiPanel2.c

HEADERS  += mainwindow.h \
    ../common/pixeldisplay.h \
    gui_top/guiTop.h \
	../../source/guiGraphics_2/guiGraphPrimitives.h \
	../../source/guiGraphics_2/guiGraphWidgets.h \
	../../source/guiGraphics_2/guiFonts.h \
	../../source/guiGraphics_2/guiGraphHAL.h \
	../../source/guiGraphics_2/guiImages.h \
	../../source/guiWidgets/guiWidgets.h \
	../../source/guiWidgets/guiTextLabel.h \
	../../source/guiWidgets/guiCheckBox.h \
	../../source/guiCore/guiEvents.h \
	../../source/guiCore/guiCore.h \
    gui_top/guiMainForm.h \
    ../../source/guiWidgets/guiButton.h \
    ../../source/guiWidgets/guiPanel.h \
    gui_top/guiPanel1.h \
    gui_top/guiPanel2.h
	


FORMS    += mainwindow.ui

