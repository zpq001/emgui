/**********************************************************
    Module guiForm




**********************************************************/

#include <stdint.h>
#include "guiFonts.h"
#include "guiGraphPrimitives.h"
#include "guiGraphWidgets.h"
#include "guiEvents.h"
#include "guiCore.h"
#include "guiWidgets.h"
#include "guiPanel.h"


static containerTouchState_t touch;



void guiPanel_SetFocused(guiPanel_t *panel, uint8_t newFocusedState)
{
    guiEvent_t event;
    if (panel == 0) return;

    if (newFocusedState)
    {
        // Set focus on panel
        if (panel->isFocused) return;
        panel->isFocused = 1;
        guiCore_AcceptFocus((guiGenericWidget_t *)panel);
    }
    else
    {
        // Focus was removed
        if (panel->isFocused == 0) return;
        panel->isFocused = 0;
    }
    // Focused state changed - call handler
    panel->redrawFlags |= PANEL_REDRAW_FOCUS;
    panel->redrawRequired = 1;
    event.type = GUI_ON_FOCUS_CHANGED;
    guiCore_CallEventHandler((guiGenericWidget_t *)panel, &event);
}





uint8_t guiPanel_DefaultKeyConverter(guiEvent_t *keyEvent)
{
    keyEvent->hparam = 0;
    if (keyEvent->spec == DEFAULT_KEY_EVENT_DOWN)
    {
        if (keyEvent->lparam == DEFAULT_KEY_OK)
            keyEvent->hparam = PANEL_KEY_OK;
        else if (keyEvent->lparam == DEFAULT_KEY_ESC)
            keyEvent->hparam = PANEL_KEY_ESC;
        else if (keyEvent->lparam == DEFAULT_KEY_LEFT)
            keyEvent->hparam = PANEL_KEY_LEFT;
        else if (keyEvent->lparam == DEFAULT_KEY_RIGHT)
            keyEvent->hparam = PANEL_KEY_RIGHT;
    }
    if (keyEvent->hparam)
        return GUI_EVENT_ACCEPTED;
    else
        return GUI_EVENT_DECLINE;
}




uint8_t guiPanel_ProcessEvent(guiGenericWidget_t *widget, guiEvent_t event)
{
    uint8_t processResult = GUI_EVENT_ACCEPTED;
    guiPanel_t *panel = (guiPanel_t *)widget;
    guiGenericWidget_t *w;

    // Process GUI messages - focus, draw, etc
    switch(event.type)
    {
          case GUI_EVENT_DRAW:
            // Check if full redraw is required
            if (panel->redrawForced)
            {
                // Widget must be fully redrawn - set all flags
                panel->redrawFlags = PANEL_REDRAW_FOCUS | PANEL_REDRAW_BACKGROUND;
            }
            guiGraph_DrawPanel(panel);
            event.type = GUI_ON_DRAW;
            guiCore_CallEventHandler((guiGenericWidget_t *)panel, &event);
            // Reset flags
            panel->redrawFlags = 0;
            panel->redrawRequired = 0;
            break;
        case GUI_EVENT_FOCUS:
            if (panel->isVisible == 0)  // TODO - add isEnabled
            {
                processResult = GUI_EVENT_DECLINE;      // Cannot accept focus
                break;
            }
            guiPanel_SetFocused(panel, 1);
            if (panel->focusFallsThrough)
            {
                guiCore_RequestFocusNextWidget((guiGenericContainer_t *)panel,1);
                //guiCore_RequestFocusChange(panel->widgets.elements[ panel->widgets.focusedIndex ]);
            }
            break;
        case GUI_EVENT_UNFOCUS:
            guiPanel_SetFocused(panel, 0);
            break;
        case GUI_EVENT_SHOW:
            guiCore_SetVisible((guiGenericWidget_t *)panel, 1);
            break;
        case GUI_EVENT_HIDE:
            guiCore_SetVisible((guiGenericWidget_t *)panel, 0);
            break;
        case GUI_EVENT_ENCODER:
            if ((panel->isVisible == 0))  // TODO - add isEnabled
            {
                processResult = GUI_EVENT_DECLINE;      // Cannot accept buttons event
                break;
            }
            if (panel->useDefaultEncoderHandler)
            {
                event.hparam = (int16_t)event.lparam < 0 ? PANEL_KEY_LEFT :
                               ((int16_t)event.lparam > 0 ? PANEL_KEY_RIGHT : 0);
                goto lbl_1;
            }
            processResult = guiCore_CallEventHandler(widget, &event);
            if (processResult == GUI_EVENT_ACCEPTED)
                goto lbl_1;
            break;
        case GUI_EVENT_KEY:
            if ((panel->isVisible == 0))  // TODO - add isEnabled
            {
                processResult = GUI_EVENT_DECLINE;      // Cannot accept buttons event
                break;
            }
            // Call user-defined key converter as handler if specified
            // CHECKME - useDefaultKeyHandler ?
            processResult = (panel->useDefaultKeyConverter) ? guiPanel_DefaultKeyConverter(&event):
                                                              guiCore_CallEventHandler(widget, &event);
            if (processResult == GUI_EVENT_DECLINE) break;
lbl_1:
            if (panel->isFocused)
            {
                if (event.hparam == PANEL_KEY_OK)
                    guiCore_RequestFocusNextWidget((guiGenericContainer_t *)panel,1);
                else
                    processResult = GUI_EVENT_DECLINE;
            }
            else
            {
                // Event came from child elements
                w = panel->widgets.elements[ panel->widgets.focusedIndex ];
                if (event.hparam == PANEL_KEY_LEFT)
                {
                    // Check if event should be passed to parent
                    if ((panel->focusFallsThrough) && (guiCore_CheckWidgetTabIndex(w) == TABINDEX_IS_MIN))
                    {
                        processResult = GUI_EVENT_DECLINE;
                        break;
                    }
                    guiCore_RequestFocusNextWidget((guiGenericContainer_t *)panel,-1);
                }
                else if (event.hparam == PANEL_KEY_RIGHT)
                {
                    // Check if event should be passed to parent
                    if ((panel->focusFallsThrough) && (guiCore_CheckWidgetTabIndex(w) == TABINDEX_IS_MAX))
                    {
                        processResult = GUI_EVENT_DECLINE;
                        break;
                    }
                    guiCore_RequestFocusNextWidget((guiGenericContainer_t *)panel,1);
                }
                else if (event.hparam == PANEL_KEY_ESC)
                {
                    if (panel->focusFallsThrough)
                    {
                        processResult = GUI_EVENT_DECLINE;
                        break;
                    }
                    guiPanel_SetFocused(panel, 1);
                }
            }
            break;
         case GUI_EVENT_TOUCH:
            guiCore_DecodeContainerTouchEvent((guiGenericWidget_t *)panel, &event, &touch);
            if (panel->keepTouch)
            {
                if (touch.state == TOUCH_RELEASE)
                    panel->keepTouch = 0;
            }
            else
            {
                // Determine if touch point lies inside one of child widgets
                if (touch.widgetAtXY == 0)
                {
                    // Touch point does not lie inside panel - skip that.
                    processResult = GUI_EVENT_DECLINE;
                }
                else if (touch.widgetAtXY != (guiGenericWidget_t *)panel)
                {
                    // Point belogs to one of child widgets - pass touch event to it.
                    guiCore_AddMessageToQueue(touch.widgetAtXY, &event);
                }
                else
                {
                    // Point belogs to panel itself
                    guiPanel_SetFocused(panel, 1);
                    panel->keepTouch = 1;
                    // TODO - touch handlers!
                }
            }
            break;
    }
    return processResult;
}




void guiPanel_Initialize(guiPanel_t *panel, guiGenericWidget_t *parent)
{
    panel->parent = parent;
    panel->acceptFocus = 1;
    panel->acceptFocusByTab = 0;
    panel->isFocused = 0;
    panel->isVisible = 0;
    panel->redrawForced = 0;
    panel->redrawRequired = 0;
    panel->isContainer = 1;
    panel->tag = 0;
    panel->tabIndex = 0;
    panel->processEvent = guiPanel_ProcessEvent;
    panel->handlers.count = 0;
    panel->acceptTouch = 1;
    panel->focusFallsThrough = 0;
    panel->keepTouch = 0;
    panel->useDefaultKeyConverter = 1;
    panel->useDefaultEncoderHandler = 1;

    panel->widgets.count = 0;
    panel->widgets.focusedIndex = 0;
    panel->widgets.traverseIndex = 0;
    panel->redrawFlags = 0;
    panel->frame = FRAME_NONE;
    panel->showFocus = 1;
}



