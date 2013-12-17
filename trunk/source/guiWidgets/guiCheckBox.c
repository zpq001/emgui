/**********************************************************
    Module checkBox




**********************************************************/

#include <stdint.h>
#include "guiEvents.h"
#include "guiCore.h"
#include "guiEventConverter.h"
#include "guiWidgets.h"
#include "guicheckBox.h"
#include "guiFonts.h"
#include "guiGraphPrimitives.h"
#include "guiGraphWidgets.h"



static widgetTouchState_t touch;



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
    guiCore_CallEventHandler((guiGenericWidget_t *)checkbox, &event);
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
    guiCore_CallEventHandler((guiGenericWidget_t *)checkBox, &event);
}


void guiCheckbox_SetVisible(guiCheckBox_t *checkBox, uint8_t newVisibleState)
{
    guiEvent_t event;
    if (checkBox == 0) return;

    if (newVisibleState)
    {
        // Show
        if (checkBox->isVisible) return;
        checkBox->isVisible = 1;
        checkBox->redrawForced = 1;
    }
    else
    {
        // Hide
        if (checkBox->isVisible == 0) return;
        checkBox->isVisible = 0;
        guiCore_InvalidateRect((guiGenericWidget_t *)checkBox,checkBox->x,checkBox->y,
              checkBox->x + checkBox->width - 1, checkBox->y + checkBox->height - 1);
    }
    // Visible state changed - call handler
    event.type = GUI_ON_VISIBLE_CHANGED;
    guiCore_CallEventHandler((guiGenericWidget_t *)checkBox, &event);
}



uint8_t guiCheckbox_DefaultKeyConverter(guiEvent_t *keyEvent)
{
    keyEvent->hparam = 0;
    if (keyEvent->spec == DEFAULT_KEY_EVENT_DOWN)
    {
        if (keyEvent->lparam == DEFAULT_KEY_OK)
            keyEvent->hparam = CHECKBOX_KEY_OK;
    }
    if (keyEvent->hparam)
        return GUI_EVENT_ACCEPTED;
    else
        return GUI_EVENT_DECLINE;
}



uint8_t guiCheckBox_ProcessEvent(guiGenericWidget_t *widget, guiEvent_t event)
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
            guiCore_CallEventHandler(widget, &event);
            // Reset flags
            checkBox->redrawFlags = 0;
            checkBox->redrawRequired = 0;
            break;
        case GUI_EVENT_FOCUS:
            guiCheckbox_SetFocused(checkBox,1);
            break;
        case GUI_EVENT_UNFOCUS:
            guiCheckbox_SetFocused(checkBox,0);
            break;
        case GUI_EVENT_SHOW:
            guiCheckbox_SetVisible(checkBox,1);
            break;
        case GUI_EVENT_HIDE:
            guiCheckbox_SetVisible(checkBox,0);
            break;
        case GUI_EVENT_KEY:
            if ((checkBox->isFocused == 0) || (checkBox->isVisible == 0))
            {
                processResult = GUI_EVENT_DECLINE;
                break;
            }
            // Call user-defined key converter as handler if specified
            processResult = (checkBox->useDefaultKeyConverter) ? guiCheckbox_DefaultKeyConverter(&event):
                                                                 guiCore_CallEventHandler(widget, &event);
            if (processResult == GUI_EVENT_DECLINE) break;
            // Check result key
            if (event.hparam == CHECKBOX_KEY_OK)
            {
                guiCheckbox_SetChecked(checkBox, !checkBox->isChecked);
            }
            break;
        case GUI_EVENT_TOUCH:
            guiCore_DecodeWidgetTouchEvent((guiGenericWidget_t *)checkBox, &event, &touch);
            if (checkBox->keepTouch)
            {
                if (touch.state == TOUCH_RELEASE)
                    checkBox->keepTouch = 0;
            }
            else
            {
                if (touch.isInsideWidget)
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
            processResult = guiCore_CallEventHandler(widget, &event);
    }
    return processResult;
}




/*            if (checkBox->useDefaultKeyConverter)
            {
                processResult = guiCheckbox_DefaultKeyConverter(&event);
                if (processResult == GUI_EVENT_DECLINE)
                {
                    processResult = guiCore_CallEventHandler(widget, &event);
                    break;
                }
            }
            else
            {
                processResult = guiCore_CallEventHandler(widget, &event);
            }
            if (processResult == GUI_EVENT_DECLINE)
                break; */





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
    //checkBox->keyConverter = guiCheckbox_DefaultKeyConverter;
    checkBox->useDefaultKeyConverter = 1;

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

