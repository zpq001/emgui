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
// Sets current font for text printing
//
//-------------------------------------------------------//
void LCD_SetFont(const tFont *newFont)
{
    if (newFont != LCD_currentFont)
        LCD_currentFont = newFont;
}


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
// Rerurns width and offset of a font item
// Font array MUST be sorted by code.
// If no item with such code is found, 0 is returned.
// Using binary search, http://kvodo.ru/dvoichnyiy-poisk.html
//-------------------------------------------------------//
uint8_t LCD_GetFontItem(const tFont *font, uint8_t code, uint8_t *width, uint16_t *offset)
{
    uint8_t itemCode;
    uint8_t start_index = 0;
    uint8_t end_index;
    uint8_t i;

    if (font->codeTable == 0)
    {
        // Font char set is a contiguous array
        start_index = font->firstCharCode;
        end_index = start_index + (font->charCount - 1);
        if ((code < start_index) || (code > end_index))
            return 0;
        else
        {
            i = code-start_index;
            if (offset != 0)
            {
                if (font->offsetTable == 0)
                    *offset = (uint16_t)i * font->bytesPerChar;
                else
                    *offset = font->offsetTable[i];
            }
            if (font->widthTable == 0)
                *width = font->width;
            else
                *width = font->widthTable[i];
            return 1;
        }
    }
    else
    {
        end_index = font->charCount;
        // Font char set is defined by charTable
        while (start_index < end_index)
        {
            i = start_index + (end_index - start_index) / 2;
            itemCode = font->codeTable[i];
            if (code < itemCode)
                end_index = i;
            else if (code > itemCode)
                start_index = i+1;
            else
            {
                // Found
                if (offset != 0)
                    // Font must have valid offsetTable when codeTable is used
                    *offset = font->offsetTable[i];
                if (font->widthTable == 0)
                    *width = font->width;
                else
                    *width = font->widthTable[i];
                return 1;
            }
        }
    }
    return 0;
}

//-------------------------------------------------------//
// Rerurns length of a string in pixels
//
//-------------------------------------------------------//
uint8_t LCD_GetStringWidth(const tFont *font, char *string)
{
    uint8_t length = 0;
    uint8_t index = 0;
    uint8_t charWidth;
    char c;

    while((c = string[index++]))
    {
        if (LCD_GetFontItem(LCD_currentFont, c, &charWidth, 0))
            length += charWidth + font->spacing;
    }

    length -= font->spacing;
    return length;
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
    uint8_t charWidth;
    uint16_t charOffset;
    char c;

    while((c = str[index++]))
    {

        if (LCD_GetFontItem(LCD_currentFont, c, &charWidth, &charOffset))
        {
            LCD_DrawImage(&LCD_currentFont->data[charOffset], x, y, charWidth, LCD_currentFont->height, mode);
            x += charWidth + LCD_currentFont->spacing;
        }
    }
}



//-------------------------------------------------------//
// Prints a string with LCD_currentFont inside rectangle using
//  alignment
// mode:
//     IMAGE_MODE_NORMAL - normal images
//     IMAGE_MODE_INVERSE - inversed images
//-------------------------------------------------------//
void LCD_PrintStringAligned(char *str, rect_t *rect, uint8_t alignment, uint8_t mode)
{
    uint8_t index = 0;
    uint8_t charWidth;
    uint16_t charOffset;
    char c;
    int16_t x_aligned, y_aligned;
    int16_t strWidthPx;

    // Find horizontal position
    if (alignment & ALIGN_LEFT)
    {
        x_aligned = rect->x1;       // pretty simple - take left rect border as starting point
    }
    else
    {
        // We need to compute length of whole string in pixels
        strWidthPx = LCD_GetStringWidth(LCD_currentFont,str);
        if (alignment & ALIGN_RIGHT)
            x_aligned = (int16_t)rect->x2 + 1 - strWidthPx;
        else
            x_aligned = rect->x1 + ((int16_t)(rect->x2 - rect->x1 + 1) - strWidthPx) / 2;
    }

    // Find vertical position
    if (alignment & ALIGN_TOP)
    {
        y_aligned = rect->y1;
    }
    else if (alignment & ALIGN_BOTTOM)
    {
        y_aligned = (int16_t)rect->y2 + 1 - LCD_currentFont->height;
    }
    else
    {
        y_aligned = rect->y1 + ((int16_t)(rect->y2 - rect->y1 + 1) - LCD_currentFont->height) / 2;
    }

    // Now print string
    while((c = str[index++]))
    {
        if (LCD_GetFontItem(LCD_currentFont, c, &charWidth, &charOffset))
        {
            LCD_DrawImage(&LCD_currentFont->data[charOffset], x_aligned, y_aligned, charWidth, LCD_currentFont->height, mode);
            x_aligned += charWidth + LCD_currentFont->spacing;
        }
    }
}





