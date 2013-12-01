
#ifndef __font_defs_h
#define __font_defs_h

#include <stdint.h>

//----- Regular fonts typedefs -----//

typedef struct 
{
	uint8_t width;
	uint8_t height;
	uint8_t count;
	uint8_t bytesPerChar;
	const uint8_t *data;
} guiFont_t;


//----------------------------------//




#endif
