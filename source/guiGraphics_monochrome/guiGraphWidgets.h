#ifndef __GUI_GRAPH_WIDGETS_
#define __GUI_GRAPH_WIDGETS_

#include <stdint.h>
#include "guiWidgets.h"


extern int16_t wx;
extern int16_t wy;

void guiGraph_SetBaseXY(int16_t x, int16_t y);
void guiGraph_OffsetBaseXY(int16_t dx, int16_t dy);


void guiGraph_DrawForm(guiForm_t *form);
void guiGraph_DrawTextLabel(guiTextLabel_t *textLabel);
void guiGraph_DrawCheckBox(guiCheckBox_t * checkBox);



#endif
