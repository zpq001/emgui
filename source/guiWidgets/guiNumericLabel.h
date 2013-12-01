
#include <stdint.h>
#include "guiFonts.h"


typedef struct {
	uint8_t x_pos;
	uint8_t y_pos;
	uint32_t value;
	uint8_t flags;
	guiFont_t *pfont;
} guiNumericLabel_t;


void guiNumericLabel_Draw(guiNumericLabel_t* pNumericLabel);
void guiNumericalLabel_SetValue(guiNumericLabel_t* pNumericLabel, uint32_t value);





