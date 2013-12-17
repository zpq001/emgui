#ifndef __GUI_GRAPH_WIDGETS_
#define __GUI_GRAPH_WIDGETS_

#include <stdint.h>
#include "guiWidgets.h"

// System color palette size
#define COLOR_PALETTE_SIZE  8
// System palette indexes
#define COLOR_INDEX_WIDGET_BACKGROUND     0
#define COLOR_INDEX_BUTTON_BACKGROUND   1
#define COLOR_INDEX_3DFRAME_LIGHT1      2
#define COLOR_INDEX_3DFRAME_LIGHT2      3
#define COLOR_INDEX_3DFRAME_DARK1       4
#define COLOR_INDEX_3DFRAME_DARK2       5
#define COLOR_INDEX_FOCUS_FRAME         6
#define COLOR_INDEX_TEXT_ACTIVE         7


#define FRAME_NONE                      0x00
#define FRAME3D_RAISED                  0x01
#define FRAME3D_SUNKEN                  0x02
#define FRAME_SINGLE                    0x03




extern const color_t colorPalette1[];
color_t *colorPalette;


extern int16_t wx;
extern int16_t wy;

void guiGraph_SetBaseXY(int16_t x, int16_t y);
void guiGraph_OffsetBaseXY(int16_t dx, int16_t dy);

void guiGraph_DrawPanel(guiPanel_t *panel);
//void guiGraph_DrawForm(guiForm_t *form);
void guiGraph_DrawTextLabel(guiTextLabel_t *textLabel);
void guiGraph_DrawCheckBox(guiCheckBox_t * checkBox);



void guiGraph_DrawButton(guiButton_t *button);



#endif
