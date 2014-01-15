/**********************************************************
    Module stringList




**********************************************************/

#include <stdint.h>         // using integer types
#include <string.h>         // using memset
#include "guiEvents.h"
#include "guiCore.h"
#include "guiWidgets.h"
#include "guiGraphWidgets.h"
#include "guiStringList.h"


static uint8_t wrapIndex(uint8_t current, uint8_t max, int8_t increment)
{
    int16_t res = (int16_t)current + increment;
    if (res > max)
        res -= (max + 1);
    else if (res < 0)
        res += (max + 1);
    return res;
}

void guiStringList_SelectItem(guiStringList_t* list, uint8_t index)
{
    guiEvent_t event;
    if (index < list->stringCount)
    {
        if (index != list->selectedIndex)
        {
            list->selectedIndex = index;
            list->firstIndexToDisplay = index;
            list->redrawRequired = 1;
            list->redrawForced = 1;
            event.type = STRINGLIST_INDEX_CHANGED;
            guiCore_CallEventHandler((guiGenericWidget_t *)list, &event );
        }
    }
}

/*
static uint8_t guiStringList_SelectNextItem(guiStringList_t* list, int8_t dir)
{
    uint8_t visibleHead = list->firstIndexToDisplay;
    uint8_t visibleTail = wrapIndex(list->firstIndexToDisplay, list->stringCount - 1, list->visibleItemsCount - 1);
    uint8_t prevSelectedIndex = list->items.selectedIndex;

    if ((list->items.selectedIndex == visibleHead) && (dir < 0))
    {
        if ((list->properties & LISTBOX_CAN_WRAP) || (list->items.selectedIndex != 0))
        {
            list->items.firstIndexToDisplay = wrapIndex(list->items.firstIndexToDisplay, list->items.count - 1, dir);
            list->items.selectedIndex = wrapIndex(list->items.selectedIndex, list->items.count - 1, dir);
        }
    }
    else if ((list->items.selectedIndex == visibleTail) && (dir > 0))
    {
        if ((list->properties & LISTBOX_CAN_WRAP) || (list->items.selectedIndex != list->items.count - 1))
        {
            list->items.firstIndexToDisplay = wrapIndex(list->items.firstIndexToDisplay, list->items.count - 1, dir);
            list->items.selectedIndex = wrapIndex(list->items.selectedIndex, list->items.count - 1, dir);
        }
    }
    else
    {
        list->items.selectedIndex = wrapIndex(list->items.selectedIndex, list->items.count - 1, dir);
    }

    if (prevSelectedIndex != list->items.selectedIndex)
    {
        guiCore_CallEventHandler((guiGenericWidget_t *)list,WEVENT_SELECTED_INDEX_CHANGED);
        list->redrawFlags |= WF_REDRAW_CONTENT;
        return 1;
    }
    else
        return 0;
}
*/

uint8_t guiStringList_SetActive(guiStringList_t *list, uint8_t newActiveState)
{
    guiEvent_t event;
    if (list == 0) return 0;

    if (newActiveState)
    {
        // Activate
        if (list->isActive) return 0;
        list->isActive = 1;
    }
    else
    {
        // Deactivate
        if (list->isActive == 0) return 0;
        list->isActive = 0;

    }
    // Active state changed - call handler
    list->redrawFocus = 1;
    list->redrawRequired = 1;
    if (list->handlers.count != 0)
    {
        event.type = STRINGLIST_ACTIVE_CHANGED;
        guiCore_CallEventHandler((guiGenericWidget_t *)list, &event);
    }
    return 1;
}


//-------------------------------------------------------//
// StringList key handler
//
// Returns GUI_EVENT_ACCEPTED if key is processed,
//         GUI_EVENT_DECLINE otherwise
//-------------------------------------------------------//
uint8_t guiStringList_ProcessKey(guiStringList_t *list, uint8_t key)
{
    if (list->isActive)
    {
       /* if (key == SPINBOX_KEY_SELECT)
        {
            guiSpinBox_SetActive(spinBox, 0, 0);
        }
        else*/ if (key == STRINGLIST_KEY_EXIT)
        {
            guiStringList_SetActive(list, 0);
        }
        else if (key == STRINGLIST_KEY_LEFT)
        {
            guiStringList_SelectItem(list,wrapIndex(list->selectedIndex, list->stringCount-1, -1));
        }
        else if (key == STRINGLIST_KEY_RIGHT)
        {
            guiStringList_SelectItem(list,wrapIndex(list->selectedIndex, list->stringCount-1, 1));
        }/*
        else if (key == SPINBOX_KEY_UP)
        {
            // increase value
            guiSpinBox_IncrementValue(spinBox, 1);
        }
        else if (key == SPINBOX_KEY_DOWN)
        {
            //decrease value
            guiSpinBox_IncrementValue(spinBox, -1);
        }
        else
        {
            return GUI_EVENT_DECLINE;
        } */
    }
    else
    {
        if (key == STRINGLIST_KEY_SELECT)
        {
            guiStringList_SetActive(list, 1);
        }
        else
        {
            return GUI_EVENT_DECLINE;
        }
    }

    return GUI_EVENT_ACCEPTED;
}



//-------------------------------------------------------//
// stringList event handler
//
// Returns GUI_EVENT_ACCEPTED if event is processed,
//         GUI_EVENT_DECLINE otherwise
//-------------------------------------------------------//
uint8_t guiStringList_ProcessEvent(guiGenericWidget_t *widget, guiEvent_t event)
{
    guiStringList_t *list = (guiStringList_t *)widget;
    uint8_t processResult = GUI_EVENT_ACCEPTED;
    uint8_t key;

    switch (event.type)
    {
        case GUI_EVENT_DRAW:
            guiGraph_DrawStringList(list);
            // Call handler
            guiCore_CallEventHandler(widget, &event);
            // Reset flags - redrawForced will be reset by core
            list->redrawFocus = 0;
            list->redrawRequired = 0;
            break;
        case GUI_EVENT_FOCUS:
            if (STRINGLIST_ACCEPTS_FOCUS_EVENT(list))
                guiCore_SetFocused((guiGenericWidget_t *)list,1);
            else
                processResult = GUI_EVENT_DECLINE;      // Cannot accept focus
            break;
        case GUI_EVENT_UNFOCUS:
            guiCore_SetFocused((guiGenericWidget_t *)list,0);
            guiStringList_SetActive(list, 0);
            break;
        case STRINGLIST_EVENT_ACTIVATE:
            if (list->isFocused)
            {
                guiStringList_SetActive(list, 1);
            }
            // Accept event anyway
            break;
        case GUI_EVENT_SHOW:
            guiCore_SetVisible((guiGenericWidget_t *)list, 1);
            break;
        case GUI_EVENT_HIDE:
            guiCore_SetVisible((guiGenericWidget_t *)list, 0);
            break;
        case GUI_EVENT_ENCODER:
            processResult = GUI_EVENT_DECLINE;
            if (STRINGLIST_ACCEPTS_ENCODER_EVENT(list))
            {
                if (list->isActive)
                {
                    //guilist_IncrementValue(list, (int16_t)event.lparam);
                    if ((int16_t)event.lparam < 0)
                        guiStringList_ProcessKey(list, STRINGLIST_KEY_LEFT);
                    else
                        guiStringList_ProcessKey(list, STRINGLIST_KEY_RIGHT);
                    processResult = GUI_EVENT_ACCEPTED;
                }
                processResult |= guiCore_CallEventHandler(widget, &event);
            }
            break;
        case GUI_EVENT_KEY:
            processResult = GUI_EVENT_DECLINE;
            if (STRINGLIST_ACCEPTS_KEY_EVENT(list))
            {
                if (event.spec == GUI_KEY_EVENT_DOWN)
                {
                    if (event.lparam == GUI_KEY_OK)
                        key = STRINGLIST_KEY_SELECT;
                    else if (event.lparam == GUI_KEY_ESC)
                        key = STRINGLIST_KEY_EXIT;
                    else if (event.lparam == GUI_KEY_LEFT)
                        key = STRINGLIST_KEY_LEFT;
                    else if (event.lparam == GUI_KEY_RIGHT)
                        key = STRINGLIST_KEY_RIGHT;
                    else if (event.lparam == GUI_KEY_UP)
                        key = STRINGLIST_KEY_UP;
                    else if (event.lparam == GUI_KEY_DOWN)
                        key = STRINGLIST_KEY_DOWN;
                    else
                        key = 0;
                    if (key != 0)
                        processResult = guiStringList_ProcessKey(list, key);
                }
                // Call KEY event handler
                processResult |= guiCore_CallEventHandler(widget, &event);
            }
            break;

        default:
            // Widget cannot process incoming event. Try to find a handler.
            processResult = guiCore_CallEventHandler(widget, &event);
    }
    return processResult;
}





void guiStringList_Initialize(guiStringList_t *list, guiGenericWidget_t *parent)
{
    memset(list, 0, sizeof(guiStringList_t));
    list->parent = parent;
    list->acceptFocusByTab = 1;
    list->isVisible = 1;
    list->showFocus = 1;
    list->processEvent = guiStringList_ProcessEvent;
}
