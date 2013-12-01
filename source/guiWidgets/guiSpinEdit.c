#include <stdio.h>

#include "guiConfig.h"
#include "guiCore.h"
#include "guiUtils.h"
#include "guiWidgetCommon.h"
#include "guiSpinEdit.h"

#include "guiFonts.h"
#include "guiFontUtils.h"
#include "guiGraphUtils.h"



static void guiSpinEdit_Draw(guiSpinEdit_t* pSpinEdit)
{
    uint8_t mode;
    uint8_t drawFrame = 0;

    uint16_t x;
    uint16_t y;
    char c;
    uint8_t i;
    uint8_t charIndex;
    uint8_t currentDigit;
    uint8_t currentDigitIsActive;


    if (pSpinEdit->redrawFlags & WF_REDRAW_SELECTION)
    {
        if (pSpinEdit->properties & SPINEDIT_HAS_FRAME)
            mode = PIXEL_ON;
        else
            mode = PIXEL_OFF;
        drawFrame = 1;
    }
    else if ((blinkTimer.FTop) && ((pSpinEdit->state & (WF_IS_SELECTED | WF_IS_ACTIVE)) == WF_IS_SELECTED))
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
        guiGraph_PutHorLine(pSpinEdit->x_pos,pSpinEdit->y_pos,pSpinEdit->width,mode);
        guiGraph_PutHorLine(pSpinEdit->x_pos,pSpinEdit->y_pos + pSpinEdit->height - 1,pSpinEdit->width,mode);
        guiGraph_PutVertLine(pSpinEdit->x_pos,pSpinEdit->y_pos,pSpinEdit->height,mode);
        guiGraph_PutVertLine(pSpinEdit->x_pos+pSpinEdit->width - 1,pSpinEdit->y_pos,pSpinEdit->height,mode);
    }

    if (pSpinEdit->redrawFlags & WF_REDRAW_CONTENT)
    {
        x = pSpinEdit->x_pos + pSpinEdit->width - 1;
        y = pSpinEdit->y_pos + 1;

        charIndex = SPINEDIT_STRING_LENGTH - 1;
        currentDigit = 0;
        i = 0;

        guiGraph_FillRect(pSpinEdit->x_pos+1, pSpinEdit->y_pos+1, pSpinEdit->width-2, pSpinEdit->height-2, FILL_WITH_WHITE);

        while (currentDigit <=  pSpinEdit->digitsToUse)     // one extra digit for minus sign
        {
            x -= pSpinEdit->pFont->width;
            if (x <= pSpinEdit->x_pos)
                break;

            if (i == pSpinEdit->dotPosition)
            {
                c = '.';
                currentDigitIsActive = 0;
            }
            else
            {
                c = pSpinEdit->string[charIndex--];
                currentDigitIsActive = currentDigit == pSpinEdit->activeDigit;
                currentDigit++;
            }
            if ((currentDigitIsActive) && (pSpinEdit->state & WF_IS_ACTIVE))
                guiFont_PrintChar(x,y,c,pSpinEdit->pFont,IMAGE_MODE_INVERSE);
            else
                guiFont_PrintChar(x,y,c,pSpinEdit->pFont,IMAGE_MODE_NORM);

            i++;
        }
    }
}


void guiSpinEdit_IncrementValue(guiSpinEdit_t* pSpinEdit, int32_t delta)
{
    int32_t mul_c = 1;
    uint8_t i;
    for (i=0;i<pSpinEdit->activeDigit;i++)
    {
        mul_c *= 10;
    }

    delta *= mul_c;
    guiSpinEdit_SetValue(pSpinEdit, pSpinEdit->value + delta);
}


void guiSpinEdit_MoveActiveDigit(guiSpinEdit_t* pSpinEdit, int8_t step)
{
    int16_t temp;
    uint8_t newActiveDigit = pSpinEdit->activeDigit;
    if (step != 0)
    {
        temp = (int16_t)pSpinEdit->activeDigit;
        temp += step;

        if (temp > (int16_t)pSpinEdit->digitsToUse - 1)
            newActiveDigit = pSpinEdit->digitsToUse - 1;
        else if (temp < 0)
            newActiveDigit = 0;
        else
            newActiveDigit = (uint8_t)temp;

        if (newActiveDigit != pSpinEdit->activeDigit)
        {
            pSpinEdit->activeDigit = newActiveDigit;
            pSpinEdit->redrawFlags |= WF_REDRAW_CONTENT;
        }
    }
}





static uint8_t guiSpinEdit_ProcessEvent(guiGenericWidget_t *pWidget, guiEvent_t event)
{
    uint8_t processResult = EVENT_FLAG_NOT_USED;
    uint16_t buttonCode = 0;
    int16_t encoderDelta = 0;
    guiSpinEdit_t *pSpinEdit = (guiSpinEdit_t *)pWidget;
    if (event.type == GUI_EVENT_BUTTONS_ENCODER)
    {
        buttonCode = ((guiEventArgButtons_t *)event.args)->buttonCode;
        encoderDelta = ((guiEventArgButtons_t *)event.args)->encoderDelta;
    }



    switch(event.type)
    {
        case GUI_EVENT_DRAW_ALL:
            pSpinEdit->redrawFlags |= (WF_REDRAW_SELECTION | WF_REDRAW_CONTENT);
            // Fall downto EVENT_DRAW
        case GUI_EVENT_DRAW:
            if ((pSpinEdit->properties & WP_IS_VISIBLE) == 0)
                break;
            guiSpinEdit_Draw(pSpinEdit);
            guiCore_CallEventHandler(pWidget,GUI_EVENT_DRAW);   // CHECKME
            pSpinEdit->redrawFlags = 0;
            processResult = EVENT_FLAG_ACCEPTED;
            break;
        case GUI_EVENT_HIDE:
            if (pSpinEdit->properties & WP_IS_VISIBLE)
            {
                pSpinEdit->properties &= ~WP_IS_VISIBLE;
                guiCore_RequestFullRedraw();
            }
            break;
        case GUI_EVENT_SHOW:
            if ((pSpinEdit->properties & WP_IS_VISIBLE) == 0)
            {
                pSpinEdit->properties |= WP_IS_VISIBLE;
                pSpinEdit->redrawFlags |= (WF_REDRAW_SELECTION | WF_REDRAW_CONTENT);
            }
            break;
        case GUI_EVENT_SELECT:
        case GUI_EVENT_DESELECT:
        case GUI_EVENT_BUTTONS_ENCODER:
            //----------------------------//
            // Process event depending on widget state
            switch (pSpinEdit->state & (WF_IS_SELECTED | WF_IS_ACTIVE))
            {
                case WF_IS_SELECTED:
                    if (event.type == GUI_EVENT_DESELECT)
                    {
                        pSpinEdit->state &= ~WF_IS_SELECTED;
                        pSpinEdit->redrawFlags |= WF_REDRAW_SELECTION;
                        guiCore_CallEventHandler((guiGenericWidget_t *)pSpinEdit,WEVENT_SELECTED_CHANGED);
                        processResult = EVENT_FLAG_ACCEPTED;
                    }
                    else if ((event.type == GUI_EVENT_BUTTONS_ENCODER) && (buttonCode & GUI_BTN_OK))
                    {
                        pSpinEdit->state |= WF_IS_ACTIVE;
                        pSpinEdit->savedValue = pSpinEdit->value;
                        pSpinEdit->redrawFlags |= WF_REDRAW_SELECTION | WF_REDRAW_CONTENT;
                        guiCore_CallEventHandler((guiGenericWidget_t *)pSpinEdit,WEVENT_ACTIVE_CHANGED);
                        processResult = EVENT_FLAG_ACCEPTED;
                    }
                    break;
                case (WF_IS_SELECTED | WF_IS_ACTIVE):
                    if ( (event.type == GUI_EVENT_DESELECT) || (buttonCode & (GUI_BTN_ESC | GUI_BTN_OK)) )
                    {
                        pSpinEdit->state &= ~WF_IS_ACTIVE;
                        pSpinEdit->state |= WF_LAST_CHANGES_ACCEPTED;
                        pSpinEdit->redrawFlags |= WF_REDRAW_CONTENT;
                        if ((buttonCode & GUI_BTN_ESC) && (pSpinEdit->properties & SPINEDIT_RESTORE_ON_ESC))
                        {
                            if (pSpinEdit->value != pSpinEdit->savedValue)  // FIX listbox
                            {
                                guiSpinEdit_SetValue(pSpinEdit, pSpinEdit->savedValue);
                                pSpinEdit->state &= ~WF_LAST_CHANGES_ACCEPTED;
                            }
                        }
                        guiCore_CallEventHandler((guiGenericWidget_t *)pSpinEdit,WEVENT_ACTIVE_CHANGED);

                        if (pSpinEdit->properties & WP_SELECT_IS_ACTIVATE)
                        {
                            pSpinEdit->state &= ~WF_IS_SELECTED;
                            pSpinEdit->redrawFlags |= WF_REDRAW_SELECTION;
                            guiCore_CallEventHandler((guiGenericWidget_t *)pSpinEdit, WEVENT_SELECTED_CHANGED);
                            //processResult = EVENT_FLAG_NOT_USED;  // already set to this value
                        }
                        else
                        {
                            processResult = EVENT_FLAG_ACCEPTED;
                        }
                    }
                    else if (buttonCode & GUI_BTN_LEFT)
                    {
                        guiSpinEdit_MoveActiveDigit(pSpinEdit,1);
                        processResult = EVENT_FLAG_ACCEPTED;
                    }
                    else if (buttonCode & GUI_BTN_RIGHT)
                    {
                        guiSpinEdit_MoveActiveDigit(pSpinEdit,-1);
                        processResult = EVENT_FLAG_ACCEPTED;
                    }
                    else if (encoderDelta != 0)
                    {
                        // TODO - update callback
                        guiSpinEdit_IncrementValue(pSpinEdit, encoderDelta);
                        processResult = EVENT_FLAG_ACCEPTED;
                    }
                    break;
                default:
                    if (event.type == GUI_EVENT_SELECT)
                    {
                        pSpinEdit->state |= WF_IS_SELECTED;
                        pSpinEdit->redrawFlags |= WF_REDRAW_SELECTION;
                        guiCore_CallEventHandler((guiGenericWidget_t *)pSpinEdit,WEVENT_SELECTED_CHANGED);
                        if (pSpinEdit->properties & WP_SELECT_IS_ACTIVATE)
                        {
                            pSpinEdit->state |= WF_IS_ACTIVE;
                            pSpinEdit->savedValue = pSpinEdit->value;
                            pSpinEdit->redrawFlags |= WF_REDRAW_CONTENT;
                            guiCore_CallEventHandler((guiGenericWidget_t *)pSpinEdit,WEVENT_ACTIVE_CHANGED);
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


void guiSpinEdit_Initialize(guiSpinEdit_t *pSpinEdit)
{
    //----------------------//
    // Fields, common for all widgets
    pSpinEdit->type = WT_LISTBOX;
    pSpinEdit->redrawFlags = 0;
    pSpinEdit->tabIndex = 0;
    pSpinEdit->properties = 0;
    pSpinEdit->tag = 0;
    pSpinEdit->processEvent = guiSpinEdit_ProcessEvent;
    pSpinEdit->handlers.count = 0;

    //----------------------//

    pSpinEdit->x_pos = 0;
    pSpinEdit->y_pos = 0;
    pSpinEdit->state = 0;

    pSpinEdit->width = 80;
    pSpinEdit->pFont = &font_8x12;
    pSpinEdit->height = font_8x12.height + 2;
    pSpinEdit->dotPosition = 0;
    pSpinEdit->blinkInterval = 0;
    pSpinEdit->activeDigit = 0;
    pSpinEdit->value = 0;
    pSpinEdit->string[0] = '\0';
    pSpinEdit->digitsToUse = 0;
    pSpinEdit->minDigitsToDisplay = 1;
}


void guiSpinEdit_SetValue(guiSpinEdit_t *pSpinEdit, int32_t newValue)
{
    if (pSpinEdit->value != newValue)
    {
        pSpinEdit->value = newValue;
        pSpinEdit->digitsToUse = i32toa_align_right(pSpinEdit->value, pSpinEdit->string, \
                                                    SPINEDIT_STRING_LENGTH | NO_TERMINATING_ZERO, pSpinEdit->minDigitsToDisplay);
        if (pSpinEdit->activeDigit >= pSpinEdit->digitsToUse)
            pSpinEdit->activeDigit = pSpinEdit->digitsToUse - 1;
        pSpinEdit->redrawFlags |= WF_REDRAW_CONTENT;
    }
}

void guiSpinEdit_SetVisible(guiSpinEdit_t* pSpinEdit, uint8_t visibleMode)
{
    if (visibleMode)
    {
        pSpinEdit->properties |= WP_IS_VISIBLE;
    }
    else
    {
        pSpinEdit->properties &= ~WP_IS_VISIBLE;
        guiCore_RequestFullRedraw();
    }
}

void guiSpinBox_SetMaxValue(guiSpinEdit_t *pSpinEdit, int32_t newValue)
{
    // TODO
}

void guiSpinBox_SetMinValue(guiSpinEdit_t *pSpinEdit, int32_t newValue)
{
    // TODO
}

