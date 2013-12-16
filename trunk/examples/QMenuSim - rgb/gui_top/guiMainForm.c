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
#include "guiPanel.h"


// Other forms - in order to switch between them
#include "guiMainForm.h"
#include "guiPanel1.h"
#include "guiPanel2.h"

extern void guiLogEvent(char *string);
extern uint8_t timeHours;
extern uint8_t timeMinutes;
extern uint8_t timeSeconds;


static uint8_t guiMainForm_ProcessEvents(guiGenericWidget_t *widget, guiEvent_t event);
static uint8_t button_onClicked(void *sender, guiEvent_t event);
//static uint8_t textLabel_onFocusChanged(void *sender, guiEvent_t event);
//static uint8_t textLabel_onButtonEvent(void *sender, guiEvent_t event);


//--------- Form elements ---------//
static guiTextLabel_t textLabel_time;
static char textLabel_time_data[50];

static guiButton_t button1;
static guiButton_t button2;
static guiWidgetHandler_t button_handlers[1];

//----------- GUI Form  -----------//
#define MAIN_FORM_ELEMENTS_COUNT 7
guiPanel_t     guiMainForm;
static void *guiMainFormElements[MAIN_FORM_ELEMENTS_COUNT];


void guiMainForm_Initialize(void)
{
    // Initialize form
    guiPanel_Initialize(&guiMainForm, 0);   // Root has no parent
    guiMainForm.processEvent = guiMainForm_ProcessEvents;
    guiMainForm.widgets.count = MAIN_FORM_ELEMENTS_COUNT;
    guiMainForm.widgets.elements = guiMainFormElements;
    guiMainForm.widgets.elements[0] = &textLabel_time;
    guiMainForm.widgets.elements[1] = &button1;
    guiMainForm.widgets.elements[2] = &button2;
    guiMainForm.widgets.elements[3] = &guiPanel1;
    guiMainForm.widgets.elements[4] = &guiPanel2;
    guiMainForm.widgets.elements[5] = 0;
    guiMainForm.widgets.elements[6] = 0;

    guiMainForm.isVisible = 1;
    guiMainForm.redrawRequired = 1;
    guiMainForm.redrawForced = 1;
    guiMainForm.x = 0;
    guiMainForm.y = 0;
    guiMainForm.width = 300;
    guiMainForm.height = 200;

    guiMainForm.showFocus = 0;
    //guiMainForm.focusFallsThrough = 1;

    // Initialize text label for time display
    guiTextLabel_Initialize(&textLabel_time, (guiGenericWidget_t *)&guiMainForm);
    textLabel_time.tabIndex = 0;
    textLabel_time.acceptFocus = 0;
    textLabel_time.acceptFocusByTab = 0;
    textLabel_time.x = guiMainForm.width - 80;
    textLabel_time.y = guiMainForm.height - 24;
    textLabel_time.width = 60;
    textLabel_time.height = 20;
    textLabel_time.alignment = ALIGN_CENTER;
    textLabel_time.text = textLabel_time_data;
    textLabel_time.font = &font_6x8_mono;

    // Setup button1
    guiButton_Initialize(&button1,  (guiGenericWidget_t *)&guiMainForm);
    button1.x = 5;
    button1.y = guiMainForm.height - 22;
    button1.width = 50;
    button1.height = 18;
    button1.text = "Panel 1";
    button1.font = &font_h10;
    button1.tabIndex = 15;
    button1.handlers.elements = button_handlers;
    button1.handlers.count = 1;

    // Setup button2
    guiButton_Initialize(&button2,  (guiGenericWidget_t *)&guiMainForm);
    button2.x = 60;
    button2.y = guiMainForm.height - 22;
    button2.width = 50;
    button2.height = 18;
    button2.text = "Panel 2";
    button2.font = &font_h10;
    button2.tabIndex = 16;
    button2.handlers.elements = button_handlers;
    button2.handlers.count = 1;

    // Setup button handlers
    button_handlers[0].eventType = BUTTON_CLICKED;
    button_handlers[0].handler = button_onClicked;


    guiPanel1_Initialize((guiGenericWidget_t *)&guiMainForm);
    guiPanel2_Initialize((guiGenericWidget_t *)&guiMainForm);
}


static uint8_t guiMainForm_ProcessEvents(struct guiGenericWidget_t *widget, guiEvent_t event)
{
    //int16_t x,y;
    guiEventArgButtons_t *argButtons;
    //guiGenericWidget_t *w;
    //uint8_t touchState;

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
            guiGraph_DrawPanel(&guiMainForm);
            // Draw static elemens
            if (guiMainForm.redrawFlags & (FORM_REDRAW_BACKGROUND | FORM_REDRAW_FOCUS))
            {
                LCD_SetLineStyle(LINE_STYLE_SOLID);
                LCD_SetPenColor(colorPalette[COLOR_INDEX_3DFRAME_DARK1]);
                LCD_DrawHorLine(3,guiMainForm.height - 25,guiMainForm.width - 6);
            }
            // Reset flags
            guiMainForm.redrawFlags = 0;
            guiMainForm.redrawRequired = 0;
            break;
        case GUI_EVENT_FOCUS:
            guiPanel_SetFocused((guiPanel_t *)&guiMainForm, 1);
            guiCore_RequestFocusNextWidget((guiGenericContainer_t *)&guiMainForm,1);
            break;
        case GUI_EVENT_UNFOCUS:
            guiPanel_SetFocused((guiPanel_t *)&guiMainForm, 0);
            break;
        case GUI_EVENT_BUTTONS_ENCODER:
            argButtons = (guiEventArgButtons_t *)event.args;
            if (argButtons->buttonCode & GUI_BTN_LEFT)
            {
                guiCore_RequestFocusNextWidget((guiGenericContainer_t *)&guiMainForm,-1);
            }
            else if (argButtons->buttonCode & GUI_BTN_RIGHT)
            {
                guiCore_RequestFocusNextWidget((guiGenericContainer_t *)&guiMainForm,1);
            }
            else if (argButtons->buttonCode & GUI_BTN_ESC)
            {
                // Keep focus on first button
                guiCore_RequestFocusChange((guiGenericWidget_t *)&guiMainForm);
            }
            break;
         case GUI_EVENT_TOUCH:
            // Call base container handler
            guiPanel_ProcessEvent((guiGenericWidget_t *)&guiMainForm, event);
            break;
    }
    return GUI_EVENT_ACCEPTED;
}



static uint8_t button_onClicked(void *sender, guiEvent_t event)
{
    guiLogEvent("Button clicked");
    guiButton_t *button = (guiButton_t *)sender;

    if (button == &button1)
    {
        if (guiPanel1.isVisible == 0)
        {
            guiCore_SetVisibleByTag(&guiMainForm.widgets,20,30,ITEMS_IN_RANGE_ARE_INVISIBLE);
            guiCore_AddMessageToQueue((guiGenericWidget_t *)&guiPanel1, guiEvent_SHOW);
            //guiCore_RequestFocusChange((guiGenericWidget_t *)&guiPanel1);
        }
    }
    else if (button == &button2)
    {
        if (guiPanel2.isVisible == 0)
        {
            guiCore_SetVisibleByTag(&guiMainForm.widgets,20,30,ITEMS_IN_RANGE_ARE_INVISIBLE);
            guiCore_AddMessageToQueue((guiGenericWidget_t *)&guiPanel2, guiEvent_SHOW);
            //guiCore_RequestFocusChange((guiGenericWidget_t *)&guiPanel2);
        }
    }

    return GUI_EVENT_ACCEPTED;
}


/*
static uint8_t button1_onPressedChanged(void *sender, guiEvent_t event)
{
    if (button1.isPressed)
        guiLogEvent("Button 1 pressed");
    else
        guiLogEvent("Button 1 released");
}

static uint8_t button1_onClicked(void *sender, guiEvent_t event)
{
    guiLogEvent("Button 1 clicked");
}
*/

/*
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
*/

