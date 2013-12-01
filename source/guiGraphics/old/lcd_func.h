

#include "font_defs.h"

// Size definitions in points
#define LCD_XSIZE 96
#define LCD_YSIZE 68

// Size definitions in bytes
#define LCD_BUFFER_SIZE 864 //96*9





#define PIXEL_OFF 0
#define PIXEL_ON 1
#define PIXEL_XOR 2

// Char width for Font_6x8.h
#define NativeFontWidth 6


// Lcd buffers
extern uint16_t lcd0_buffer[];
extern uint16_t lcd1_buffer[];

void LcdPutPixel (uint8_t x_pos, uint8_t y_pos, uint8_t mode, uint16_t *lcd_buffer);
void LcdPutHorLine(uint8_t x_pos, uint8_t y_pos, uint8_t length, uint8_t mode, uint16_t *lcd_buffer);
void LcdPutVertLine(uint8_t x_pos, uint8_t y_pos, uint8_t length, uint8_t mode, uint16_t *lcd_buffer);

// Fills LCD buffer with specified value
void LcdFillBuffer(uint16_t* lcd_buffer, uint8_t value);


void LcdPutCharNative(uint8_t x, uint8_t y, uint8_t ch, uint8_t inversion, uint16_t* lcd_buffer);
void LcdPutStrNative(uint8_t x, uint8_t row, uint8_t *dataPtr, uint8_t inversion, uint16_t* lcd_buffer );

void LcdPutImage(uint8_t* img, uint8_t x_pos, uint8_t y_pos, uint8_t width, uint8_t height, uint16_t* lcd_buffer);


void LcdPutSpecialStr(uint8_t x_pos, uint8_t y_pos, uint8_t* str, tSpecialFont* myFont, uint16_t* lcd_buffer);
void LcdPutNormalStr(uint8_t x_pos, uint8_t y_pos, uint8_t* str, tNormalFont* myFont, uint16_t* lcd_buffer);


