/**********************************************************
    Module button


    State flow:


    unfocused, unpressed      [touch press inside button]     ->    focused, pressed  (set_focus, press, accept)
                              [touch press outside button]    ->    decline
    focused,   unpressed      [touch press inside button]     ->    focused, pressed  (press, accept)
    focused,   pressed        [touch release]                 ->    focused, unpressed (release, accept)
    focused,   pressed        [touch move]                    ->    accept




**********************************************************/

#include <stdint.h>
#include "guiEvents.h"
#include "guiCore.h"
#include "guiWidgets.h"
#include "guiButton.h"
#include "guiFonts.h"
#include "guiGraphPrimitives.h"
#include "guiGraphWidgets.h"


typedef struct {
    uint8_t setVisible : 1;
    uint8_t setNotVisible : 1;
    uint8_t setFocused : 1;
    uint8_t setUnfocused : 1;
    uint8_t setPressed : 1;
    uint8_t setReleased : 1;
    uint8_t callClickedHandler : 1;


} btn_proc_flags_t;

static btn_proc_flags_t f;




static uint8_t guiButton_ProcessEvent(guiGenericWidget_t *widget, guiEvent_t event)
{
    guiButton_t *button = (guiButton_t *)widget;
    uint8_t processResult = GUI_EVENT_ACCEPTED;
    int16_t x,y;
    uint8_t touchState;
    uint8_t touchInsideWidget;

    // Clear all flags
    f.setVisible = 0;
    f.setNotVisible = 0;
    f.setFocused = 0;
    f.setUnfocused = 0;
    f.setPressed = 0;
    f.setReleased = 0;
    f.callClickedHandler = 0;

    switch (event.type)
    {
        case GUI_EVENT_DRAW:
            // Check visibility and redraw required flag
            if ((button->isVisible == 0) || (button->redrawRequired == 0))
                break;
            // Check if full redraw is required
            if (button->redrawForced)
            {
                // Widget must be fully redrawn - set all flags
                button->redrawFlags = BUTTON_REDRAW_FOCUS |
                                      BUTTON_REDRAW_STATE |
                                      BUTTON_REDRAW_BACKGROUND;
            }
            guiGraph_DrawButton(button);
            event.type = GUI_ON_DRAW;
            guiCore_CallEventHandler(widget, &event);
            // Reset flags
            button->redrawFlags = 0;
            button->redrawRequired = 0;
            break;
        case GUI_EVENT_FOCUS:
            if (button->isFocused == 0)
                f.setFocused = 1;
            break;
        case GUI_EVENT_UNFOCUS:
            if (button->isFocused)
            {
                f.setUnfocused = 1;
                button->keepTouch = 0;
                if (button->isPressed)
                    f.setReleased = 1;
            }
            break;
        case GUI_EVENT_SHOW:
            if (button->isVisible == 0)
                f.setVisible = 1;
            break;
        case GUI_EVENT_HIDE:
            if (button->isVisible)
                f.setNotVisible = 1;
            break;
        case GUI_EVENT_KEY: //GUI_EVENT_BUTTONS_ENCODER:
            // Check focused, visible, etc
        /*    if (((guiEventArgButtons_t *)event.args)->buttonCode & GUI_BTN_OK)
            {
                if (button->isPressed == 0)
                    f.setPressed = 1;
                else
                    f.setReleased = 1;
            }
            else
            {
                // Widget cannot process incoming event. Try to find a handler.
                processResult = guiCore_CallEventHandler(widget, event);
            } */
            processResult = GUI_EVENT_DECLINE;
            break;
        case GUI_EVENT_TOUCH:
            // Convert coordinates to widget's relative
            x = (int16_t)event.lparam;
            y = (int16_t)event.hparam;
            guiCore_ConvertToRelativeXY(widget,&x, &y);
            touchState = (int16_t)event.spec;
            touchInsideWidget = (guiCore_GetWidgetAtXY(widget,x,y)) ? 1 : 0;

            if (button->keepTouch)
            {
                if (touchState == TOUCH_RELEASE)
                {
                    if (button->isPressed)
                        f.setReleased = 1;
                    if (touchInsideWidget)
                        f.callClickedHandler = 1;
                    button->keepTouch = 0;
                }
                else    // TOUCH_MOVE
                {
                    if ((touchInsideWidget == 0) && (button->isPressed))
                        f.setReleased = 1;      // Moved out of widget borders
                    else if ((touchInsideWidget) && (button->isPressed == 0))
                        f.setPressed = 1;       // Moved into widget borders
                }
            }
            else //if (touchState == TOUCH_PRESS)
            {
                // Check if touch point is inside the widget
                if (touchInsideWidget)
                {
                    if (button->isFocused == 0)
                        f.setFocused = 1;
                    f.setPressed = 1;
                    button->keepTouch = 1;
                }
                else
                {
                    processResult = GUI_EVENT_DECLINE;
                }
            }
            break;
        default:
            // Widget cannot process incoming event. Try to find a handler.
            processResult = guiCore_CallEventHandler(widget, &event);
    }



    //-------------------------------//
    //-------------------------------//


    // Focus change process
    if ((f.setFocused) || (f.setUnfocused))
    {
        if (f.setFocused)
        {
            button->isFocused = 1;
            guiCore_AcceptFocus(widget);
        }
        else
            button->isFocused = 0;
        button->redrawFlags |= BUTTON_REDRAW_FOCUS;
        button->redrawRequired = 1;
        event.type = GUI_ON_FOCUS_CHANGED;
        guiCore_CallEventHandler(widget, &event);
    }

    // Visible change process
    if ((f.setVisible) || (f.setNotVisible))
    {
        if (f.setVisible)
        {
            button->isVisible = 1;
            button->redrawForced = 1;   // Widget must be fully redrawn - set all flags
        }
        else
        {
            button->isVisible = 0;
            guiCore_InvalidateRect(widget,button->x,button->y,
                  button->x + button->width - 1, button->y + button->height - 1);
        }

        event.type = GUI_ON_VISIBLE_CHANGED;
        guiCore_CallEventHandler(widget, &event);
    }

    // Pressed change
    if ((f.setPressed) || (f.setReleased))
    {
        if (f.setPressed)
        {
            button->isPressed = 1;
            button->redrawFlags |= BUTTON_REDRAW_STATE;
            button->redrawRequired = 1;
        }
        else
        {
            button->isPressed = 0;
            button->redrawFlags |= BUTTON_REDRAW_STATE;
            button->redrawRequired = 1;
        }

        event.type = BUTTON_PRESSED_CHANGED;
        guiCore_CallEventHandler(widget, &event);
    }

    // Handlers
    if (f.callClickedHandler)
    {
        event.type = BUTTON_CLICKED;
        guiCore_CallEventHandler(widget, &event);
    }



    return processResult;
}




void guiButton_Initialize(guiButton_t *button, guiGenericWidget_t *parent)
{
    button->parent = parent;
    button->acceptFocus = 0;
    button->acceptFocusByTab = 1;
    button->acceptTouch = 1;
    button->isContainer = 0;
    button->isFocused = 0;
    button->isVisible = 1;
    button->redrawForced = 0;
    button->redrawRequired = 0;
    button->tag = 0;
    button->tabIndex = 0;
    button->processEvent = guiButton_ProcessEvent;
    button->handlers.count = 0;
    button->keepTouch = 0;

    button->redrawFlags = 0;
    button->x = 0;
    button->y = 0;
    button->width = 40;
    button->height = 15;
    button->textAlignment = ALIGN_CENTER;
    button->font = &font_6x8_mono;
    button->text = 0;
    button->isPressed = 0;
}


void guibutton_SetRedrawFlags(guiButton_t *button, uint8_t flags)
{
    if (flags)
    {
        button->redrawFlags |= flags;
        button->redrawRequired = 1;
    }
}

