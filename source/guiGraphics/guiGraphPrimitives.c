/**********************************************************
  Module guiGraphPrimitives contains low-level LCD routines.

  LCD functions description:
    - Pixel output mode specifies how data in the buffer is updated.
        Can be PIXEL_MODE_REWRITE - old pixel value is rewrited with new one.
               PIXEL_MODE_AND - old pixel value is ANDed with new value
               PIXEL_MODE_OR - old pixel value is ORed with new value
               PIXEL_MODE_XOR - old pixel value is XORed with new value
        Every function that modiifes LCD buffer data uses these modes.
    - pixelValue is an argument
    - LCD_currentFont specifies font that is used for text
      Can be set directly
    - LCD_lineStyle specifies how lines are drawed

**********************************************************/



#include <stdint.h>
#include "guiGraphPrimitives.h"
#include "guiGraphHAL.h"
#include "guiFonts.h"


const tFont* LCD_currentFont;



//-------------------------------------------------------//
// Draws a rectangle using LCD_lineStyle
//	Parameters:
//		uint8_t x_pos	- pixel x coordinate
//		uint8_t y_pos	- pixel y coordinate
//      uint8_t width
//      uint8_t height
//      pixelValue  	- new pixel value, 1 or 0
// Pixel output mode is set by calling LCD_setPixelOutputMode()
//-------------------------------------------------------//
void LCD_DrawRect(uint8_t x_pos, uint8_t y_pos, uint8_t width, uint8_t height, uint8_t pixelValue)
{
    LCD_DrawHorLine(x_pos,y_pos,width,pixelValue);
    LCD_DrawHorLine(x_pos,y_pos + height - 1,width,pixelValue);
    LCD_DrawVertLine(x_pos,y_pos,height - 1,pixelValue);
    LCD_DrawVertLine(x_pos + width - 1,y_pos, height - 1,pixelValue);
}



//-------------------------------------------------------//
// Rerurns pointer to a font item with specified acode.
// If no item with such code is found, 0 is returned.
// TODO - use dichotomy
//-------------------------------------------------------//
const tFontItem* LCD_GetFontItem(const tFont *font, uint8_t code)
{
    tFontItem* itemPtr = 0;
    uint8_t i;
    for (i=0;i<font->charCount;i++)
    {
        itemPtr = (tFontItem*)&font->chars[i];
        if (itemPtr->code == code)
            break;
    }
    return itemPtr;
}



//-------------------------------------------------------//
// Prints a string with LCD_currentFont at current position
// mode:
//     IMAGE_MODE_NORMAL - normal images
//     IMAGE_MODE_INVERSE - inversed images
//-------------------------------------------------------//
void LCD_PrintString(char *str, uint8_t x, uint8_t y, uint8_t mode)
{
    uint8_t index = 0;
    const tFontItem *fontItem;
    char c;

    while((c = str[index++]))
    {
        fontItem = LCD_GetFontItem(LCD_currentFont, c);
        if (fontItem != 0)
        {
            LCD_DrawImage(fontItem->data, x, y, fontItem->width, LCD_currentFont->height, mode);
            x += fontItem->width + LCD_currentFont->spacing;
        }
    }
}




