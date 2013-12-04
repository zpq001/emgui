#ifndef __GUI_FONTS_H_
#define __GUI_FONTS_H_

#include <stdint.h>


//---------------------------------------------//
// Variable-width fonts typedefs
typedef struct 
{
	uint8_t code;
	uint8_t width;
	const uint8_t *data;
} tFontItem;


typedef struct 
{
	uint8_t height;
    uint8_t charCount;
    uint8_t spacing;
    const tFontItem *chars;
} tFont;


extern const tFont font_h12;



#endif
