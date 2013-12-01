#include <stdio.h>

#include "guiConfig.h"
#include "guiCore.h"
#include "guiWidgetCommon.h"
#include "guiListBox.h"

#include "guiFonts.h"
#include "guiFontUtils.h"
#include "guiGraphUtils.h"



static uint8_t wrapIndex(uint8_t current, uint8_t max, int8_t increment)
{
    int16_t res = (int16_t)current + increment;
    if (res > max)
        res -= (max + 1);
    else if (res < 0)
        res += (max + 1);
    return res;
}


static void guiListBox_Draw(guiListBox_t* pListBox)
{
    uint8_t mode;
    uint8_t drawFrame;

    uint8_t i;
    uint8_t index;
    uint16_t x;
    uint16_t y;

    if (pListBox->redrawFlags & WF_REDRAW_SELECTION)
    {
        if (pListBox->properties & LISTBOX_HAS_FRAME)
            mode = PIXEL_ON;
        else
            mode = PIXEL_OFF;
        drawFrame = 1;
    }
    else if ((blinkTimer.FTop) && ((pListBox->state & (WF_IS_SELECTED | WF_IS_ACTIVE)) == WF_IS_SELECTED))
    {
        if (blinkTimer.FA_TGL)
            mode = PIXEL_OFF;
        else
            mode = PIXEL_ON;
        drawFrame = 1;
    }

    if (drawFrame)
    {
        // Draw a frame
        guiGraph_PutHorLine(pListBox->x_pos,pListBox->y_pos,pListBox->width,mode);
        guiGraph_PutHorLine(pListBox->x_pos,pListBox->y_pos + pListBox->height - 1,pListBox->width,mode);
        guiGraph_PutVertLine(pListBox->x_pos,pListBox->y_pos,pListBox->height,mode);
        guiGraph_PutVertLine(pListBox->x_pos+pListBox->width - 1,pListBox->y_pos,pListBox->height,mode);
    }

    if (pListBox->redrawFlags & WF_REDRAW_CONTENT)
    {
        x = pListBox->x_pos+2;
        y = pListBox->y_pos+1;
        index = pListBox->items.firstIndexToDisplay;


        for (i=0;i<pListBox->visibleItemsCount; i++)
        {

            if (index == pListBox->items.selectedIndex)
            {
                guiGraph_FillRect(pListBox->x_pos+1, y, pListBox->width-2, pListBox->pFont->height, FILL_WITH_BLACK);
                mode = PIXEL_MODE_XOR;
            }
            else
            {
                guiGraph_FillRect(pListBox->x_pos+1, y, pListBox->width-2, pListBox->pFont->height, FILL_WITH_WHITE);
                mode = PIXEL_MODE_OR;
            }
            if (pListBox->items.strings[index])
            {
                guiFont_PrintString(x, y, pListBox->items.strings[index], pListBox->pFont, mode);
            }
            y += pListBox->pFont->height;
            index = wrapIndex(index, pListBox->items.count-1, 1);
        }
    }
}



void guiListBox_SelectItem(guiListBox_t* pListBox, uint8_t index)
{
    if (index < pListBox->items.count)
    {
        if (index != pListBox->items.selectedIndex)
        {
            pListBox->items.selectedIndex = index;
            pListBox->items.firstIndexToDisplay = index;
            pListBox->redrawFlags |= WF_REDRAW_CONTENT;
            guiCore_CallEventHandler((guiGenericWidget_t *)pListBox, WEVENT_SELECTED_INDEX_CHANGED);
        }
    }
}


static uint8_t guiListBox_SelectNextItem(guiListBox_t* pListBox, int8_t dir)
{
    uint8_t visibleHead = pListBox->items.firstIndexToDisplay;
    uint8_t visibleTail = wrapIndex(pListBox->items.firstIndexToDisplay, pListBox->items.count - 1, pListBox->visibleItemsCount - 1);
    uint8_t prevSelectedIndex = pListBox->items.selectedIndex;

    if ((pListBox->items.selectedIndex == visibleHead) && (dir < 0))
    {
        if ((pListBox->properties & LISTBOX_CAN_WRAP) || (pListBox->items.selectedIndex != 0))
        {
            pListBox->items.firstIndexToDisplay = wrapIndex(pListBox->items.firstIndexToDisplay, pListBox->items.count - 1, dir);
            pListBox->items.selectedIndex = wrapIndex(pListBox->items.selectedIndex, pListBox->items.count - 1, dir);
        }
    }
    else if ((pListBox->items.selectedIndex == visibleTail) && (dir > 0))
    {
        if ((pListBox->properties & LISTBOX_CAN_WRAP) || (pListBox->items.selectedIndex != pListBox->items.count - 1))
        {
            pListBox->items.firstIndexToDisplay = wrapIndex(pListBox->items.firstIndexToDisplay, pListBox->items.count - 1, dir);
            pListBox->items.selectedIndex = wrapIndex(pListBox->items.selectedIndex, pListBox->items.count - 1, dir);
        }
    }
    else
    {
        pListBox->items.selectedIndex = wrapIndex(pListBox->items.selectedIndex, pListBox->items.count - 1, dir);
    }

    if (prevSelectedIndex != pListBox->items.selectedIndex)
    {
        guiCore_CallEventHandler((guiGenericWidget_t *)pListBox,WEVENT_SELECTED_INDEX_CHANGED);
        pListBox->redrawFlags |= WF_REDRAW_CONTENT;
        return 1;
    }
    else
        return 0;
}


static uint8_t guiListBox_ProcessEvent(guiGenericWidget_t *pWidget, guiEvent_t event)
{
    uint8_t processResult = EVENT_FLAG_NOT_USED;
    uint16_t buttonCode = 0;
    int16_t encoderDelta = 0;
    guiListBox_t *pListBox = (guiListBox_t *)pWidget;
    if (event.type == GUI_EVENT_BUTTONS_ENCODER)
    {
        buttonCode = ((guiEventArgButtons_t *)event.args)->buttonCode;
        encoderDelta = ((guiEventArgButtons_t *)event.args)->encoderDelta;
    }



    switch(event.type)
    {
        case GUI_EVENT_DRAW_ALL:
            pListBox->redrawFlags |= (WF_REDRAW_SELECTION | WF_REDRAW_CONTENT);
            // Fall downto EVENT_DRAW
        case GUI_EVENT_DRAW:
            if ((pListBox->properties & WP_IS_VISIBLE) == 0)
                break;
            guiListBox_Draw(pListBox);
            guiCore_CallEventHandler(pWidget,GUI_EVENT_DRAW);   // CHECKME
            pListBox->redrawFlags = 0;
            processResult = EVENT_FLAG_ACCEPTED;
            break;
        case GUI_EVENT_HIDE:
            pListBox->properties &= ~WP_IS_VISIBLE;
            guiCore_RequestFullRedraw();
            break;
        case GUI_EVENT_SHOW:
            pListBox->properties |= WP_IS_VISIBLE;
            pListBox->redrawFlags |= (WF_REDRAW_SELECTION | WF_REDRAW_CONTENT);
            break;
        case GUI_EVENT_SELECT:
        case GUI_EVENT_DESELECT:
        case GUI_EVENT_BUTTONS_ENCODER:
            //----------------------------//
            // Process event depending on widget state
            switch (pListBox->state & (WF_IS_SELECTED | WF_IS_ACTIVE))
            {
                case WF_IS_SELECTED:
                    if (event.type == GUI_EVENT_DESELECT)
                    {
                        pListBox->state &= ~WF_IS_SELECTED;
                        pListBox->redrawFlags |= WF_REDRAW_SELECTION;
                        guiCore_CallEventHandler((guiGenericWidget_t *)pListBox,WEVENT_SELECTED_CHANGED);
                        processResult = EVENT_FLAG_ACCEPTED;
                    }
                    else if ((event.type == GUI_EVENT_BUTTONS_ENCODER) && (buttonCode & GUI_BTN_OK))
                    {
                        pListBox->state |= WF_IS_ACTIVE;
                        pListBox->items.savedIndex = pListBox->items.selectedIndex;
                        pListBox->redrawFlags |= WF_REDRAW_SELECTION;
                        guiCore_CallEventHandler((guiGenericWidget_t *)pListBox,WEVENT_ACTIVE_CHANGED);
                        processResult = EVENT_FLAG_ACCEPTED;
                    }
                    break;
                case (WF_IS_SELECTED | WF_IS_ACTIVE):
                    if ( (event.type == GUI_EVENT_DESELECT) || (buttonCode & (GUI_BTN_ESC | GUI_BTN_OK)) )
                    {
                        pListBox->state &= ~WF_IS_ACTIVE;
                        if ((buttonCode & GUI_BTN_ESC) && (pListBox->properties & LISTBOX_RESTORE_INDEX_ON_ESC))
                        {
                            guiListBox_SelectItem(pListBox, pListBox->items.savedIndex);
                            pListBox->redrawFlags |= WF_REDRAW_CONTENT;
                            pListBox->state &= ~WF_LAST_CHANGES_ACCEPTED;
                        }
                        else
                        {
                            pListBox->state |= WF_LAST_CHANGES_ACCEPTED;
                        }
                        guiCore_CallEventHandler((guiGenericWidget_t *)pListBox,WEVENT_ACTIVE_CHANGED);

                        if (pListBox->properties & WP_SELECT_IS_ACTIVATE)
                        {
                            pListBox->state &= ~WF_IS_SELECTED;
                            pListBox->redrawFlags |= WF_REDRAW_SELECTION;
                            guiCore_CallEventHandler((guiGenericWidget_t *)pListBox,WEVENT_SELECTED_CHANGED);
                            //processResult = EVENT_FLAG_NOT_USED;  // already set to this value
                        }
                        else
                        {
                            processResult = EVENT_FLAG_ACCEPTED;
                        }
                    }
                    else if ((buttonCode & GUI_BTN_LEFT) || (encoderDelta < 0))
                    {
                        guiListBox_SelectNextItem(pListBox,-1);
                        processResult = EVENT_FLAG_ACCEPTED;
                    }
                    else if ((buttonCode & GUI_BTN_RIGHT) || (encoderDelta > 0))
                    {
                        guiListBox_SelectNextItem(pListBox,1);
                        processResult = EVENT_FLAG_ACCEPTED;
                    }
                    break;
                default:
                    if (event.type == GUI_EVENT_SELECT)
                    {
                        pListBox->state |= WF_IS_SELECTED;
                        pListBox->redrawFlags |= WF_REDRAW_SELECTION;
                        guiCore_CallEventHandler((guiGenericWidget_t *)pListBox,WEVENT_SELECTED_CHANGED);
                        if (pListBox->properties & WP_SELECT_IS_ACTIVATE)
                        {
                            pListBox->state |= WF_IS_ACTIVE;
                            pListBox->items.savedIndex = pListBox->items.selectedIndex;
                            guiCore_CallEventHandler((guiGenericWidget_t *)pListBox,WEVENT_ACTIVE_CHANGED);
                        }
                        processResult = EVENT_FLAG_ACCEPTED;
                    }
                    break;
            }
            break;
            //----------------------------//
        default:
            if (guiCore_CallEventHandler(pWidget,event.type))
                processResult = EVENT_FLAG_ACCEPTED;
    }

    return processResult;
}


void guiListBox_Initialize(guiListBox_t *pListBox)
{
    //----------------------//
    // Fields, common for all widgets
    pListBox->type = WT_LISTBOX;
    pListBox->redrawFlags = 0;
    pListBox->tabIndex = 0;
    pListBox->properties = 0;
    pListBox->state = 0;
    pListBox->tag = 0;
    pListBox->processEvent = guiListBox_ProcessEvent;
    pListBox->handlers.count = 0;
    pListBox->items.count = 0;
    pListBox->items.selectedIndex = 0;
    pListBox->items.firstIndexToDisplay = 0;
    //----------------------//

    pListBox->x_pos = 0;
    pListBox->y_pos = 0;

    pListBox->visibleItemsCount = 4;
    pListBox->width = 80;
    pListBox->pFont = &font_8x12;
    pListBox->height = 4 * font_8x12.height + 2;
}




