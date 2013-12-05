/**********************************************************
    Module guiMainForm




**********************************************************/

#include <stdio.h>      // due to printf
#include <stdint.h>

#include "guiFonts.h"
#include "guiGraphPrimitives.h"
#include "guiEvents.h"
#include "guiWidgets.h"
#include "guiTextLabel.h"
#include "guiForm.h"


// Other forms - in order to switch between them
#include "guiMainForm.h"
//#include "guiSetupForm.h"

extern void guiLogEvent(char *string);



//static void textLabel1_updateCallback(void *pSender);
//static void textLabel2_updateCallback(void *pSender);
static uint8_t guiMainForm_ProcessEvents(guiGenericWidget_t *pWidget, guiEvent_t event);
//static void guiMainForm_drawStatic(void);


//--------- Form elements ---------//
static guiTextLabel_t textLabel1;
//static char textLabel1_data[20];
//static guiWidgetHandler_t textLabel1Handlers[2];

static guiTextLabel_t textLabel2;
//static char textLabel2_data[20];
//static guiWidgetHandler_t textLabel2Handlers[2];


//----------- GUI Form  -----------//
guiForm_t     guiMainForm;
static void *guiMainFormElements[2];


void guiMainForm_Initialize(void)
{
    // Initialize gui elements

    guiForm_Initialize(&guiMainForm);
    guiMainForm.processEvent = guiMainForm_ProcessEvents;
    guiMainForm.widgets.count = 2;
    guiMainForm.widgets.elements = guiMainFormElements;
    guiMainForm.widgets.elements[0] = &textLabel1;
    guiMainForm.widgets.elements[1] = &textLabel2;



    //guiMainForm.handlers.count = 2;
    //guiMainForm.handlers.elements[0] = {GUI_EVENT_SELECT, }

    guiTextLabel_Initialize(&textLabel1, (guiGenericWidget_t *)&guiMainForm);
    textLabel1.tabIndex = 1;
    textLabel1.acceptFocus = 1;
    textLabel1.acceptFocusByTab = 1;
    textLabel1.x = 5;
    textLabel1.y = 10;
    textLabel1.width = 80;
    textLabel1.height = 20;
    textLabel1.alignment = ALIGN_CENTER;
    textLabel1.text = "My label #1";

    guiTextLabel_Initialize(&textLabel2, (guiGenericWidget_t *)&guiMainForm);
    textLabel2.tabIndex = 2;
    textLabel2.acceptFocus = 1;
    textLabel2.acceptFocusByTab = 1;
    textLabel2.x = 5;
    textLabel2.y = 40;
    textLabel2.width = 80;
    textLabel2.height = 20;
    textLabel2.alignment = ALIGN_CENTER;
    textLabel2.text = "My label #2";


/*
    guiTextLabel_Initialize(&TextLabel1);
    TextLabel1.pfont = &font_8x12;
    TextLabel1.string = textLabel1_data;
    TextLabel1.x_pos = 10;
    TextLabel1.y_pos = 3;
    TextLabel1.tabIndex = 4;
    TextLabel1.properties = WP_IS_VISIBLE;
    TextLabel1.handlers.count = 1;
    TextLabel1.handlers.elements = textLabel1Handlers;
    TextLabel1.handlers.elements[0].eventType = GUI_EVENT_UPDATE;
    TextLabel1.handlers.elements[0].handler = textLabel1_updateCallback;


    guiTextLabel_Initialize(&TextLabel2);
    TextLabel2.pfont = &font_8x12;
    TextLabel2.string = textLabel2_data;
    TextLabel2.x_pos = 10;
    TextLabel2.y_pos = 50;
    TextLabel2.tabIndex = 9;
    TextLabel2.properties = WP_IS_VISIBLE;
    TextLabel2.handlers.count = 1;
    TextLabel2.handlers.elements = textLabel2Handlers;
    TextLabel2.handlers.elements[0].eventType = GUI_EVENT_UPDATE;
    TextLabel2.handlers.elements[0].handler = textLabel2_updateCallback;
    */
}


static uint8_t guiMainForm_ProcessEvents(struct guiGenericWidget_t *pWidget, guiEvent_t event)
{
/*    // Process GUI messages - select, draw, etc
    switch(event.type)
    {
        case GUI_EVENT_DRAW:
            guiForm_Draw(&guiMainForm);     // Draws form and all childs
            if (guiMainForm.redrawFlags & WF_REDRAW)
                guiMainForm_drawStatic();
            guiMainForm.redrawFlags = 0;
            break;
        case GUI_EVENT_SELECT:
            guiCore_SelectWidget(&guiMainForm.widgets, (guiGenericWidget_t *)&TextLabel1);
            guiCore_RequestFullRedraw();
            break;
        case GUI_EVENT_DESELECT:
            guiCore_SelectWidget(&guiMainForm.widgets, 0);
            break;
        default:
            // Process form logic
            // CHECKME - maybe pass event to selected widget - if appropriate handler is not found,
            // process here ?
            // If using containers, there should be a function that allows tabStop for any container, not only for form
            if (((guiEventArgButtons_t *)event.args)->buttonCode & GUI_BTN_ESC)
            {
                guiCore_RequestSwitchForm(&guiSetupForm);
            }
            else if (((guiEventArgButtons_t *)event.args)->buttonCode & GUI_BTN_LEFT)
            {
                guiCore_SelectNextWidget(&guiMainForm.widgets, -1);
            }
            else if (((guiEventArgButtons_t *)event.args)->buttonCode & GUI_BTN_RIGHT)
            {
                guiCore_SelectNextWidget(&guiMainForm.widgets, 1);
            }
                // Pass event to the widgets
    }
    guiCore_CallEventHandler((guiGenericWidget_t *)&guiMainForm,event.type); */
    return 0;

}


/*
static void textLabel1_updateCallback(void* pSender)
{
    guiLogEvent("Request update for MainForm.textLabel1");

    // Move label across form
    static int8_t increment = 1;
    if (TextLabel1.x_pos >= 70) increment = -1;
    else if (TextLabel1.x_pos <= 10) increment = 1;
    TextLabel1.x_pos += increment;
    guiCore_RequestFullRedraw();

    sprintf(TextLabel1.string,"%s%d","Label xpos = ",TextLabel1.x_pos);
}

static void textLabel2_updateCallback(void* pSender)
{
    static uint32_t calls = 0;
    guiLogEvent("Request update for MainForm.textLabel2");
    sprintf(TextLabel2.string,"%s%d","Update calls: ",++calls);
    TextLabel2.redrawFlags |= WF_REDRAW;
}
*/
