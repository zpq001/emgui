/**********************************************************
    Module button




**********************************************************/

#include <stdint.h>
#include "guiEvents.h"
#include "guiCore.h"
#include "guiWidgets.h"
#include "guiButton.h"
#include "guiFonts.h"
#include "guiGraphPrimitives.h"
#include "guiGraphWidgets.h"




static uint8_t guiButton_ProcessEvent(guiGenericWidget_t *widget, guiEvent_t event)
{
    guiButton_t *button = (guiButton_t *)widget;
    uint8_t processResult = GUI_EVENT_ACCEPTED;

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
            guiCore_CallEventHandler(widget, event);
            // Reset flags
            button->redrawFlags = 0;
            button->redrawRequired = 0;
            break;
        case GUI_EVENT_FOCUS:
            button->isFocused = 1;
            guiCore_AcceptFocus(widget);
            goto lbl_focus;
        case GUI_EVENT_UNFOCUS:
            button->isFocused = 0;
lbl_focus:
            button->redrawFlags |= BUTTON_REDRAW_FOCUS;
            button->redrawRequired = 1;
            event.type = GUI_ON_FOCUS_CHANGED;
            guiCore_CallEventHandler(widget, event);
            break;
        case GUI_EVENT_SHOW:
            // Check if widget is not visible
            if (button->isVisible == 0)
            {
                button->isVisible = 1;
                // Widget must be fully redrawn - set all flags
                button->redrawForced = 1;
                event.type = GUI_ON_VISIBLE_CHANGED;
                guiCore_CallEventHandler(widget, event);
            }
            break;
        case GUI_EVENT_HIDE:
            // Check if widget is visible
            if (button->isVisible)
            {
                button->isVisible = 0;
                guiCore_InvalidateRect(widget,button->x,button->y,
                      button->x + button->width - 1, button->y + button->height - 1);
                event.type = GUI_ON_VISIBLE_CHANGED;
                guiCore_CallEventHandler(widget, event);
            }
            break;
        case GUI_EVENT_BUTTONS_ENCODER:
            // Check focused, visible, etc
            if (((guiEventArgButtons_t *)event.args)->buttonCode & GUI_BTN_OK)
            {
                button->isPressed = !button->isPressed;
                button->redrawFlags = BUTTON_REDRAW_STATE;
                button->redrawRequired = 1;
                event.type = BUTTON_PRESSED_CHANGED;
                guiCore_CallEventHandler(widget, event);
            }
            else
            {
                // Widget cannot process incoming event. Try to find a handler.
                processResult = guiCore_CallEventHandler(widget, event);
            }
            break;
        default:
            // Widget cannot process incoming event. Try to find a handler.
            processResult = guiCore_CallEventHandler(widget, event);
    }
    return processResult;
}




void guiButton_Initialize(guiButton_t *button, guiGenericWidget_t *parent)
{
    button->parent = parent;
    button->acceptFocus = 0;
    button->acceptFocusByTab = 1;
    button->isContainer = 0;
    button->isFocused = 0;
    button->isVisible = 1;
    button->redrawForced = 0;
    button->redrawRequired = 0;
    button->tag = 0;
    button->tabIndex = 0;
    button->processEvent = guiButton_ProcessEvent;
    button->handlers.count = 0;

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

