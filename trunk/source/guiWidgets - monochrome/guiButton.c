/**********************************************************
    Module button


**********************************************************/

#include <stdint.h>         // using integer types
#include <string.h>         // using memset
#include "guiEvents.h"
#include "guiCore.h"
#include "guiWidgets.h"
#include "guiButton.h"
#include "guiGraphWidgets.h"




//-------------------------------------------------------//
// Sets button pressed state
//
// This function does not perform any widget state checks
//      except isPressed state.
// Returns 1 if new state was applied. Otherwise returns 0.
//-------------------------------------------------------//
uint8_t guiButton_SetPressed(guiButton_t *button, uint8_t newPressedState)
{
    guiEvent_t event;
    if (button == 0) return 0;

    if (newPressedState)
    {
        // Press
        if (button->isPressed) return 0;
        button->isPressed = 1;
    }
    else
    {
        // Release
        if (button->isPressed == 0) return 0;
        button->isPressed = 0;
    }
    // Pressed state changed - call handler
    button->redrawPressedState = 1;
    button->redrawRequired = 1;
    if (button->handlers.count != 0)
    {
        event.type = BUTTON_PRESSED_CHANGED;
        guiCore_CallEventHandler((guiGenericWidget_t *)button, &event);
    }
    return 1;
}


//-------------------------------------------------------//
// Calls button click handler
//
//-------------------------------------------------------//
void guiButton_Click(guiButton_t *button)
{
    guiEvent_t event;
    if (button->handlers.count != 0)
    {
        event.type = BUTTON_CLICKED;
        guiCore_CallEventHandler((guiGenericWidget_t *)button, &event);
    }
}



//-------------------------------------------------------//
// Button key handler
//
// Returns GUI_EVENT_ACCEPTED if key is processed,
//         GUI_EVENT_DECLINE otherwise
//-------------------------------------------------------//
uint8_t guiButton_ProcessKey(guiButton_t *button, uint8_t key, uint8_t enableClick)
{
    if (key == BUTTON_KEY_PRESS)
    {
        if (button->isToggle)
        {
            if (button->isPressOnly)
                guiButton_SetPressed(button, 1);
            else
                guiButton_SetPressed(button, !button->isPressed);
        }
        else
        {
            guiButton_SetPressed(button, 1);
        }
    }
    else if (key == BUTTON_KEY_RELEASE)
    {
        if (button->isToggle == 0)
        {
            if ((guiButton_SetPressed(button,0)) && (enableClick))
                guiButton_Click(button);
        }
    }
    else
    {
        return GUI_EVENT_DECLINE;   // unknown key
    }
    return GUI_EVENT_ACCEPTED;
}



uint8_t guiButton_ProcessEvent(guiGenericWidget_t *widget, guiEvent_t event)
{
    guiButton_t *button = (guiButton_t *)widget;
    uint8_t processResult = GUI_EVENT_ACCEPTED;
    uint8_t key;
    widgetTouchState_t touch;

    switch (event.type)
    {
        case GUI_EVENT_DRAW:
            guiGraph_DrawButton(button);
            // Call handler
            guiCore_CallEventHandler(widget, &event);
            // Reset flags - redrawForced will be reset by core
            button->redrawFocus = 0;
            button->redrawPressedState = 0;
            button->redrawRequired = 0;
            break;
        case GUI_EVENT_FOCUS:
            if (BUTTON_ACCEPTS_FOCUS_EVENT(button))
                guiCore_SetFocused((guiGenericWidget_t *)button,1);
            else
                processResult = GUI_EVENT_DECLINE;      // Cannot accept focus
            break;
        case GUI_EVENT_UNFOCUS:
            guiCore_SetFocused((guiGenericWidget_t *)button,0);
            button->keepTouch = 0;
            if (button->isToggle == 0)
                guiButton_SetPressed(button,0);
            break;
        case GUI_EVENT_SHOW:
            guiCore_SetVisible((guiGenericWidget_t *)button, 1);
            break;
        case GUI_EVENT_HIDE:
            guiCore_SetVisible((guiGenericWidget_t *)button, 0);
            break;
        case GUI_EVENT_KEY:
            processResult = GUI_EVENT_DECLINE;
            if (BUTTON_ACCEPTS_KEY_EVENT(button))
            {
                if ((event.spec == GUI_KEY_EVENT_DOWN) && (event.lparam == GUI_KEY_OK))
                    key = BUTTON_KEY_PRESS;
                else if ((event.spec == GUI_KEY_EVENT_UP) && (event.lparam == GUI_KEY_OK))
                    key = BUTTON_KEY_RELEASE;
                else
                    key = 0;
                if (key != 0)
                    guiButton_ProcessKey(button, key, 1);
                // Call KEY event handler
                processResult |= guiCore_CallEventHandler(widget, &event);
            }
            break;
        case GUI_EVENT_TOUCH:
            if (BUTTON_ACCEPTS_TOUCH_EVENT(button))
            {
                // Convert touch event
                guiCore_DecodeWidgetTouchEvent((guiGenericWidget_t *)button, &event, &touch);
                // Check if widget holds the touch
                if (button->keepTouch)
                {
                    if (touch.state == TOUCH_RELEASE)
                    {
                        // Click will be generated if touch is inside button
                        guiButton_ProcessKey(button, BUTTON_KEY_RELEASE, touch.isInsideWidget);
                        button->keepTouch = 0;
                    }
                    else if (button->isToggle == 0)
                    {
                        // Track moving in/out of button borders
                        if ((touch.isInsideWidget == 0) && (button->isPressed))
                            guiButton_SetPressed(button, 0);      // Moved out of widget borders
                        else if ((touch.isInsideWidget) && (button->isPressed == 0))
                            guiButton_SetPressed(button, 1);       // Moved into widget borders
                    }
                }
                else if (touch.state != TOUCH_RELEASE)
                {
                    // New touch event to widget - it can either capture touch, or skip event to parent
                    if (touch.isInsideWidget)
                    {
                        // Capture
                        guiCore_SetFocused((guiGenericWidget_t *)button,1);
                        guiButton_ProcessKey(button, BUTTON_KEY_PRESS, 0);
                        button->keepTouch = 1;
                    }
                    else
                    {
                        // Skip
                        processResult = GUI_EVENT_DECLINE;
                        break;
                    }
                }
                // Call touch handler - return value is ignored
                event.type = GUI_ON_TOUCH_EVENT;
                event.spec = touch.state;
                event.lparam = (uint16_t)touch.x;
                event.hparam = (uint16_t)touch.y;
                guiCore_CallEventHandler(widget, &event);
            }
            else
            {
                processResult = GUI_EVENT_DECLINE;      // Cannot process touch event
            }
            break;
        default:
            // Widget cannot process incoming event. Try to find a handler.
            processResult = guiCore_CallEventHandler(widget, &event);
    }


    return processResult;
}


/*
                if ((touch.state == TOUCH_PRESS) || (touch.state == TOUCH_MOVE))
                {
                    if (button->keepTouch)
                    {
                        // Track moving in/out of button borders
                        if ((touch.isInsideWidget == 0) && (button->isPressed))
                            guiButton_SetPressed(button, 0);      // Moved out of widget borders
                        else if ((touch.isInsideWidget) && (button->isPressed == 0))
                            guiButton_SetPressed(button, 1);       // Moved into widget borders
                    }
                    else
                    {
                        // Check if widget should react
                        if (touch.isInsideWidget)
                        {
                            guiCore_SetFocused((guiGenericWidget_t *)button,1);
                            guiButton_SetPressed(button, 1);
                            button->keepTouch = 1;
                        }
                        else
                        {
                            processResult = GUI_EVENT_DECLINE;
                            break;
                        }
                    }
                }
                else if (touch.state == TOUCH_RELEASE)
                {
                    if (button->keepTouch)
                    {
                        guiButton_SetPressed(button, 0);
                        if (touch.isInsideWidget)
                            guiButton_Click(button);
                        button->keepTouch = 0;
                    }
                    else
                    {
                        // do smth
                    }
                }

                */


//-------------------------------------------------------//
// Default initialization
//
//-------------------------------------------------------//
void guiButton_Initialize(guiButton_t *button, guiGenericWidget_t *parent)
{
    memset(button, 0, sizeof(*button));
    button->type = WT_BUTTON;
    button->parent = parent;
    button->acceptFocusByTab = 1;
    button->acceptTouch = 1;
    button->isVisible = 1;
    button->showFocus = 1;
    button->processEvent = guiButton_ProcessEvent;
    button->textAlignment = ALIGN_CENTER;
}



