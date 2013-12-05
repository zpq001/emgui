/**********************************************************
  Module guiGraphWidgets contains functions for drawing widgets.



**********************************************************/

#include <stdint.h>
#include "guiGraphHAL.h"
#include "guiGraphPrimitives.h"
#include "guiFonts.h"
#include "guiWidgets.h"





void guiGraph_DrawTextLabel(guiTextLabel_t *textLabel)
{
    rect_t rect;

    // Process redraw flags - TODO
    // Check isVisible

    // Erase rectangle
    LCD_SetPixelOutputMode(PIXEL_MODE_REWRITE);
    LCD_FillRect(textLabel->x,textLabel->y,textLabel->width,textLabel->height,FILL_WITH_WHITE);

    // Draw focus
    if (textLabel->isFocused)
    {
        LCD_SetLineStyle(LINE_STYLE_DOTTED);
        LCD_DrawRect(textLabel->x,textLabel->y,textLabel->width,textLabel->height,1);
    }

    // Draw string
    if (textLabel->text)
    {
        LCD_SetPixelOutputMode(PIXEL_MODE_OR);
        LCD_SetFont(textLabel->font);
        rect.x1 = textLabel->x;
        rect.y1 = textLabel->y;
        rect.x2 = textLabel->x + textLabel->width - 1;
        rect.y2 = textLabel->y + textLabel->height - 1;
        LCD_PrintStringAligned(textLabel->text, &rect, textLabel->alignment, IMAGE_MODE_NORMAL);
    }

    // Reset flags
    // TODO
}







