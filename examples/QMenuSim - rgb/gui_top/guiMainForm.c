/**********************************************************
    Module guiMainForm




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
#include "guiForm.h"


// Other forms - in order to switch between them
#include "guiMainForm.h"

extern void guiLogEvent(char *string);
extern uint8_t timeHours;
extern uint8_t timeMinutes;
extern uint8_t timeSeconds;


static uint8_t guiMainForm_ProcessEvents(guiGenericWidget_t *widget, guiEvent_t event);
static uint8_t textLabel_onFocusChanged(void *sender, guiEvent_t event);
static uint8_t textLabel_onButtonEvent(void *sender, guiEvent_t event);


//--------- Form elements ---------//
static guiTextLabel_t textLabel1;
static guiTextLabel_t textLabel2;
static guiTextLabel_t textLabel3;
static guiTextLabel_t textLabel4;
static guiTextLabel_t textLabel_time;
static guiTextLabel_t textLabel_hint;
static char textLabel_time_data[50];
static guiWidgetHandler_t label_handlers[2];

static guiButton_t button1;


//----------- GUI Form  -----------//
#define MAIN_FORM_ELEMENTS_COUNT 7
guiForm_t     guiMainForm;
static void *guiMainFormElements[MAIN_FORM_ELEMENTS_COUNT];


void guiMainForm_Initialize(void)
{
    // Initialize form
    guiForm_Initialize(&guiMainForm);
    guiMainForm.processEvent = guiMainForm_ProcessEvents;
    guiMainForm.widgets.count = MAIN_FORM_ELEMENTS_COUNT;
    guiMainForm.widgets.elements = guiMainFormElements;
//    guiMainForm.widgets.elements[0] = 0;//&guiSubForm1;
    guiMainForm.widgets.elements[0] = &button1;
    guiMainForm.widgets.elements[1] = &textLabel_time;
    guiMainForm.widgets.elements[2] = &textLabel1;
    guiMainForm.widgets.elements[3] = &textLabel2;
    guiMainForm.widgets.elements[4] = &textLabel3;
    guiMainForm.widgets.elements[5] = &textLabel4;
    guiMainForm.widgets.elements[6] = &textLabel_hint;
    guiMainForm.isVisible = 1;
    guiMainForm.redrawRequired = 1;
    guiMainForm.redrawForced = 1;
    guiMainForm.x = 0;
    guiMainForm.y = 0;
    guiMainForm.width = 300;
    guiMainForm.height = 200;

    // Initialize text label for time display
    guiTextLabel_Initialize(&textLabel_time, (guiGenericWidget_t *)&guiMainForm);
    textLabel_time.tabIndex = 0;
    textLabel_time.acceptFocus = 0;
    textLabel_time.acceptFocusByTab = 0;
    textLabel_time.x = 128 + 50;
    textLabel_time.y = 112;
    textLabel_time.width = 70;
    textLabel_time.height = 14;
    textLabel_time.alignment = ALIGN_CENTER;
    textLabel_time.text = textLabel_time_data;
    textLabel_time.font = &font_6x8_mono;

    // Initialize text label for hint
    guiTextLabel_Initialize(&textLabel_hint, (guiGenericWidget_t *)&guiMainForm);
    textLabel_hint.tabIndex = 0;
    textLabel_hint.acceptFocus = 0;
    textLabel_hint.acceptFocusByTab = 0;
    textLabel_hint.x = 128 + 10;
    textLabel_hint.y = 10;
    textLabel_hint.width = 100;
    textLabel_hint.height = 14;
    textLabel_hint.alignment = ALIGN_CENTER;
    textLabel_hint.text = 0;
    textLabel_hint.font = &font_h10_bold;
    textLabel_hint.hasFrame = 1;
    textLabel_hint.tag = 10;

    // Initialize other labels
    guiTextLabel_Initialize(&textLabel1, (guiGenericWidget_t *)&guiMainForm);
    textLabel1.tabIndex = 10;
    textLabel1.acceptFocus = 0;
    textLabel1.acceptFocusByTab = 1;
    textLabel1.x = 20;
    textLabel1.y = 10;
    textLabel1.width = 70;
    textLabel1.height = 14;
    textLabel1.alignment = ALIGN_LEFT;
    textLabel1.text = "Form 1";
    textLabel1.font = &font_h10;
    textLabel1.handlers.count = 2;
    textLabel1.handlers.elements = label_handlers;
    textLabel1.tag = 11;

    guiTextLabel_Initialize(&textLabel2, (guiGenericWidget_t *)&guiMainForm);
    textLabel2.tabIndex = 11;
    textLabel2.acceptFocus = 0;
    textLabel2.acceptFocusByTab = 1;
    textLabel2.x = 20;
    textLabel2.y = 30;
    textLabel2.width = 70;
    textLabel2.height = 14;
    textLabel2.alignment = ALIGN_LEFT;
    textLabel2.text = "Form 2";
    textLabel2.font = &font_h10;
    textLabel2.handlers.count = 2;
    textLabel2.handlers.elements = label_handlers;
    textLabel2.tag = 12;

    guiTextLabel_Initialize(&textLabel3, (guiGenericWidget_t *)&guiMainForm);
    textLabel3.tabIndex = 12;
    textLabel3.acceptFocus = 0;
    textLabel3.acceptFocusByTab = 1;
    textLabel3.x = 20;
    textLabel3.y = 50;
    textLabel3.width = 70;
    textLabel3.height = 14;
    textLabel3.alignment = ALIGN_LEFT;
    textLabel3.text = "Form 3";
    textLabel3.font = &font_h10;
    textLabel3.handlers.count = 2;
    textLabel3.handlers.elements = label_handlers;
    textLabel3.tag = 13;

    guiTextLabel_Initialize(&textLabel4, (guiGenericWidget_t *)&guiMainForm);
    textLabel4.tabIndex = 13;
    textLabel4.acceptFocus = 0;
    textLabel4.acceptFocusByTab = 1;
    textLabel4.x = 20;
    textLabel4.y = 70;
    textLabel4.width = 70;
    textLabel4.height = 14;
    textLabel4.alignment = ALIGN_LEFT;
    textLabel4.text = "Form 4";
    textLabel4.font = &font_h10;
    textLabel4.handlers.count = 2;
    textLabel4.handlers.elements = label_handlers;
    textLabel4.tag = 14;

    label_handlers[0].eventType = GUI_ON_FOCUS_CHANGED;
    label_handlers[0].handler = textLabel_onFocusChanged;
    label_handlers[1].eventType = GUI_EVENT_BUTTONS_ENCODER;
    label_handlers[1].handler = textLabel_onButtonEvent;


    guiButton_Initialize(&button1,  (guiGenericWidget_t *)&guiMainForm);
    button1.x = 128 + 10;
    button1.y = 40;
    button1.width = 60;
    button1.height = 20;
    button1.text = "Hi there!";
    button1.font = &font_h10;
    button1.tabIndex = 15;

    // Prepare logic
    guiMainForm.widgets.focusedIndex = 2;
}


static uint8_t guiMainForm_ProcessEvents(struct guiGenericWidget_t *widget, guiEvent_t event)
{
    guiEventArgButtons_t *argButtons;
    // Process GUI messages - focus, draw, etc
    switch(event.type)
    {
          case GUI_EVENT_UPDATE:
            sprintf(textLabel_time.text, "%2d:%02d:%02d", timeHours, timeMinutes, timeSeconds);
            guiTextLabel_SetRedrawFlags(&textLabel_time, TEXT_LABEL_REDRAW_TEXT);
            break;
          case GUI_EVENT_DRAW:
            // Check if full redraw is required
            if (guiMainForm.redrawForced)
            {
                // Widget must be fully redrawn - set all flags
                guiMainForm.redrawFlags = FORM_REDRAW_FOCUS |
                                         FORM_REDRAW_BACKGROUND;
            }
            guiGraph_DrawForm(&guiMainForm);
            // Draw static elemens
            if (guiMainForm.redrawFlags & FORM_REDRAW_BACKGROUND)
            {
                //LCD_DrawHorLine(0,110,255);
            }
            // Reset flags
            guiMainForm.redrawFlags = 0;
            guiMainForm.redrawRequired = 0;
            break;
        case GUI_EVENT_FOCUS:
            guiCore_AcceptFocus((guiGenericWidget_t *)&guiMainForm);
            //guiCore_RequestFocusChange(guiMainForm.widgets.elements[guiMainForm.widgets.focusedIndex]);
            guiCore_RequestFocusNextWidget((guiGenericContainer_t *)&guiMainForm,1);
            break;
        case GUI_EVENT_UNFOCUS:
            // do smth
            break;

        case GUI_EVENT_BUTTONS_ENCODER:
            argButtons = (guiEventArgButtons_t *)event.args;
            if (argButtons->buttonCode & GUI_BTN_LEFT)
                guiCore_RequestFocusNextWidget((guiGenericContainer_t *)&guiMainForm,-1);
            else if (argButtons->buttonCode & GUI_BTN_RIGHT)
                guiCore_RequestFocusNextWidget((guiGenericContainer_t *)&guiMainForm,1);
            else if (argButtons->buttonCode & GUI_BTN_ESC)
            {
                //guiCore_AddMessageToQueue((guiGenericWidget_t *)&guiSubForm1,guiEvent_HIDE);
                //guiCore_SetVisibleByTag(&guiMainForm.widgets, 10,20,ITEMS_IN_RANGE_ARE_VISIBLE);
                guiCore_RequestFocusChange((guiGenericWidget_t *)&guiMainForm);
            }
            break;
    }
    return GUI_EVENT_ACCEPTED;
}




static uint8_t textLabel_onFocusChanged(void *sender, guiEvent_t event)
{
    guiGenericWidget_t *textLabel = (guiGenericWidget_t *)sender;
    if (textLabel->isFocused)
    {
        if (textLabel == (guiGenericWidget_t *)&textLabel1)
            textLabel_hint.text = "Focused label 1";
        else if (textLabel == (guiGenericWidget_t *)&textLabel2)
            textLabel_hint.text = "Focused label 2";
        else if (textLabel == (guiGenericWidget_t *)&textLabel3)
            textLabel_hint.text = "Focused label 3";
        else if (textLabel == (guiGenericWidget_t *)&textLabel4)
            textLabel_hint.text = "Focused label 4";
        else
            textLabel_hint.text = "Focused ???";

        guiTextLabel_SetRedrawFlags(&textLabel_hint, TEXT_LABEL_REDRAW_TEXT);
    }

    return GUI_EVENT_ACCEPTED;
}



static uint8_t textLabel_onButtonEvent(void *sender, guiEvent_t event)
{
    guiGenericWidget_t *textLabel = (guiGenericWidget_t *)sender;
    guiEventArgButtons_t *argButtons = (guiEventArgButtons_t *)event.args;

    if (argButtons->buttonCode & GUI_BTN_OK)
    {
        if (textLabel == (guiGenericWidget_t *)&textLabel1)
        {

        }
        else if (textLabel == (guiGenericWidget_t *)&textLabel2)
        {
            //guiCore_SetVisibleByTag(&guiMainForm.widgets, 10,20,ITEMS_IN_RANGE_ARE_INVISIBLE);
            //guiCore_AddMessageToQueue((guiGenericWidget_t *)&guiSubForm1,guiEvent_SHOW);
            //guiCore_RequestFocusChange((guiGenericWidget_t *)&guiSubForm1);
        }
        else if (textLabel == (guiGenericWidget_t *)&textLabel3)
        {

        }
        else //if (textLabel == (guiGenericWidget_t *)&textLabel4)
        {

        }
        return GUI_EVENT_ACCEPTED;
    }
    return GUI_EVENT_DECLINE;
}


