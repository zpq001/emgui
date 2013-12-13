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









static uint8_t guiPanel_ProcessEvent(guiGenericWidget_t *widget, guiEvent_t event)
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
            //guiGraph_DrawPanel(panel);
            guiGraph_DrawForm((guiForm_t *)panel);       // FIXME
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
            // TODO - add property
            // guiCore_RequestFocusNextWidget((guiGenericContainer_t *)panel,1);
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
            if ((panel->isVisible == 0) || (panel->isFocused == 0))  // TODO - add isEnabled
            {
                processResult = GUI_EVENT_DECLINE;      // Cannot accept buttons event
                break;
            }
            argButtons = (guiEventArgButtons_t *)event.args;
            if (argButtons->buttonCode & GUI_BTN_LEFT)
                guiCore_RequestFocusNextWidget((guiGenericContainer_t *)panel,-1);
            else if (argButtons->buttonCode & GUI_BTN_RIGHT)
                guiCore_RequestFocusNextWidget((guiGenericContainer_t *)panel,1);
            else
                processResult = GUI_EVENT_DECLINE;
            break;
         case GUI_EVENT_TOUCH:
            if ((panel->isVisible == 0) || (0))  // TODO - add isEnabled
            {
                processResult = GUI_EVENT_DECLINE;      // Cannot accept touch event
                break;
            }
            // Convert coordinates to widget's relative
            x = ((guiEventTouch_t *)event.args)->x;
            y = ((guiEventTouch_t *)event.args)->y;
            guiCore_ConvertToRelativeXY((guiGenericWidget_t *)panel, &x, &y);
            touchState = ((guiEventTouch_t *)event.args)->state;
            w = guiCore_GetWidgetAtXY((guiGenericWidget_t *)panel, x, y);

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
            }
            break;
    }
    return processResult;
}




void guiPanel_Initialize(guiPanel_t *panel)
{
    panel->parent = 0;
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

    panel->widgets.count = 0;
    panel->widgets.focusedIndex = 0;
    panel->widgets.traverseIndex = 0;
    panel->redrawFlags = 0;
    panel->hasFrame = 0;
}



