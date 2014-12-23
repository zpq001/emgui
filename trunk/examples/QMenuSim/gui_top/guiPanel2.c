/**********************************************************
    Module guiPanel2




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
#include "guiButton.h"
#include "guiPanel.h"


static uint8_t panel2_onDraw(void *sender, guiEvent_t *event);


//-------- Panel elements ---------//
static guiButton_t button1;
static guiButton_t button2;

//----------- GUI Form  -----------//
#define PANEL2_ELEMENTS_COUNT 2
guiPanel_t guiPanel2;
static void *guiPanel2Elements[PANEL2_ELEMENTS_COUNT];
static guiWidgetHandler_t panel2_handlers[1];


void guiPanel2_Initialize()
{
    // Initialize form
    guiPanel_Initialize(&guiPanel2, 0);
    guiPanel2.widgets.count = PANEL2_ELEMENTS_COUNT;
    guiPanel2.widgets.elements = guiPanel2Elements;
    guiPanel2.widgets.elements[0] = &button1;
    guiPanel2.widgets.elements[1] = &button2;
    //guiPanel2.widgets.elements[3] = 0;
    //guiPanel2.widgets.elements[4] = 0;
    //guiPanel2.widgets.elements[5] = 0;
    //guiPanel2.widgets.elements[6] = 0;
    guiPanel2.handlers.count = 1;
    guiPanel2.handlers.elements = panel2_handlers;

    guiPanel2.x = 15;
    guiPanel2.y = 15;
    //guiPanel2.y = 35;
    guiPanel2.width = 280;
    guiPanel2.height = 150;
    guiPanel2.focusFallsThrough = 0;
    guiPanel2.showFocus = 1;
    guiPanel2.frame = FRAME3D_RAISED;
    guiPanel2.tag = 21;

    // Setup button1
    guiButton_Initialize(&button1,  (guiGenericWidget_t *)&guiPanel2);
    button1.x = 5;
    button1.y = 20;
    button1.width = 80;
    button1.height = 18;
    button1.text = "Btn 1";
    button1.font = &font_h10;
    button1.tabIndex = 10;

    // Setup button2
    guiButton_Initialize(&button2,  (guiGenericWidget_t *)&guiPanel2);
    button2.x = 5;
    button2.y = 40;
    button2.width = 80;
    button2.height = 18;
    button2.text = "Btn 2";
    button2.font = &font_h10;
    button2.tabIndex = 11;


    guiPanel2.handlers.elements[0].type = WIDGET_ON_DRAW_EVENT;
    guiPanel2.handlers.elements[0].handler = panel2_onDraw;
}



static uint8_t panel2_onDraw(void *sender, guiEvent_t *event)
{

    if (guiPanel2.redrawForced)
    {
        LCD_SetFont(&font_h10_bold);
        LCD_SetPenColor(CL_BLUE);
        LCD_PrintString("Panel #2", wx + guiPanel2.width/2 - 25, wy + 4);
    }
    return GUI_EVENT_ACCEPTED;
}


