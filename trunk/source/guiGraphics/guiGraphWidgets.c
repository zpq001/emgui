/**********************************************************
  Module guiGraphWidgets contains functions for drawing widgets. (hi, Cap!)



**********************************************************/

#include <stdint.h>
#include "guiGraphHAL.h"
#include "guiGraphPrimitives.h"
#include "guiFonts.h"
#include "guiWidgets.h"

#include "guiTextLabel.h"



/*
        There are two sources of widget redraw requests:

        First one is the widget itself - if some widget internal state is changed, it sets "redrawRequired" flag,
    thus indicating the core it's need to redraw. Widget also sets some internal redraw flags, which are analyzed
    only in appropriate draw function.

        Second is the GUI core. When GUI core discovers that widget should be redrawn by parent request, or for
    other reason, the core sets both "redrawRequired" and "redrawForced" flags.

    The "redrawForced" flag is set and cleared by core itself. The "redrawRequired" can be set by
    both GUI core and widget, but it should be cleared by widget after completing draw procedure and
    executing callback function.

*/




//-------------------------------------------------------//
// Draw a form
//
//
//-------------------------------------------------------//
void guiGraph_DrawForm(guiForm_t *form)
{




}



//-------------------------------------------------------//
// Draw a textLabel
//
//
//-------------------------------------------------------//
void guiGraph_DrawTextLabel(guiTextLabel_t *textLabel)
{
    rect_t rect;

    if (textLabel->redrawFlags & TEXT_LABEL_REDRAW_FOCUS)
    {
        LCD_SetPixelOutputMode(PIXEL_MODE_REWRITE);
        if (textLabel->isFocused)
        {
            LCD_SetLineStyle(LINE_STYLE_DOTTED);
            LCD_DrawRect(textLabel->x,textLabel->y,textLabel->width,textLabel->height,1);
        }
        else
        {
            // TODO - add hasFrame
            LCD_SetLineStyle(LINE_STYLE_SOLID);
            LCD_DrawRect(textLabel->x,textLabel->y,textLabel->width,textLabel->height,1);
        }
    }


    if (textLabel->redrawFlags & TEXT_LABEL_REDRAW_TEXT)
    {
        // Erase rectangle
        LCD_SetPixelOutputMode(PIXEL_MODE_REWRITE);
        LCD_FillRect(textLabel->x+1,textLabel->y+1,textLabel->width-2,textLabel->height-2,FILL_WITH_WHITE);

        // Draw string
        if (textLabel->text)
        {
            LCD_SetPixelOutputMode(PIXEL_MODE_OR);
            LCD_SetFont(textLabel->font);
            rect.x1 = textLabel->x+1;
            rect.y1 = textLabel->y+1;
            rect.x2 = textLabel->x + textLabel->width - 2;
            rect.y2 = textLabel->y + textLabel->height - 2;
            LCD_PrintStringAligned(textLabel->text, &rect, textLabel->alignment, IMAGE_MODE_NORMAL);
        }
    }
}







