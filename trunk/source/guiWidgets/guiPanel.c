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
    event.args = 0;
    guiCore_CallEventHandler((guiGenericWidget_t *)panel, event);
}









uint8_t guiPanel_ProcessEvent(guiGenericWidget_t *widget, guiEvent_t event)
{
    uint8_t processResult = GUI_EVENT_ACCEPTED;
    guiPanel_t *panel = (guiPanel_t *)widget;
    int16_t x,y;
    guiEventArgButtons_t *argButtons;
    guiGenericWidget_t *w;
    uint8_t touchState;

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
            guiCore_CallEventHandler((guiGenericWidget_t *)panel, event);
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
        case GUI_EVENT_BUTTONS_ENCODER:
            if ((panel->isVisible == 0))// || (panel->isFocused == 0))  // TODO - add isEnabled
            {
                processResult = GUI_EVENT_DECLINE;      // Cannot accept buttons event
                break;
            }
            argButtons = (guiEventArgButtons_t *)event.args;

            if (panel->isFocused)
            {
                if (argButtons->buttonCode & GUI_BTN_OK)
                    guiCore_RequestFocusNextWidget((guiGenericContainer_t *)panel,1);
                else
                    processResult = GUI_EVENT_DECLINE;
            }
            else
            {
                if (argButtons->buttonCode & GUI_BTN_LEFT)
                {
                    // Event came from child elements
                    if (panel->focusFallsThrough)
                    {
                        // Check if event should be passed to parent
                        w = panel->widgets.elements[ panel->widgets.focusedIndex ];
                        if (guiCore_CheckWidgetTabIndex(w) == TABINDEX_IS_MIN)
                        {
                            processResult = GUI_EVENT_DECLINE;
                            break;
                        }
                    }
                    guiCore_RequestFocusNextWidget((guiGenericContainer_t *)panel,-1);
                }
                else if (argButtons->buttonCode & GUI_BTN_RIGHT)
                {
                    // Event came from child elements
                    if (panel->focusFallsThrough)
                    {
                        // Check if event should be passed to parent
                        w = panel->widgets.elements[ panel->widgets.focusedIndex ];
                        if (guiCore_CheckWidgetTabIndex(w) == TABINDEX_IS_MAX)
                        {
                            processResult = GUI_EVENT_DECLINE;
                            break;
                        }
                    }
                    guiCore_RequestFocusNextWidget((guiGenericContainer_t *)panel,1);
                }
                else if (argButtons->buttonCode & GUI_BTN_ESC)
                {
                    if (panel->focusFallsThrough)
                    {
                        processResult = GUI_EVENT_DECLINE;
                        break;
                    }
                    else
                    {
                        guiPanel_SetFocused(panel, 1);
                    }
                }
                else
                {
                    // Unknown key
                    processResult = guiCore_CallEventHandler(widget, event);
                }
            }
            break;
         case GUI_EVENT_TOUCH:
            // Convert coordinates to widget's relative
            x = ((guiEventTouch_t *)event.args)->x;
            y = ((guiEventTouch_t *)event.args)->y;
            guiCore_ConvertToRelativeXY((guiGenericWidget_t *)panel, &x, &y);
            touchState = ((guiEventTouch_t *)event.args)->state;
            w = guiCore_GetWidgetAtXY((guiGenericWidget_t *)panel, x, y);
            if (panel->keepTouch)
            {
                if (touchState == TOUCH_RELEASE)
                {
                    panel->keepTouch = 0;
                }
            }
            else
            {
                // Determine if touch point lies inside one of child widgets
                if (w == 0)
                {
                    // Touch point does not lie inside panel - skip that.
                    processResult = GUI_EVENT_DECLINE;
                }
                else if (w != (guiGenericWidget_t *)panel)
                {
                    // Point belogs to one of child widgets - pass touch event to it.
                    guiCore_AddMessageToQueue(w, event);
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

    panel->widgets.count = 0;
    panel->widgets.focusedIndex = 0;
    panel->widgets.traverseIndex = 0;
    panel->redrawFlags = 0;
    panel->frame = FRAME_NONE;
    panel->showFocus = 1;
}



