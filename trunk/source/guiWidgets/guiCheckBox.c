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




void guiCheckbox_SetFocused(guiCheckBox_t *checkbox, uint8_t newFocusedState)
{
    guiEvent_t event;
    if (checkbox == 0) return;

    if (newFocusedState)
    {
        // Set focus on panel
        if (checkbox->isFocused) return;
        checkbox->isFocused = 1;
        guiCore_AcceptFocus((guiGenericWidget_t *)checkbox);
    }
    else
    {
        // Focus was removed
        if (checkbox->isFocused == 0) return;
        checkbox->isFocused = 0;
    }
    // Focused state changed - call handler
    checkbox->redrawFlags |= CHECKBOX_REDRAW_FOCUS;
    checkbox->redrawRequired = 1;
    event.type = GUI_ON_FOCUS_CHANGED;
    event.args = 0;
    guiCore_CallEventHandler((guiGenericWidget_t *)checkbox, event);
}


void guiCheckbox_SetChecked(guiCheckBox_t *checkBox, uint8_t newCheckedState)
{
    guiEvent_t event;
    if (checkBox == 0) return;

    if (newCheckedState)
    {
        // Check
        if (checkBox->isChecked) return;
        checkBox->isChecked = 1;
    }
    else
    {
        // Uncheck
        if (checkBox->isChecked == 0) return;
        checkBox->isChecked = 0;
    }
    // Checked state changed - call handler
    checkBox->redrawFlags |= CHECKBOX_REDRAW_STATE;
    checkBox->redrawRequired = 1;
    event.type = CHECKBOX_CHECKED_CHANGED;
    event.args = 0;
    guiCore_CallEventHandler((guiGenericWidget_t *)checkBox, event);
}


static uint8_t guiCheckBox_ProcessEvent(guiGenericWidget_t *widget, guiEvent_t event)
{
    guiCheckBox_t *checkBox = (guiCheckBox_t *)widget;
    int16_t x,y;
    uint8_t touchState;
    uint8_t touchInsideWidget;
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
        case GUI_EVENT_TOUCH:
            // Convert coordinates to widget's relative
            x = ((guiEventTouch_t *)event.args)->x;
            y = ((guiEventTouch_t *)event.args)->y;
            guiCore_ConvertToRelativeXY(widget,&x, &y);
            touchState = ((guiEventTouch_t *)event.args)->state;
            touchInsideWidget = (guiCore_GetWidgetAtXY(widget,x,y)) ? 1 : 0;

            if (checkBox->keepTouch)
            {
                if (touchState == TOUCH_RELEASE)
                {
                    checkBox->keepTouch = 0;
                }
            }
            else
            {
                // Check if touch point is inside the widget
                if (touchInsideWidget)
                {
                    if (checkBox->isFocused == 0)
                        guiCheckbox_SetFocused(checkBox,1);
                    guiCheckbox_SetChecked(checkBox, !checkBox->isChecked);
                    checkBox->keepTouch = 1;
                }
                else
                {
                    processResult = GUI_EVENT_DECLINE;
                }
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
    checkBox->acceptTouch = 0;
    checkBox->isContainer = 0;
    checkBox->isFocused = 0;
    checkBox->isVisible = 1;
    checkBox->redrawForced = 0;
    checkBox->redrawRequired = 0;
    checkBox->tag = 0;
    checkBox->tabIndex = 0;
    checkBox->processEvent = guiCheckBox_ProcessEvent;
    checkBox->handlers.count = 0;
    checkBox->keepTouch = 0;

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

/*
void guiButton_SetRedrawFlags(guiButton_t *button, uint8_t flags)
{
    if (flags)
    {
        checkBox->redrawFlags |= flags;
        checkBox->redrawRequired = 1;
    }
}
*/
