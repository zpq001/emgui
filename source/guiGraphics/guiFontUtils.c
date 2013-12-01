
#include "guiFonts.h"
#include "guiGraphCommon.h"
#include "guiConfig.h"
#include "guiGraphUtils.h"




void guiFont_PrintChar(uint8_t x_pos, uint8_t y_pos, char c, guiFont_t *myFont, uint8_t mode)
{
    uint16_t charPointer = ((uint8_t)c) * myFont->bytesPerChar;
    guiGraph_DrawImage((uint8_t*)&myFont->data[charPointer],x_pos,y_pos,myFont->width,myFont->height,mode);
}


void guiFont_PrintString(uint8_t x_pos, uint8_t y_pos, char *str, guiFont_t *myFont, uint8_t mode)
{
	uint16_t i = 0;
	uint16_t charPointer;
	
	while(str[i] != '\0')
	{
        charPointer = ((uint8_t)str[i++]) * myFont->bytesPerChar;
        guiGraph_DrawImage((uint8_t*)&myFont->data[charPointer],x_pos,y_pos,myFont->width,myFont->height,mode);
		x_pos += myFont->width;
	}
}

