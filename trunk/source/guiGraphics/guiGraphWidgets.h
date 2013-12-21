#ifndef __GUI_GRAPH_WIDGETS_
#define __GUI_GRAPH_WIDGETS_

#include <stdint.h>
#include "guiGraphPrimitives.h"
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


// Widget Appearance


//---------------------------------------------//
// Button
#define BUTTON_FOCUS_RECT_MARGIN    2


//---------------------------------------------//
// Checkbox
/*
#define CHECKBOX_GRAPH_XSIZE  10
#define CHECKBOX_GRAPH_YSIZE  10
#define CHECKBOX_TEXT_MARGIN  6
#define CHECKBOX_IMG_CHECKED  checkbox_10x10_checked_no_frame
#define CHECKBOX_IMG_EMPTY  checkbox_10x10_empty_no_frame
*/ /*
#define CHECKBOX_GRAPH_XSIZE  8
#define CHECKBOX_GRAPH_YSIZE  8
#define CHECKBOX_TEXT_MARGIN  4
#define CHECKBOX_IMG_CHECKED  checkbox_8x8_checked_no_frame
#define CHECKBOX_IMG_EMPTY  checkbox_8x8_empty_no_frame
*/
#define CHECKBOX_GRAPH_XSIZE  9
#define CHECKBOX_GRAPH_YSIZE  9
#define CHECKBOX_TEXT_MARGIN  5
#define CHECKBOX_IMG_CHECKED  checkbox_9x9_checked_no_frame
#define CHECKBOX_IMG_EMPTY  checkbox_9x9_empty_no_frame

//---------------------------------------------//
// Panel
#define PANEL_FOCUS_RECT_MARGIN    2


//---------------------------------------------//
// Radiobutton
#define RADIOBUTTON_RADIUS  6
#define RADIOBUTTON_CHECK_RADIUS  2
#define RADIOBUTTON_TEXT_MARGIN  5

//---------------------------------------------//
// Textlabel
#define TEXT_LABEL_TEXT_MARGIN  2



extern const color_t colorPalette1[];
color_t *colorPalette;


extern int16_t wx;
extern int16_t wy;

void guiGraph_SetBaseXY(int16_t x, int16_t y);
void guiGraph_OffsetBaseXY(int16_t dx, int16_t dy);

void guiGraph_DrawPanel(guiPanel_t *panel);
void guiGraph_DrawTextLabel(guiTextLabel_t *textLabel);
void guiGraph_DrawCheckBox(guiCheckBox_t * checkBox);
void guiGraph_DrawRadioButton(guiRadioButton_t *button);


void guiGraph_DrawButton(guiButton_t *button);



#endif
