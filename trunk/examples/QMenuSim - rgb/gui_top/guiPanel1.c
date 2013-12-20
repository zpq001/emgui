/**********************************************************
    Module guiPanel1




**********************************************************/

#include <stdio.h>      // due to printf
#include <stdint.h>

#include "guiFonts.h"
#include "guiGraphHAL.h"
#include "guiGraphPrimitives.h"
#include "guiGraphWidgets.h"

#include "guiCore.h"
#include "guiEvents.h"
#include "guiWidgets.h"
#include "guiTextLabel.h"
#include "guiCheckBox.h"
#include "guiRadioButton.h"
#include "guiButton.h"
#include "guiPanel.h"


static uint8_t panel1_onDraw(void *sender, guiEvent_t *event);


//-------- Panel elements ---------//
static guiButton_t button1;
static guiButton_t button2;
static guiCheckBox_t checkBox1;
static guiCheckBox_t checkBox2;
static guiRadioButton_t radioButton1;
static guiRadioButton_t radioButton2;
static guiRadioButton_t radioButton3;
static guiRadioButton_t radioButton4;

//----------- GUI Form  -----------//
#define PANEL1_ELEMENTS_COUNT 8
guiPanel_t guiPanel1;
static void *guiPanel1Elements[PANEL1_ELEMENTS_COUNT];
static guiWidgetHandler_t panel1_handlers[1];


void guiPanel1_Initialize(guiGenericWidget_t *parent)
{
    // Initialize form
    guiPanel_Initialize(&guiPanel1, parent);
    guiPanel1.widgets.count = PANEL1_ELEMENTS_COUNT;
    guiPanel1.widgets.elements = guiPanel1Elements;
    guiPanel1.widgets.elements[0] = &button1;
    guiPanel1.widgets.elements[1] = &button2;
    guiPanel1.widgets.elements[2] = &checkBox1;
    guiPanel1.widgets.elements[3] = &radioButton1;
    guiPanel1.widgets.elements[4] = &radioButton2;
    guiPanel1.widgets.elements[5] = &radioButton3;
    guiPanel1.widgets.elements[6] = &radioButton4;
    guiPanel1.widgets.elements[7] = &checkBox2;
    guiPanel1.handlers.count = 1;
    guiPanel1.handlers.elements = panel1_handlers;

    guiPanel1.isVisible = 1;
    guiPanel1.x = 10;
    guiPanel1.y = 10;
    guiPanel1.width = 280;
    guiPanel1.height = 150;
    guiPanel1.frame = FRAME3D_SUNKEN;
    guiPanel1.tag = 20;

    // Setup button1
    guiButton_Initialize(&button1,  (guiGenericWidget_t *)&guiPanel1);
    button1.x = 5;
    button1.y = 20;
    button1.width = 80;
    button1.height = 18;
    button1.text = "Btn 1";
    button1.font = &font_h10;
    button1.tabIndex = 10;
    //button1.handlers.elements = button_handlers;
    //button1.handlers.count = 1;

    // Setup button2
    guiButton_Initialize(&button2,  (guiGenericWidget_t *)&guiPanel1);
    button2.x = 150;
    button2.y = 90;
    button2.width = 80;
    button2.height = 50;
    button2.text = "Btn 2";
    button2.font = &font_h10;
    button2.tabIndex = 11;
    //button2.handlers.elements = button_handlers;
    //button2.handlers.count = 1;

    // Setup checkbox
    guiCheckBox_Initialize(&checkBox1,(guiGenericWidget_t *)&guiPanel1);
    checkBox1.x = 5;
    checkBox1.y = 60;
    checkBox1.width = 50;
    checkBox1.height = 16;
    checkBox1.text = "Box 1";
    checkBox1.font = &font_h10;
    checkBox1.tabIndex = 12;

    guiCheckBox_Initialize(&checkBox2,(guiGenericWidget_t *)&guiPanel1);
    checkBox2.x = 5;
    checkBox2.y = 80;
    checkBox2.width = 50;
    checkBox2.height = 16;
    checkBox2.text = "Box 2";
    checkBox2.font = &font_h10;
    checkBox2.tabIndex = 17;


    guiRadioButton_Initialize(&radioButton1, (guiGenericWidget_t *)&guiPanel1);
    radioButton1.x = 110;
    radioButton1.y = 20;
    radioButton1.width = 80;
    radioButton1.height = 16;
    radioButton1.text = "My radio 1";
    radioButton1.font = &font_h10;
    radioButton1.tabIndex = 13;
    radioButton1.acceptFocusByTab = 1;
    radioButton1.acceptTouch = 1;

    guiRadioButton_Initialize(&radioButton2, (guiGenericWidget_t *)&guiPanel1);
    radioButton2.x = 110;
    radioButton2.y = 40;
    radioButton2.width = 80;
    radioButton2.height = 16;
    radioButton2.text = "My radio 2";
    radioButton2.font = &font_h10;
    radioButton2.tabIndex = 14;
    radioButton2.acceptFocusByTab = 1;
    radioButton2.acceptTouch = 1;

    guiRadioButton_Initialize(&radioButton3, (guiGenericWidget_t *)&guiPanel1);
    radioButton3.x = 110;
    radioButton3.y = 60;
    radioButton3.width = 80;
    radioButton3.height = 16;
    radioButton3.text = "My radio 3";
    radioButton3.font = &font_h10;
    radioButton3.tabIndex = 15;
    radioButton3.acceptFocusByTab = 1;
    radioButton3.acceptTouch = 1;

    guiRadioButton_Initialize(&radioButton4, (guiGenericWidget_t *)&guiPanel1);
    radioButton4.x = 110;
    radioButton4.y = 80;
    radioButton4.width = 80;
    radioButton4.height = 16;
    radioButton4.text = "My radio 4";
    radioButton4.font = &font_h10;
    radioButton4.tabIndex = 16;
    radioButton4.acceptFocusByTab = 1;
    radioButton4.acceptTouch = 1;

    guiPanel1.handlers.elements[0].eventType = GUI_EVENT_DRAW;
    guiPanel1.handlers.elements[0].handler = panel1_onDraw;

    radioButton1.isChecked = 1;
}



static uint8_t panel1_onDraw(void *sender, guiEvent_t *event)
{
    if (guiPanel1.redrawForced)
    {
        LCD_SetFont(&font_h10_bold);
        LCD_SetPenColor(CL_BLUE);
        LCD_PrintString("Panel #1", wx + guiPanel1.width/2 - 25, wy + 4);
    }
    return GUI_EVENT_ACCEPTED;
}




