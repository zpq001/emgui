/**********************************************************
    Module checkBox




**********************************************************/

#include <stdint.h>
#include "guiEvents.h"
#include "guiCore.h"
#include "guiWidgets.h"
#include "guicheckBox.h"
#include "guiFonts.h"
#include "guiGraphPrimitives.h"
#include "guiGraphWidgets.h"




static uint8_t guiCheckBox_ProcessEvent(guiGenericWidget_t *widget, guiEvent_t event)
{
    guiCheckBox_t *checkBox = (guiCheckBox_t *)widget;
    uint8_t processResult = GUI_EVENT_ACCEPTED;

    switch (event.type)
    {
        case GUI_EVENT_DRAW:
            // Check visibility and redraw required flag
            if ((checkBox->isVisible == 0) || (checkBox->redrawRequired == 0))
                break;
            // Check if full redraw is required
            if (checkBox->redrawForced)
            {
                // Widget must be fully redrawn - set all flags
                checkBox->redrawFlags = CHECKBOX_REDRAW_FOCUS |
                                        CHECKBOX_REDRAW_STATE |
                                        CHECKBOX_REDRAW_BACKGROUND;
            }
            guiGraph_DrawCheckBox(checkBox);
            event.type = GUI_ON_DRAW;
            guiCore_CallEventHandler(widget, event);
            // Reset flags
            checkBox->redrawFlags = 0;
            checkBox->redrawRequired = 0;
            break;
        case GUI_EVENT_FOCUS:
            checkBox->isFocused = 1;
            guiCore_AcceptFocus(widget);
            goto lbl_focus;
        case GUI_EVENT_UNFOCUS:
            checkBox->isFocused = 0;
lbl_focus:
            checkBox->redrawFlags |= CHECKBOX_REDRAW_FOCUS;
            checkBox->redrawRequired = 1;
            event.type = GUI_ON_FOCUS_CHANGED;
            guiCore_CallEventHandler(widget, event);
            break;
        case GUI_EVENT_SHOW:
            // Check if widget is not visible
            if (checkBox->isVisible == 0)
            {
                checkBox->isVisible = 1;
                // Widget must be fully redrawn - set all flags
                checkBox->redrawFlags = CHECKBOX_REDRAW_FOCUS |
                                        CHECKBOX_REDRAW_STATE |
                                        CHECKBOX_REDRAW_BACKGROUND;
                event.type = GUI_ON_VISIBLE_CHANGED;
                guiCore_CallEventHandler(widget, event);
            }
            break;
        case GUI_EVENT_HIDE:
            // Check if widget is visible
            if (checkBox->isVisible)
            {
                checkBox->isVisible = 0;
                guiCore_InvalidateRect(widget,checkBox->x,checkBox->y,
                      checkBox->x + checkBox->width - 1, checkBox->y + checkBox->height - 1);
                event.type = GUI_ON_VISIBLE_CHANGED;
                guiCore_CallEventHandler(widget, event);
            }
            break;
        case GUI_EVENT_BUTTONS_ENCODER:
            // Check focused, visible, etc
            if (((guiEventArgButtons_t *)event.args)->buttonCode & GUI_BTN_OK)
            {
                checkBox->isChecked = !checkBox->isChecked;
                checkBox->redrawFlags = CHECKBOX_REDRAW_STATE;
                checkBox->redrawRequired = 1;
                event.type = CHECKBOX_CHECKED_CHANGED;
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




void guiCheckBox_Initialize(guiCheckBox_t *checkBox, guiGenericWidget_t *parent)
{
    checkBox->parent = parent;
    checkBox->acceptFocus = 0;
    checkBox->acceptFocusByTab = 0;
    checkBox->isContainer = 0;
    checkBox->isFocused = 0;
    checkBox->isVisible = 1;
    checkBox->redrawForced = 0;
    checkBox->redrawRequired = 0;
    checkBox->tag = 0;
    checkBox->tabIndex = 0;
    checkBox->processEvent = guiCheckBox_ProcessEvent;
    checkBox->handlers.count = 0;

    checkBox->redrawFlags = 0;
    checkBox->x = 0;
    checkBox->y = 0;
    checkBox->width = 40;
    checkBox->height = 15;
    checkBox->textAlignment = ALIGN_LEFT;
    checkBox->font = &font_6x8_mono;
    checkBox->text = 0;
    checkBox->hasFrame = 0;
    checkBox->isChecked = 0;
}


void guiCheckBox_SetRedrawFlags(guiCheckBox_t *checkBox, uint8_t flags)
{
    if (flags)
    {
        checkBox->redrawFlags |= flags;
        checkBox->redrawRequired = 1;
    }
}

