#ifndef __GUI_GRAPH_PRIMITIVES_H_
#define __GUI_GRAPH_PRIMITIVES_H_

#include <stdint.h>
#include "guiGraphHAL.h"
#include "guiFonts.h"

typedef struct {
	uint16_t x1;
	uint16_t y1;
	uint16_t x2;
	uint16_t y2;
} rect_t;

typedef struct {
    uint16_t x;
    uint16_t y;
} point_t;


#define FONT_OUTPUT_TRANSPARENT     0
#define FONT_OUTPUT_SOLID           1


color_t penColor;             // Pen is used for drawing lines, frames, circles, etc
color_t fillColor;            // Used for filling objects
const tFont* currentFont;     // Font that currently used
color_t fontForeColor;        // Used when printing text
color_t fontBackColor;        //
uint8_t fontOutputMode;       // Specifies text background - OUTPUT_MODE_TRANSPARENT or OUTPUT_MODE_SOLID



void guiGraph_fillRect(rect_t* rect);
void guiGraph_drawHorLine(uint16_t x, uint16_t y, uint16_t length);
void guiGraph_drawVertLine(uint16_t x, uint16_t y, uint16_t length);
void guiGraph_drawRect(rect_t *rect);


void guiGraph_printTextXY(uint16_t x, uint16_t y, char *string);

#endif
