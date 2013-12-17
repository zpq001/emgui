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
#include "guiButton.h"
#include "guiPanel.h"


static uint8_t panel1_onDraw(void *sender, guiEvent_t *event);


//-------- Panel elements ---------//
static guiButton_t button1;
static guiButton_t button2;
static guiCheckBox_t checkBox1;

//----------- GUI Form  -----------//
#define PANEL1_ELEMENTS_COUNT 3
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
    //guiPanel1.widgets.elements[4] = 0;
    //guiPanel1.widgets.elements[5] = 0;
    //guiPanel1.widgets.elements[6] = 0;
    guiPanel1.handlers.count = 1;
    guiPanel1.handlers.elements = panel1_handlers;

    guiPanel1.isVisible = 1;
    guiPanel1.redrawRequired = 1;
    guiPanel1.redrawForced = 1;
    guiPanel1.x = 10;
    guiPanel1.y = 10;
    guiPanel1.width = 280;
    guiPanel1.height = 150;
    guiPanel1.acceptFocusByTab = 1;
    guiPanel1.focusFallsThrough = 1;
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
    button2.x = 5;
    button2.y = 40;
    button2.width = 80;
    button2.height = 18;
    button2.text = "Btn 2";
    button2.font = &font_h10;
    button2.tabIndex = 11;
    //button2.handlers.elements = button_handlers;
    //button2.handlers.count = 1;

    // Setup checkbox
    guiCheckBox_Initialize(&checkBox1,(guiGenericWidget_t *)&guiPanel1);
    checkBox1.x = 5;
    checkBox1.y = 60;
    checkBox1.width = 80;
    checkBox1.height = 16;
    checkBox1.text = "Abc123";
    checkBox1.font = &font_h10;
    checkBox1.tabIndex = 12;
    checkBox1.acceptFocusByTab = 1;
    checkBox1.acceptTouch = 1;

    // Setup button handlers
    //button_handlers[0].eventType = BUTTON_CLICKED;
    //button_handlers[0].handler = button_onClicked;

    guiPanel1.handlers.elements[0].eventType = GUI_ON_DRAW;
    guiPanel1.handlers.elements[0].handler = panel1_onDraw;
}



static uint8_t panel1_onDraw(void *sender, guiEvent_t *event)
{
    if (guiPanel1.redrawFlags & PANEL_REDRAW_BACKGROUND)
    {
        LCD_SetFont(&font_h10_bold);
        LCD_SetPenColor(CL_BLUE);
        LCD_PrintString("Panel #1", wx + guiPanel1.width/2 - 25, wy + 4);
    }
    return GUI_EVENT_ACCEPTED;
}




/*
static uint8_t button_onClicked(void *sender, guiEvent_t event)
{
    guiLogEvent("Button clicked");




    return GUI_EVENT_ACCEPTED;
}
*/

