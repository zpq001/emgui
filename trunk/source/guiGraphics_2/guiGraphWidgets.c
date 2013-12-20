/**********************************************************
  Module guiGraphWidgets contains functions for drawing widgets. (hi, Cap!)



**********************************************************/

#include <stdint.h>
#include "guiGraphHAL.h"
#include "guiGraphPrimitives.h"
#include "guiGraphWidgets.h"
#include "guiFonts.h"
#include "guiImages.h"
#include "guiWidgets.h"



int16_t wx;
int16_t wy;

const color_t colorPalette1[COLOR_PALETTE_SIZE] = {
    colorFromRgb(210,210,210),      // COLOR_INDEX_WIDGET_BACKGROUND
    colorFromRgb(220,220,220),      // COLOR_INDEX_BUTTON_BACKGROUND
    colorFromRgb(240,240,240),      // COLOR_INDEX_3DFRAME_LIGHT1
    colorFromRgb(200,200,200),      // COLOR_INDEX_3DFRAME_LIGHT2
    colorFromRgb(100,100,100),      // COLOR_INDEX_3DFRAME_DARK1
    colorFromRgb(150,150,150),      // COLOR_INDEX_3DFRAME_DARK2
    colorFromRgb(0,0,0),            // COLOR_INDEX_FOCUS_FRAME
    colorFromRgb(0,0,0),            // COLOR_INDEX_TEXT_ACTIVE
};

color_t *colorPalette = (color_t *)colorPalette1;




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



//-------------------------------------------------------//
// Draws nice 3-D frame
// Line style is set to SOLID
//-------------------------------------------------------//
void guiGraph_Draw3DFrame(rect_t *rect, uint8_t frameState)
{
    uint8_t c1,c2,c3,c4;
    switch (frameState)
    {
        case FRAME3D_SUNKEN:
            c1 = COLOR_INDEX_3DFRAME_DARK2;
            c2 = COLOR_INDEX_3DFRAME_DARK1;
            c3 = COLOR_INDEX_3DFRAME_LIGHT1;
            c4 = COLOR_INDEX_3DFRAME_LIGHT2;
            break;
        default:        // Raised
            c1 = COLOR_INDEX_3DFRAME_LIGHT1;
            c2 = COLOR_INDEX_3DFRAME_LIGHT2;
            c3 = COLOR_INDEX_3DFRAME_DARK1;
            c4 = COLOR_INDEX_3DFRAME_DARK2;
    }

    LCD_SetLineStyle(LINE_STYLE_SOLID);

    // top, left
    LCD_SetPenColor(colorPalette1[c1]);
    LCD_DrawHorLine(rect->x1, rect->y1, rect->x2 - rect->x1);
    LCD_DrawVertLine(rect->x1, rect->y1 + 1, rect->y2 - rect->y1 - 1);

    LCD_SetPenColor(colorPalette1[c2]);
    LCD_DrawHorLine(rect->x1 + 1, rect->y1 + 1, rect->x2 - rect->x1 - 2);
    LCD_DrawVertLine(rect->x1 + 1, rect->y1 + 2, rect->y2 - rect->y1 - 3);

    // bottom, right
    LCD_SetPenColor(colorPalette1[c3]);
    LCD_DrawHorLine(rect->x1, rect->y2, rect->x2 - rect->x1 + 1);
    LCD_DrawVertLine(rect->x2, rect->y1, rect->y2 - rect->y1);

    LCD_SetPenColor(colorPalette1[c4]);
    LCD_DrawHorLine(rect->x1 + 1, rect->y2 - 1, rect->x2 - rect->x1 - 1);
    LCD_DrawVertLine(rect->x2 - 1, rect->y1 + 1, rect->y2 - rect->y1 - 1);
}



//-------------------------------------------------------//
// Draw a panel
//
//
//-------------------------------------------------------//
void guiGraph_DrawPanel(guiPanel_t *panel)
{
    rect_t rect1;

    if (panel->redrawForced)
    {
        // Background
        LCD_SetFillColor(colorPalette1[COLOR_INDEX_WIDGET_BACKGROUND]);
        rect1.x1 = wx;
        rect1.x2 = wx + panel->width - 1;
        rect1.y1 = wy;
        rect1.y2 = wy + panel->height - 1;
        LCD_FillRect(&rect1);

        /* Frame
        rect1.x1 = wx;
        rect1.x2 = wx + panel->width - 1;
        rect1.y1 = wy;
        rect1.y2 = wy + panel->height - 1; */

        if ((panel->frame == FRAME3D_SUNKEN) || (panel->frame == FRAME3D_RAISED))
        {
            guiGraph_Draw3DFrame(&rect1, panel->frame);
        }
        else if (panel->frame == FRAME_SINGLE)
        {
            LCD_SetPenColor(colorPalette[COLOR_INDEX_3DFRAME_DARK1]);
            LCD_SetLineStyle(LINE_STYLE_SOLID);
            LCD_DrawRect(&rect1);
        }

    }

    if ((panel->redrawForced) || (panel->redrawFocus))
    {
        if (panel->showFocus)
        {
            if (panel->isFocused)
            {
                LCD_SetPenColor(colorPalette[COLOR_INDEX_FOCUS_FRAME]);
                LCD_SetLineStyle(LINE_STYLE_DOTTED);
            }
            else
            {
                LCD_SetPenColor(colorPalette[COLOR_INDEX_WIDGET_BACKGROUND]);
                LCD_SetLineStyle(LINE_STYLE_SOLID);
            }
            rect1.x1 = wx + PANEL_FOCUS_RECT_MARGIN;
            rect1.x2 = wx + panel->width - 1 - PANEL_FOCUS_RECT_MARGIN;
            rect1.y1 = wy + PANEL_FOCUS_RECT_MARGIN;
            rect1.y2 = wy + panel->height - 1 - PANEL_FOCUS_RECT_MARGIN;
            LCD_DrawRect(&rect1);
        }
    }
}




//-------------------------------------------------------//
// Draw a form
//
//
//-------------------------------------------------------//
/*
void guiGraph_DrawForm(guiForm_t *form)
{
    rect_t rect1;

    if (form->redrawFlags & FORM_REDRAW_BACKGROUND)
    {
        LCD_SetFillColor(colorPalette1[COLOR_INDEX_WIDGET_BACKGROUND]);
        rect1.x1 = wx;
        rect1.x2 = wx + form->width - 1;
        rect1.y1 = wy;
        rect1.y2 = wy + form->height - 1;
        LCD_FillRect(&rect1);
    }
}
*/

//-------------------------------------------------------//
// Draw a textLabel
//
//
//-------------------------------------------------------//
void guiGraph_DrawTextLabel(guiTextLabel_t *textLabel)
{
    rect_t rect1;

    rect1.x1 = wx;
    rect1.x2 = wx + textLabel->width - 1;
    rect1.y1 = wy;
    rect1.y2 = wy + textLabel->height - 1;

    if ( ((textLabel->redrawForced) || (textLabel->redrawFocus)) &&
         (textLabel->showFocus))
    {
        if (textLabel->isFocused)
        {
            LCD_SetLineStyle(LINE_STYLE_DOTTED);
            LCD_SetPenColor(colorPalette[COLOR_INDEX_FOCUS_FRAME]);
        }
        else
        {
            LCD_SetLineStyle(LINE_STYLE_SOLID);
            if (textLabel->hasFrame)
                 LCD_SetPenColor(CL_GREEN); // FIXME
            else
                 LCD_SetPenColor(colorPalette[COLOR_INDEX_WIDGET_BACKGROUND]);
        }
        LCD_DrawRect(&rect1);
    }

   if (textLabel->redrawForced)
   {
       // Erase rectangle
       LCD_SetFillColor(colorPalette1[COLOR_INDEX_WIDGET_BACKGROUND]);
       rect1.x1 = wx + 1;
       rect1.x2 = wx  + textLabel->width - 2;
       rect1.y1 = wy + 1;
       rect1.y2 = wy + textLabel->height - 2;
       LCD_FillRect(&rect1);

       // Draw string
       if ((textLabel->text) && (textLabel->font))
       {
           LCD_SetFont(textLabel->font);
           LCD_SetPenColor(colorPalette1[COLOR_INDEX_TEXT_ACTIVE]);
           rect1.x1 = wx + 1 + TEXT_LABEL_TEXT_MARGIN;
           rect1.y1 = wy + 1;
           rect1.x2 = wx + textLabel->width - 2 - TEXT_LABEL_TEXT_MARGIN;
           rect1.y2 = wy + textLabel->height - 2;
           LCD_PrintStringAligned(textLabel->text, &rect1, textLabel->textAlignment);
       }
   }
}


void guiGraph_DrawCheckBox(guiCheckBox_t * checkBox)
{
    int8_t y_aligned;
    rect_t rect1;
    uint8_t *img;

    y_aligned = checkBox->height - CHECKBOX_GRAPH_YSIZE;
    y_aligned /= 2;
    y_aligned = wy + y_aligned;


    rect1.x1 = wx;
    rect1.x2 = wx + checkBox->width - 1;
    rect1.y1 = wy;
    rect1.y2 = wy + checkBox->height - 1;


    if (checkBox->redrawForced)
    {
       // Erase rectangle
        LCD_SetFillColor(colorPalette1[COLOR_INDEX_WIDGET_BACKGROUND]);
        LCD_FillRect(&rect1);

       // Draw string
       if (checkBox->text)
       {
           LCD_SetPenColor(colorPalette1[COLOR_INDEX_TEXT_ACTIVE]);
           LCD_SetFont(checkBox->font);
           rect1.x1 = wx + 2 + CHECKBOX_GRAPH_XSIZE + CHECKBOX_TEXT_MARGIN;
           rect1.y1 = wy + 1;
           rect1.x2 = wx + checkBox->width - 2;
           rect1.y2 = wy + checkBox->height - 2;
           LCD_PrintStringAligned(checkBox->text, &rect1, checkBox->textAlignment);
       }

       // Check frame
       rect1.x1 = wx;
       rect1.x2 = wx + 3 + CHECKBOX_GRAPH_XSIZE;
       rect1.y1 = y_aligned - 2;
       rect1.y2 = y_aligned + 1 + CHECKBOX_GRAPH_YSIZE;
       guiGraph_Draw3DFrame(&rect1, FRAME3D_SUNKEN);

       // Draw rectangle frame
       //LCD_SetPixelOutputMode(PIXEL_MODE_REWRITE);
       //LCD_DrawRect(wx + 2,y_aligned,CHECKBOX_GRAPH_XSIZE,CHECKBOX_GRAPH_YSIZE,1);
    }


    if ((checkBox->redrawForced) || (checkBox->redrawCheckedState))
    {
        LCD_SetPenColor(CL_BLACK);
        LCD_SetAltPenColor(CL_WHITE);
        img = (checkBox->isChecked) ? CHECKBOX_IMG_CHECKED :
                                     CHECKBOX_IMG_EMPTY;
        LCD_SetImageOutput(IMAGE_PAINT_SET_PIXELS | IMAGE_PAINT_VOID_PIXELS);
        LCD_drawPackedImage(img, wx+2, y_aligned, CHECKBOX_GRAPH_XSIZE, CHECKBOX_GRAPH_YSIZE);

    }



    if ((checkBox->redrawForced) || (checkBox->redrawFocus))
    {
        rect1.x1 = wx + 3 + CHECKBOX_GRAPH_XSIZE + CHECKBOX_TEXT_MARGIN/2;
        rect1.y1 = wy + 1;
        rect1.x2 = wx + checkBox->width - 2;
        rect1.y2 = wy + checkBox->height - 2;

        if (checkBox->isFocused)
        {
          LCD_SetLineStyle(LINE_STYLE_DOTTED);
          LCD_SetPenColor(colorPalette[COLOR_INDEX_FOCUS_FRAME]);
          LCD_DrawRect(&rect1);
        }
        else
        {
          LCD_SetLineStyle(LINE_STYLE_SOLID);
          LCD_SetPenColor(colorPalette[COLOR_INDEX_WIDGET_BACKGROUND]);
        //     if (checkBox->hasFrame)
              LCD_DrawRect(&rect1);
        //     else
        //         LCD_DrawRect(wx,wy,checkBox->width,checkBox->height);
        }
    }



}





void guiGraph_DrawRadioButton(guiRadioButton_t *button)
{
    int8_t y_aligned;
    int8_t x_aligned;
    rect_t rect1;

    rect1.x1 = wx;
    rect1.x2 = wx + button->width - 1;
    rect1.y1 = wy;
    rect1.y2 = wy + button->height - 1;


    y_aligned = wy + button->height / 2;
    x_aligned = wx + RADIOBUTTON_RADIUS;


    if (button->redrawForced)
    {
        // Erase rectangle
        LCD_SetFillColor(colorPalette1[COLOR_INDEX_WIDGET_BACKGROUND]);
        //LCD_SetFillColor(CL_WHITE);
        LCD_FillRect(&rect1);

        // Draw string
        if (button->text)
        {
            LCD_SetPenColor(colorPalette1[COLOR_INDEX_TEXT_ACTIVE]);
            LCD_SetFont(button->font);
            rect1.x1 = wx + 2 + RADIOBUTTON_RADIUS*2 + RADIOBUTTON_TEXT_MARGIN;
            rect1.y1 = wy + 1;
            rect1.x2 = wx + button->width - 2;
            rect1.y2 = wy + button->height - 2;
            LCD_PrintStringAligned(button->text, &rect1, button->textAlignment);
        }
    }


    if ((button->redrawForced) || (button->redrawCheckedState))
    {
        LCD_SetFillColor(CL_WHITE);
        LCD_DrawFilledCircle(x_aligned,y_aligned,RADIOBUTTON_RADIUS);
        //LCD_SetPenColor(colorFromRgb(140,140,140));
        LCD_SetPenColor(colorPalette1[COLOR_INDEX_3DFRAME_DARK2]);
        LCD_DrawCircle(x_aligned,y_aligned,RADIOBUTTON_RADIUS);
        //LCD_SetPenColor(colorFromRgb(70,70,70));
        LCD_SetPenColor(colorPalette1[COLOR_INDEX_3DFRAME_DARK1]);
        LCD_DrawCircle(x_aligned,y_aligned,RADIOBUTTON_RADIUS-1);
        //LCD_SetPenColor(colorPalette1[COLOR_INDEX_3DFRAME_DARK1]);
        //LCD_DrawCircle(x_aligned,y_aligned,RADIOBUTTON_RADIUS-1);

        if (button->isChecked)
        {
            LCD_SetFillColor(CL_BLACK);
            LCD_DrawFilledCircle(x_aligned,y_aligned,RADIOBUTTON_CHECK_RADIUS);
        }
    }



    if ((button->redrawForced) || (button->redrawFocus))
    {
        rect1.x1 = wx + 3 + RADIOBUTTON_RADIUS*2 + RADIOBUTTON_TEXT_MARGIN/2;
        rect1.y1 = wy + 1;
        rect1.x2 = wx + button->width - 2;
        rect1.y2 = wy + button->height - 2;

        if (button->isFocused)
        {
          LCD_SetLineStyle(LINE_STYLE_DOTTED);
          LCD_SetPenColor(colorPalette[COLOR_INDEX_FOCUS_FRAME]);
          LCD_DrawRect(&rect1);
        }
        else
        {
          LCD_SetLineStyle(LINE_STYLE_SOLID);
          LCD_SetPenColor(colorPalette[COLOR_INDEX_WIDGET_BACKGROUND]);
          LCD_DrawRect(&rect1);
        }
    }

}






//-------------------------------------------------------//
// Draw a button
//
//
//-------------------------------------------------------//
void guiGraph_DrawButton(guiButton_t *button)
{
    rect_t rect1;
    rect1.x1 = wx + 2;
    rect1.x2 = wx + button->width - 3;
    rect1.y1 = wy + 2;
    rect1.y2 = wy + button->height - 3;


    if (button->redrawForced)
    {
        LCD_SetFillColor(colorPalette1[COLOR_INDEX_BUTTON_BACKGROUND]);
        LCD_FillRect(&rect1);
        LCD_SetFont(button->font);
        LCD_SetPenColor(colorPalette1[COLOR_INDEX_TEXT_ACTIVE]);
        LCD_PrintStringAligned(button->text, &rect1, button->textAlignment);
    }

    if ((button->redrawForced) || (button->redrawFocus))
    {
        if (button->isFocused)
        {
            LCD_SetPenColor(colorPalette[COLOR_INDEX_FOCUS_FRAME]);
            LCD_SetLineStyle(LINE_STYLE_DOTTED);
        }
        else
        {
            LCD_SetPenColor(colorPalette[COLOR_INDEX_BUTTON_BACKGROUND]);
            LCD_SetLineStyle(LINE_STYLE_SOLID);
        }

        rect1.x1 = wx + BUTTON_FOCUS_RECT_MARGIN;
        rect1.x2 = wx + button->width - 1 - BUTTON_FOCUS_RECT_MARGIN;
        rect1.y1 = wy + BUTTON_FOCUS_RECT_MARGIN;
        rect1.y2 = wy + button->height - 1 - BUTTON_FOCUS_RECT_MARGIN;
        LCD_DrawRect(&rect1);
    }

    if ((button->redrawForced) || (button->redrawPressedState))
    {
        rect1.x1 = wx;
        rect1.x2 = wx + button->width - 1;
        rect1.y1 = wy;
        rect1.y2 = wy + button->height - 1;
        if (button->isPressed)
            guiGraph_Draw3DFrame(&rect1, FRAME3D_SUNKEN);
        else
            guiGraph_Draw3DFrame(&rect1, FRAME3D_RAISED);
    }

}

