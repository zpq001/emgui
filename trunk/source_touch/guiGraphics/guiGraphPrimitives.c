
#include <stdint.h>
#include "guiGraphPrimitives.h"
#include "guiGraphHAL.h"
#include "guiFonts.h"

rect_t drawArea;		// absolute coordinates of rectangle, inside which drawing is allowed
                        // All changes to this should be done through guiGraph_setDrawingArea()


color_t penColor;             // Pen is used for drawing lines, frames, circles, etc
const tFont* currentFont;     // Font that currently used
color_t fontForeColor;        // Used when printing text
color_t fontBackColor;        //
uint8_t fontOutputMode;       // Specifies text background - OUTPUT_MODE_TRANSPARENT or OUTPUT_MODE_SOLID



//-------------------------------------------------------//
// Sets global drawing area
// Coordinates are absolute
//-------------------------------------------------------//
void guiGraph_setDrawingArea(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    drawArea.x1 = x1;
    drawArea.y1 = y1;
    drawArea.x2 = (x2 >= LCD_XSIZE) ? LCD_XSIZE - 1 : x2;
    drawArea.y2 = (y2 >= LCD_YSIZE) ? LCD_YSIZE - 1 : y2;
}


//-------------------------------------------------------//
// Converts rect coordinates which are relative to drawArea
// to absolute values.
// Converted coodinates are bound by drawArea
// Returns zero if there is no intersection
//-------------------------------------------------------//
static uint8_t guiGraph_makeAbsoluteRect(rect_t* rect)
{
    rect->x1 = drawArea.x1 + rect->x1;
    if (rect->x1 > drawArea.x2) return 0;

    rect->y1 = drawArea.y1 + rect->y1;
    if (rect->y1 > drawArea.y2) return 0;

    rect->x2 = drawArea.x1 + rect->x2;
    if (rect->x2 > drawArea.x2) rect->x2 = drawArea.x2;

    rect->y2 = drawArea.y1 + rect->y2;
    if (rect->y2 > drawArea.y2) rect->y2 = drawArea.y2;

    return 1;
}

//-------------------------------------------------------//
// Converts X,Y coordinates which are relative to drawArea
// to absolute values.
// Converted coodinates are bound by drawArea
// Returns zero if there is no intersection
//-------------------------------------------------------//
static uint8_t guiGraph_makeAbsoluteXY(uint16_t *x, uint16_t *y)
{
    *x = drawArea.x1 + *x;
    if (*x > drawArea.x2) return 0;

    *y = drawArea.y1 + *y;
    if (*y > drawArea.y2) return 0;

    return 1;
}


//-------------------------------------------------------//
// Fills a rectangle with specified color
// Rectangle coordinates are relative to drawArea
// Rectangle is checked and bounded before painting
//-------------------------------------------------------//
void guiGraph_fillRect(rect_t* rect, color_t color)
{
	uint16_t x,y;
    rect_t drawRect = *rect;
    if (guiGraph_makeAbsoluteRect(&drawRect))   // convert relative coordinates to absolute
    {
        for (x=drawRect.x1; x<=drawRect.x2; x++)
            for (y=drawRect.y1; y<=drawRect.y2; y++)
                guiGraph_putPixel(x,y,color);
    }
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
static void drawPackedImage(const uint8_t *img, uint16_t x_pos, uint16_t y_pos, uint16_t img_width, uint16_t img_height)
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
        // Check Y-range
        if ((y_pos >= drawArea.y1) && (y_pos <= drawArea.y2))
        {
            for (x = x_pos; x < x_pos + img_width; x++)
            {
                temp = img[img_index++];
                // Check X-range
                if ((x_pos >= drawArea.x1) && (x_pos <= drawArea.x2))
                {
                    if (temp & bit_mask)
                        guiGraph_putPixel(x,y_pos,fontForeColor);
                    else if (fontOutputMode == FONT_OUTPUT_SOLID)
                        guiGraph_putPixel(x,y_pos,fontBackColor);
                }
            }
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
// Bounded by drawArea
//-------------------------------------------------------//
void guiGraph_printTextXY(uint16_t x, uint16_t y, char *string)
{
    uint8_t index = 0;
    const tFontItem *fontItem;
    char c;
    if (guiGraph_makeAbsoluteXY(&x, &y))   // convert relative coordinates to absolute
    {
        while((c = string[index++]))
        {
            fontItem = guiGraph_getFontItem(currentFont, c);
            if (fontItem != 0)
            {
                drawPackedImage(fontItem->data,x,y,fontItem->width,currentFont->height);
                x += fontItem->width;
                if (x > drawArea.x2)
                    break;
            }
        }
    }
}



//-------------------------------------------------------//
// Prints text string using aligment inside a rectangle.
// Rectangle is used only for aligment.
//-------------------------------------------------------//
// TODO



