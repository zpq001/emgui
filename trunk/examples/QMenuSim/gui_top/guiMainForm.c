/**********************************************************
    Module guiMainForm




**********************************************************/

#include <stdio.h>      // due to printf
#include <stdint.h>

#include "guiConfig.h"

#include "guiFonts.h"
#include "guiGraphHAL.h"
#include "guiGraphPrimitives.h"
#include "guiGraphWidgets.h"

#include "guiCore.h"
#include "guiCoreTimers.h"
#include "guiCoreMemory.h"
#include "guiEvents.h"
#include "guiWidgets.h"
#include "guiTextLabel.h"
#include "guiButton.h"
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
static uint8_t button_onPressed(void *sender, guiEvent_t *event);
//static uint8_t textLabel_onFocusChanged(void *sender, guiEvent_t event);
//static uint8_t textLabel_onButtonEvent(void *sender, guiEvent_t event);


//----------- GUI Form  -----------//
guiPanel_t     guiMainForm;

//--------- Form elements ---------//
static guiTextLabel_t textLabel_time;
static guiButton_t button1;
static guiButton_t button2;



void guiMainForm_Initialize(void)
{
    // Initialize form
    guiPanel_Initialize(&guiMainForm, 0);   // Root has no parent
    guiCore_AllocateWidgetCollection((guiGenericContainer_t *)&guiMainForm, 10);
    guiMainForm.processEvent = guiMainForm_ProcessEvents;
    guiMainForm.isVisible = 1;
    guiMainForm.redrawRequired = 1;
    guiMainForm.redrawForced = 1;
    guiMainForm.x = 0;
    guiMainForm.y = 0;
    guiMainForm.width = 320;
    guiMainForm.height = 240;

    // Text label for time display
    guiTextLabel_Initialize(&textLabel_time, 0);
    guiCore_AddWidgetToCollection((guiGenericWidget_t *)&textLabel_time, (guiGenericContainer_t *)&guiMainForm);
    textLabel_time.x = guiMainForm.width - 80;
    textLabel_time.y = guiMainForm.height - 22;
    textLabel_time.width = 60;
    textLabel_time.height = 16;
    textLabel_time.text = guiCore_calloc(20);
    textLabel_time.font = &font_6x8_mono;
    //textLabel_time.acceptFocusByTab = 1;

    // Setup button1
    guiButton_Initialize(&button1, 0);
    guiCore_AddWidgetToCollection((guiGenericWidget_t *)&button1, (guiGenericContainer_t *)&guiMainForm);
    button1.x = 5;
    button1.y = guiMainForm.height - 22;
    button1.width = 50;
    button1.height = 18;
    button1.text = "Panel 1";
    button1.font = &font_h10;
    button1.tabIndex = 15;
    guiCore_AllocateHandlers((guiGenericWidget_t *)&button1, 2);
    guiCore_AddHandler((guiGenericWidget_t *)&button1, BUTTON_PRESSED_CHANGED, button_onPressed);

    // Setup button2
    guiButton_Initialize(&button2, 0);
    guiCore_AddWidgetToCollection((guiGenericWidget_t *)&button2, (guiGenericContainer_t *)&guiMainForm);
    button2.x = 60;
    button2.y = guiMainForm.height - 22;
    button2.width = 50;
    button2.height = 18;
    button2.text = "Panel 2";
    button2.font = &font_h10;
    button2.tabIndex = 16;
    button2.handlers.count = button1.handlers.count;            // Handlers are shared
    button2.handlers.elements = button1.handlers.elements;

    // Toggle buttons
    button1.isToggle = 1;
    button1.isPressOnly = 1;
    button2.isToggle = 1;
    button2.isPressOnly = 1;

    button1.isPressed = 1;

    // Initialize other
    guiPanel1_Initialize();
    guiPanel2_Initialize();

    // Add other widgets
    guiCore_AddWidgetToCollection((guiGenericWidget_t *)&guiPanel1, (guiGenericContainer_t *)&guiMainForm);
    guiCore_AddWidgetToCollection((guiGenericWidget_t *)&guiPanel2, (guiGenericContainer_t *)&guiMainForm);

}


static uint8_t guiMainForm_ProcessEvents(struct guiGenericWidget_t *widget, guiEvent_t event)
{
    // Process GUI messages - focus, draw, etc
    switch(event.type)
    {
          case GUI_EVENT_INIT:
            guiCore_InitTimer(TMR_TIME_UPDATE, 1, 0, (guiGenericWidget_t *)&guiMainForm);
            guiCore_StartTimer(TMR_TIME_UPDATE, 1);
            guiCore_AcceptFocusedState(&guiMainForm, 1);
            break;
          case GUI_EVENT_TIMER:
            sprintf(textLabel_time.text, "%2d:%02d:%02d", timeHours, timeMinutes, timeSeconds);
            textLabel_time.redrawForced = 1;
            textLabel_time.redrawRequired = 1;
            break;
          case GUI_EVENT_DRAW:
            // Check if full redraw is required
            guiGraph_DrawPanel(&guiMainForm);
            // Draw static elemens
            if (guiMainForm.redrawForced)
            {
                LCD_SetLineStyle(LINE_STYLE_SOLID);
                LCD_SetPenColor(colorPalette[COLOR_INDEX_3DFRAME_DARK1]);
                LCD_DrawHorLine(3,guiMainForm.height - 25,guiMainForm.width - 6);
            }
            // Reset flags
            guiMainForm.redrawFocus = 0;
            guiMainForm.redrawRequired = 0;
            break;
        case GUI_EVENT_FOCUS:
            guiCore_AcceptFocusedState(&guiMainForm, 1);
            guiCore_SetFocusOnNextWidget((guiGenericContainer_t *)&guiMainForm, 1, INVOKE_QUEUED);
            break;
        case GUI_EVENT_UNFOCUS:
            guiCore_AcceptFocusedState(&guiMainForm, 0);
            guiMainForm.keepTouch = 0;
            break;
/*        case GUI_EVENT_ENCODER:
            if ((int16_t)event.lparam < 0)
                guiCore_SetFocusOnNextWidget((guiGenericContainer_t *)&guiMainForm,-1);
            else if ((int16_t)event.lparam > 0)
                guiCore_SetFocusOnNextWidget((guiGenericContainer_t *)&guiMainForm,1);
            break; */
        case GUI_EVENT_KEY:
            if (event.spec == GUI_KEY_EVENT_DOWN)
            {
                if (event.payload.params.lparam == GUI_KEY_LEFT)
                {
                    guiCore_SetFocusOnNextWidget((guiGenericContainer_t *)&guiMainForm, -1, INVOKE_QUEUED);
                }
                else if (event.payload.params.lparam == GUI_KEY_RIGHT)
                {
                    guiCore_SetFocusOnNextWidget((guiGenericContainer_t *)&guiMainForm, 1, INVOKE_QUEUED);
                }
                else if (event.payload.params.lparam == GUI_KEY_ESC)
                {
                    // Keep focus on first button
                    guiCore_SetFocusOn((guiGenericWidget_t *)&guiMainForm, INVOKE_QUEUED);
                }
            }
            break;
         case GUI_EVENT_TOUCH:
            // Call base container handler
            guiPanel_ProcessEvent((guiGenericWidget_t *)&guiMainForm, event);
            break;
    }
    return GUI_EVENT_ACCEPTED;
}



static uint8_t button_onPressed(void *sender, guiEvent_t *event)
{
    guiButton_t *button = (guiButton_t *)sender;

    if (button->isPressed)
    {
        if (button == &button1)
        {
            guiButton_SetPressed(&button2, 0);
            if (guiPanel1.isVisible == 0)
            {
                guiCore_SetVisibleByTag(&guiMainForm.widgets, 20, 30, HIDE_IN_RANGE, INVOKE_QUEUED);
                guiCore_SetVisible((guiGenericWidget_t *)&guiPanel1, WIDGET_VISIBLE, INVOKE_QUEUED);
                //guiCore_SetVisibleExclusively((guiGenericWidget_t *)&guiPanel1);
                //guiCore_RequestFocusChange((guiGenericWidget_t *)&guiPanel1);
            }
        }
        else if (button == &button2)
        {
            guiButton_SetPressed(&button1, 0);
            if (guiPanel2.isVisible == 0)
            {
                guiCore_SetVisibleByTag(&guiMainForm.widgets, 20, 30, HIDE_IN_RANGE, INVOKE_QUEUED);
                guiCore_SetVisible((guiGenericWidget_t *)&guiPanel2, WIDGET_VISIBLE, INVOKE_QUEUED);
                //guiCore_SetVisibleExclusively((guiGenericWidget_t *)&guiPanel2);
                //guiCore_RequestFocusChange((guiGenericWidget_t *)&guiPanel2);
            }
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
            //guiCore_AcceptVisibleStateByTag(&guiMainForm.widgets, 10,20,HIDE_IN_RANGE);
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

