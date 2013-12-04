#ifndef __GUI_GRAPH_PRIMITIVES_H_
#define __GUI_GRAPH_PRIMITIVES_H_

#include <stdint.h>
#include "guiGraphHAL.h"
#include "guiFonts.h"



extern const tFont* LCD_currentFont;


void LCD_DrawRect(uint8_t x_pos, uint8_t y_pos, uint8_t width, uint8_t height, uint8_t pixelValue);
void LCD_PrintString(char *str, uint8_t x, uint8_t y, uint8_t mode);

#endif
