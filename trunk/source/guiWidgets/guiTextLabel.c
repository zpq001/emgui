#include <stdio.h>

#include "guiCore.h"
#include "guiWidgetCommon.h"
#include "guiTextLabel.h"

#include "guiFonts.h"
#include "guiFontUtils.h"
#include "guiGraphUtils.h"



static void guiTextLabel_Draw(guiTextLabel_t* pTextLabel)
{
    uint8_t mode = (pTextLabel->state & WF_IS_SELECTED) ? IMAGE_MODE_INVERSE : IMAGE_MODE_NORM;
    if (pTextLabel->string)
        guiFont_PrintString(pTextLabel->x_pos, pTextLabel->y_pos, pTextLabel->string, pTextLabel->pfont, mode);
}

// CHECKME - Possibly create common select/deselect handler for all widgets ?
static void guiTextLabel_Select(guiTextLabel_t* pTextLabel, uint8_t mode)
{

    if ((mode != 0) && ((pTextLabel->state & WF_IS_SELECTED) == 0))  // CHECKME - mode
    {
        pTextLabel->state |= WF_IS_SELECTED;
        pTextLabel->redrawFlags |= WF_REDRAW;
    }
    else if ((mode == 0) && ((pTextLabel->state & WF_IS_SELECTED) != 0))
    {
             pTextLabel->state &= ~WF_IS_SELECTED;
             pTextLabel->redrawFlags |= WF_REDRAW;
    }

}

static uint8_t guiTextLabel_ProcessEvent(guiGenericWidget_t *pWidget, guiEvent_t event)
{
    guiTextLabel_t *pThis = (guiTextLabel_t *)pWidget;
    switch(event.type)
    {
        case GUI_EVENT_DRAW_ALL:
            // Text label has no extra graphic elements
            // Fall downto EVENT_DRAW
            pThis->redrawFlags |= WF_REDRAW;
        case GUI_EVENT_DRAW:
            if ((pThis->properties & WP_IS_VISIBLE) == 0)
                break;
            if (pThis->redrawFlags & WF_REDRAW)
                guiTextLabel_Draw(pThis);
            pThis->redrawFlags = 0;
            break;
        case GUI_EVENT_SELECT:
            guiTextLabel_Select(pThis,1);
            break;
        case GUI_EVENT_DESELECT:
            guiTextLabel_Select(pThis,0);
            break;
        case GUI_EVENT_HIDE:
            if (pThis->properties & WP_IS_VISIBLE)
            {
                pThis->properties &= ~WP_IS_VISIBLE;
                guiCore_RequestFullRedraw();
            }
            break;
        case GUI_EVENT_SHOW:
            if ((pThis->properties & WP_IS_VISIBLE) == 0)
            {
                pThis->properties |= WP_IS_VISIBLE;
                pThis->redrawFlags |= WF_REDRAW;
            }
            break;
    }
    guiCore_CallEventHandler(pWidget,event.type);
    return 0;
}


void guiTextLabel_Initialize(guiTextLabel_t *pTextLabel)
{
    //----------------------//
    // Fields, common for all widgets
    pTextLabel->type = WT_TEXT_LABEL;
    pTextLabel->redrawFlags = 0;
    pTextLabel->tabIndex = 0;
    pTextLabel->properties = 0;
    pTextLabel->tag = 0;
    pTextLabel->processEvent = guiTextLabel_ProcessEvent;
    pTextLabel->handlers.count = 0;
    //----------------------//

    pTextLabel->x_pos = 0;
    pTextLabel->y_pos = 0;
    pTextLabel->state = 0;
    pTextLabel->pfont = 0;
    pTextLabel->string = 0;
}




