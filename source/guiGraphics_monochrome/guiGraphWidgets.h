#ifndef __GUI_GRAPH_WIDGETS_
#define __GUI_GRAPH_WIDGETS_

#include <stdint.h>
#include "guiGraphPrimitives.h"
#include "guiWidgets.h"



#define FRAME_NONE                      0x00
#define FRAME3D_RAISED                  0x01
#define FRAME3D_SUNKEN                  0x02
#define FRAME_SINGLE                    0x03


// Widget Appearance

//---------------------------------------------//
// Checkbox
#define CHECKBOX_GRAPH_XSIZE  10
#define CHECKBOX_GRAPH_YSIZE  10
#define CHECKBOX_TEXT_MARGIN  6
#define CHECKBOX_IMG_CHECKED  checkbox_10x10_checked
#define CHECKBOX_IMG_EMPTY  checkbox_10x10_empty


//---------------------------------------------//
// Textlabel
#define TEXT_LABEL_TEXT_MARGIN  0


//---------------------------------------------//
// SpinBox
#define SPINBOX_ACTIVE_UNDERLINE_MARGIN 1
#define SPINBOX_ACTIVE_UNDERLINE_WIDTH 2

//---------------------------------------------//
// StringList
#define STRINGLIST_INTERVAL 2


extern int16_t wx;
extern int16_t wy;

void guiGraph_SetBaseXY(int16_t x, int16_t y);
void guiGraph_OffsetBaseXY(int16_t dx, int16_t dy);


void guiGraph_DrawPanel(guiPanel_t *panel);
void guiGraph_DrawTextLabel(guiTextLabel_t *textLabel);
void guiGraph_DrawCheckBox(guiCheckBox_t * checkBox);
void guiGraph_DrawSpinBox(guiSpinBox_t * spinBox);
void guiGraph_DrawStringList(guiStringList_t * list);


#endif
