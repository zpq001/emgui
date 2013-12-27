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
INCLUDEPATH += ../../source/guiWidgets_monochrome/
INCLUDEPATH += ../../source/guiCore/
INCLUDEPATH += ../../source/utils/
INCLUDEPATH += ../../source/guiGraphics_monochrome/

SOURCES += main.cpp\
		mainwindow.cpp \
    ../common/pixeldisplay.cpp \
	../../source/guiGraphics_monochrome/font_6x8_mono.c \
    ../../source/guiGraphics_monochrome/font_h32.c \
    ../../source/guiGraphics_monochrome/font_h10.c \
    ../../source/guiGraphics_monochrome/font_h10_bold.c \
	../../source/guiGraphics_monochrome/widget_images.c \
    ../../source/guiGraphics_monochrome/guiGraphHAL.c \
    ../../source/guiGraphics_monochrome/guiGraphPrimitives.c \
    ../../source/guiGraphics_monochrome/guiGraphWidgets.c \
    ../../source/guiCore/guiCore.c \
	../../source/guiWidgets_monochrome/guiPanel.c \
    ../../source/guiWidgets_monochrome/guiCheckBox.c \
	../../source/guiWidgets_monochrome/guiTextLabel.c \
	gui_top/guiTop.c \
    gui_top/guiMainForm.c \
    gui_top/guiSetupPanel.c \
    gui_top/guiMasterPanel.c \
    ../../source/guiGraphics_monochrome/font_h11.c \
    ../../source/guiWidgets_monochrome/guiSpinBox.c \
    ../../source/utils/utils.c \
    ../../source/guiGraphics_monochrome/font_h16.c \
    ../common/keydriver.cpp \
    gui_top/uartParser.c \
    ../../source/guiGraphics_monochrome/other_images.c
	

HEADERS  += mainwindow.h \
    ../common/pixeldisplay.h \
	../../source/guiGraphics_monochrome/guiFonts.h \
	../../source/guiGraphics_monochrome/guiImages.h \
	../../source/guiGraphics_monochrome/guiGraphHAL.h \
    ../../source/guiGraphics_monochrome/guiGraphPrimitives.h \
	../../source/guiGraphics_monochrome/guiGraphWidgets.h \
	../../source/guiCore/guiEvents.h \
    ../../source/guiCore/guiCore.h \
	../../source/guiWidgets_monochrome/guiWidgets.h \
	../../source/guiWidgets_monochrome/guiPanel.h \
	../../source/guiWidgets_monochrome/guiTextLabel.h \
	../../source/guiWidgets_monochrome/guiCheckBox.h \
    gui_top/guiConfig.h \
	gui_top/guiTop.h \
    gui_top/guiMainForm.h \
    gui_top/guiSetupPanel.h \
    gui_top/guiMasterPanel.h \
    ../../source/guiWidgets_monochrome/guiSpinBox.h \
    ../../source/utils/utils.h \
    ../common/keydriver.h \
    gui_top/uartParser.h
    
    
	


FORMS    += mainwindow.ui

