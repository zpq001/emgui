#include <stdio.h>

#include "guiWidgetFlags.h"
#include "guiNumericLabel.h"

#include "guiFonts.h"
#include "guiFontUtils.h"


void guiNumericLabel_Draw(guiNumericLabel_t* pNumericLabel)
{
	char temp_str[20];
	sprintf(temp_str,"%d",pNumericLabel->value);
    guiFont_PrintString(pNumericLabel->x_pos, pNumericLabel->y_pos, temp_str, pNumericLabel->pfont);
}

void guiNumericalLabel_SetValue(guiNumericLabel_t* pNumericLabel, uint32_t value)
{
	pNumericLabel->value = value;
}




