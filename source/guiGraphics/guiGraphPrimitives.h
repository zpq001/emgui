#ifndef __GUI_GRAPH_PRIMITIVES_H_
#define __GUI_GRAPH_PRIMITIVES_H_

#include <stdint.h>
#include "guiGraphHAL.h"
#include "guiFonts.h"

typedef struct {
    int16_t x1;
    int16_t y1;
    int16_t x2;
    int16_t y2;
} rect_t;

typedef struct {
    int16_t x;
    int16_t y;
} point_t;


#define IMAGE_PAINT_SET_PIXELS    0x1
#define IMAGE_PAINT_VOID_PIXELS   0x2

// Align modes - required alignment mode is selected by
// combining these flags
#define ALIGN_CENTER    0x00
#define ALIGN_LEFT      0x01
#define ALIGN_RIGHT     0x02
#define ALIGN_TOP       0x04
#define ALIGN_BOTTOM    0x08
// Aliases
#define ALIGN_TOP_LEFT      (ALIGN_TOP | ALIGN_LEFT)
#define ALIGN_BOTTOM_LEFT   (ALIGN_BOTTOM | ALIGN_LEFT)
#define ALIGN_TOP_RIGHT     (ALIGN_TOP | ALIGN_RIGHT)
#define ALIGN_BOTTOM_RIGHT   (ALIGN_BOTTOM | ALIGN_RIGHT)


// Dashed and dotted line style settings
// Counter increments from 0 to LCD_xxx_PERIOD-1
// if counter < LCD_xxx_COMPARE, pixel is put unchaged
// if counter >= LCD_xxx_COMPARE, pixel is put inversed
#define LCD_DOT_PERIOD      4
#define LCD_DOT_COMPARE     2
#define LCD_DASH_PERIOD     7
#define LCD_DASH_COMPARE    5


// Line drawing mode (not for all functions)
#define LINE_STYLE_SOLID      0x10
#define LINE_STYLE_DASHED     0x20
#define LINE_STYLE_DOTTED     0x30

//color_t penColor;             // Pen is used for drawing lines, frames, circles, etc
//color_t fillColor;            // Used for filling objects
//const tFont* currentFont;     // Font that currently used
//color_t fontForeColor;        // Used when printing text
//color_t fontBackColor;        //
//uint8_t fontOutputMode;       // Specifies text background - FONT_OUTPUT_TRANSPARENT or FONT_OUTPUT_SOLID


void LCD_SetFont(const tFont *newFont);
void LCD_SetPenColor(const color_t newColor);
void LCD_SetAltPenColor(const color_t newColor);
void LCD_SetFillColor(const color_t newColor);
void LCD_SetImageOutput(uint8_t newMode);
void LCD_SetLineStyle(uint8_t newStyle);

void LCD_FillRect(rect_t* rect);
void LCD_DrawHorLine(uint16_t x, uint16_t y, uint16_t length);
void LCD_DrawVertLine(uint16_t x, uint16_t y, uint16_t length);
void LCD_DrawRect(rect_t *rect);
void LCD_drawPackedImage(const uint8_t *img, uint16_t x_pos, uint16_t y_pos, uint16_t img_width, uint16_t img_height);

void LCD_PrintString(char *str, uint8_t x, uint8_t y);
void LCD_PrintStringAligned(char *str, rect_t *rect, uint8_t alignment);

void LCD_DrawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
//void LCD_DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t radius);
void LCD_DrawCircle(int16_t x0, int16_t y0, int16_t radius);
void LCD_DrawFilledCircle(int16_t x0, int16_t y0, int16_t radius);


#endif
