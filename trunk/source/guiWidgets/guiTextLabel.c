/**********************************************************
    Module TextLabel




**********************************************************/

#include <stdint.h>
#include "guiEvents.h"
#include "guiWidgets.h"
#include "guiTextLabel.h"
#include "guiFonts.h"
#include "guiGraphPrimitives.h"
#include "guiGraphWidgets.h"




static uint8_t guiTextLabel_ProcessEvent(guiGenericWidget_t *widget, guiEvent_t event)
{
    guiTextLabel_t *textLabel = (guiTextLabel_t *)widget;
    switch (event.type)
    {
        case GUI_EVENT_DRAW:
            // Check visibility - already done by core.
            //if (textLabel->isVisible == 0)
            //    break;
            // Check if full redraw is required
            if (textLabel->redrawForced)
            {
                // Widget must be fully redrawn - set all flags
                textLabel->redrawFlags = TEXT_LABEL_REDRAW_FOCUS |
                                         TEXT_LABEL_REDRAW_TEXT;
            }
            guiGraph_DrawTextLabel(textLabel);

            // TODO - callback

            // Reset flags
            textLabel->redrawFlags = 0;
            textLabel->redrawRequired = 0;
            break;
    }
    return 0;
}


void guiTextLabel_Initialize(guiTextLabel_t *textLabel, guiGenericWidget_t *parent)
{
    textLabel->parent = parent;
    textLabel->acceptFocus = 0;
    textLabel->acceptFocusByTab = 0;
    textLabel->isContainer = 0;
    textLabel->isFocused = 0;
    textLabel->isVisible = 1;
    textLabel->redrawForced = 0;
    textLabel->redrawRequired = 0;
    textLabel->tag = 0;
    textLabel->tabIndex = 0;
    textLabel->processEvent = guiTextLabel_ProcessEvent;
    textLabel->handlers.count = 0;


    textLabel->redrawFlags = 0;
    textLabel->x = 0;
    textLabel->y = 0;
    textLabel->width = 40;
    textLabel->height = 15;
    textLabel->alignment = ALIGN_TOP_LEFT;
    textLabel->font = &font_h12;
    textLabel->text = 0;
}


void guiTextLabel_SetRedrawFlags(guiTextLabel_t *textLabel, uint8_t flags)
{
    if (flags)
    {
        textLabel->redrawFlags |= flags;
        textLabel->redrawRequired = 1;
    }
}

