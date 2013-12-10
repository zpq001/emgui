/**********************************************************
  Module guiGraphWidgets contains functions for drawing widgets. (hi, Cap!)



**********************************************************/

#include <stdint.h>
#include "guiGraphHAL.h"
#include "guiGraphPrimitives.h"
#include "guiFonts.h"
#include "guiImages.h"
#include "guiWidgets.h"

#include "guiForm.h"
#include "guiTextLabel.h"
#include "guiCheckBox.h"


int16_t wx;
int16_t wy;


//-------------------------------------------------------//
// Sets point (0,0) of coordinate system
// Parameters x and y must be absolute values
// Widget's geometry is relative to (wx,wy)
//-------------------------------------------------------//
void guiGraph_SetBaseXY(int16_t x, int16_t y)
{
    wx = x;
    wy = y;
}

//-------------------------------------------------------//
// Sets point (0,0) of coordinate system
//-------------------------------------------------------//
void guiGraph_OffsetBaseXY(int16_t dx, int16_t dy)
{
    wx += dx;
    wy += dy;
}


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
    if (form->redrawFlags & FORM_REDRAW_FOCUS)
    {
        LCD_SetPixelOutputMode(PIXEL_MODE_REWRITE);
        if (form->isFocused)
        {
            LCD_SetLineStyle(LINE_STYLE_DOTTED);
            LCD_DrawRect(wx,wy,form->width,form->height,1);
        }
        else
        {
            LCD_SetLineStyle(LINE_STYLE_SOLID);
            if (form->hasFrame)
                LCD_DrawRect(wx,wy,form->width,form->height,1);
            else
                LCD_DrawRect(wx,wy,form->width,form->height,0);
        }
    }

    if (form->redrawFlags & FORM_REDRAW_BACKGROUND)
    {
        // Erase rectangle
        LCD_SetPixelOutputMode(PIXEL_MODE_REWRITE);
        LCD_FillRect(wx+1,wy+1,form->width-2,form->height-2,FILL_WITH_WHITE);
    }
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
            LCD_DrawRect(wx,wy,textLabel->width,textLabel->height,1);
        }
        else
        {
            LCD_SetLineStyle(LINE_STYLE_SOLID);
            if (textLabel->hasFrame)
                LCD_DrawRect(wx,wy,textLabel->width,textLabel->height,1);
            else
                LCD_DrawRect(wx,wy,textLabel->width,textLabel->height,0);
        }
    }


    if (textLabel->redrawFlags & TEXT_LABEL_REDRAW_TEXT)
    {
        // Erase rectangle
        LCD_SetPixelOutputMode(PIXEL_MODE_REWRITE);
        LCD_FillRect(wx+1,wy+1,textLabel->width-2,textLabel->height-2,FILL_WITH_WHITE);

        // Draw string
        if (textLabel->text)
        {
            LCD_SetPixelOutputMode(PIXEL_MODE_OR);
            LCD_SetFont(textLabel->font);
            rect.x1 = wx + 1 + TEXT_LABEL_TEXT_MARGIN;
            rect.y1 = wy + 1;
            rect.x2 = wx + textLabel->width - 2 - TEXT_LABEL_TEXT_MARGIN;
            rect.y2 = wy + textLabel->height - 2;
            LCD_PrintStringAligned(textLabel->text, &rect, textLabel->alignment, IMAGE_MODE_NORMAL);
        }
    }
}



void guiGraph_DrawCheckBox(guiCheckBox_t * checkBox)
{
    int8_t y_aligned;
    rect_t rect;
    uint8_t *img;

    y_aligned = checkBox->height - CHECKBOX_GRAPH_YSIZE;
    y_aligned /= 2;
    y_aligned = wy + y_aligned;

    if (checkBox->redrawFlags & CHECKBOX_REDRAW_FOCUS)
    {
        LCD_SetPixelOutputMode(PIXEL_MODE_REWRITE);
        if (checkBox->isFocused)
        {
            LCD_SetLineStyle(LINE_STYLE_DOTTED);
            LCD_DrawRect(wx,wy,checkBox->width,checkBox->height,1);
        }
        else
        {
            LCD_SetLineStyle(LINE_STYLE_SOLID);
            if (checkBox->hasFrame)
                LCD_DrawRect(wx,wy,checkBox->width,checkBox->height,1);
            else
                LCD_DrawRect(wx,wy,checkBox->width,checkBox->height,0);
        }
    }


    if (checkBox->redrawFlags & CHECKBOX_REDRAW_BACKGROUND)
    {
        // Erase rectangle
        LCD_SetPixelOutputMode(PIXEL_MODE_REWRITE);
        LCD_FillRect(wx+1,wy+1,checkBox->width-2,checkBox->height-2,FILL_WITH_WHITE);

        // Draw string
        if (checkBox->text)
        {
            LCD_SetPixelOutputMode(PIXEL_MODE_OR);
            LCD_SetFont(checkBox->font);
            rect.x1 = wx + 2 + CHECKBOX_TEXT_MARGIN + CHECKBOX_GRAPH_XSIZE;
            rect.y1 = wy + 1;
            rect.x2 = wx + checkBox->width - 2;
            rect.y2 = wy + checkBox->height - 2;
            LCD_PrintStringAligned(checkBox->text, &rect, checkBox->textAlignment, IMAGE_MODE_NORMAL);
        }

        // Draw rectangle frame
        //LCD_SetPixelOutputMode(PIXEL_MODE_REWRITE);
        //LCD_DrawRect(wx + 2,y_aligned,CHECKBOX_GRAPH_XSIZE,CHECKBOX_GRAPH_YSIZE,1);
    }

    LCD_SetPixelOutputMode(PIXEL_MODE_REWRITE);
    if (checkBox->redrawFlags & CHECKBOX_REDRAW_STATE)
    {
        img = (checkBox->isChecked) ? CHECKBOX_IMG_CHECKED :
                                      CHECKBOX_IMG_EMPTY;
        LCD_DrawImage(img,wx+2,y_aligned,CHECKBOX_GRAPH_XSIZE, CHECKBOX_GRAPH_YSIZE,IMAGE_MODE_NORMAL);
    }


}



