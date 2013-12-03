
#include <stdint.h>
#include "guiGraphPrimitives.h"
#include "guiGraphHAL.h"
#include "guiFonts.h"



color_t penColor;             // Pen is used for drawing lines, frames, circles, etc
color_t fillColor;            // Used for filling objects
const tFont* currentFont;     // Font that currently used
color_t fontForeColor;        // Used when printing text
color_t fontBackColor;        //
uint8_t fontOutputMode;       // Specifies text background - OUTPUT_MODE_TRANSPARENT or OUTPUT_MODE_SOLID




//-------------------------------------------------------//
// Fills a rectangle with fillColor
//-------------------------------------------------------//
void guiGraph_fillRect(rect_t* rect)
{
	uint16_t x,y;
    rect_t drawRect = *rect;
    for (x=drawRect.x1; x<=drawRect.x2; x++)
        for (y=drawRect.y1; y<=drawRect.y2; y++)
            guiGraph_putPixel(x,y,fillColor);
}

//-------------------------------------------------------//
// Draws horizontal line with penColor
//-------------------------------------------------------//
void guiGraph_drawHorLine(uint16_t x, uint16_t y, uint16_t length)
{
    while(length--)
    {
        guiGraph_putPixel(x,y,penColor);
        x++;
    }
}

//-------------------------------------------------------//
// Draws vertical line with penColor
//-------------------------------------------------------//
void guiGraph_drawVertLine(uint16_t x, uint16_t y, uint16_t length)
{
    while(length--)
    {
        guiGraph_putPixel(x,y,penColor);
        y++;
    }
}

//-------------------------------------------------------//
// Draws rectangle line with penColor
//-------------------------------------------------------//
void guiGraph_drawRect(rect_t *rect)
{
    uint16_t width, height;
    if ((rect->x1 > rect->x2) || (rect->y1 > rect->y2))
        return;
    width = rect->x2 - rect->x1 + 1;
    height = rect->y2 - rect->y1 + 1;
    guiGraph_drawVertLine(rect->x1,rect->y1,height);
    guiGraph_drawVertLine(rect->x2,rect->y1,height);
    guiGraph_drawHorLine(rect->x1,rect->y1,width);
    guiGraph_drawHorLine(rect->x1,rect->y2,width);
}



//=======================================================//
//=======================================================//
//  FONTS


//-------------------------------------------------------//
// Draws packed image, coordinates are absolute.
// Image is printed using:
//  - penColor
//  - altPenColor
//  - outputMode
//-------------------------------------------------------//
void guiGraph_drawPackedImage(const uint8_t *img, uint16_t x_pos, uint16_t y_pos, uint16_t img_width, uint16_t img_height)
{
    uint8_t bit_mask = 0x01;
    uint8_t temp;
    uint16_t img_index;
    uint16_t img_start_index = 0;
    uint16_t x;
    uint16_t y_fin = y_pos + img_height;

    while(y_pos < y_fin)
    {
        img_index = img_start_index;
        for (x = x_pos; x < x_pos + img_width; x++)
        {
            temp = img[img_index++];
            if (temp & bit_mask)
                guiGraph_putPixel(x,y_pos,fontForeColor);
            else if (fontOutputMode == FONT_OUTPUT_SOLID)
                guiGraph_putPixel(x,y_pos,fontBackColor);
        }
        y_pos++;
        if (bit_mask == 0x80)
        {
            bit_mask = 0x01;
            img_start_index += img_width;
        }
        else
        {
            bit_mask = bit_mask << 1;
        }
    }
}


//-------------------------------------------------------//
// Rerurns pointer to a font item with specified acode.
// If no item with such code is found, 0 is returned.
// TODO - use dichotomy
//-------------------------------------------------------//
const tFontItem* guiGraph_getFontItem(const tFont *font, uint8_t code)
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
// Prints text string using X and Y coordinates
//-------------------------------------------------------//
void guiGraph_printTextXY(uint16_t x, uint16_t y, char *string)
{
    uint8_t index = 0;
    const tFontItem *fontItem;
    char c;

    while((c = string[index++]))
    {
        fontItem = guiGraph_getFontItem(currentFont, c);
        if (fontItem != 0)
        {
            guiGraph_drawPackedImage(fontItem->data,x,y,fontItem->width,currentFont->height);
            x += fontItem->width;
        }
    }
}



//-------------------------------------------------------//
// Prints text string using aligment inside a rectangle.
// Rectangle is used only for aligment.
//-------------------------------------------------------//
// TODO



