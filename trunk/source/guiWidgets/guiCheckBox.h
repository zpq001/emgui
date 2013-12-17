#ifndef __GUI_CHECK_BOX_H_
#define __GUI_CHECK_BOX_H_

#include <stdint.h>
#include "guiWidgets.h"


// Redraw flags:
#define CHECKBOX_REDRAW_FOCUS     (1<<0)
#define CHECKBOX_REDRAW_STATE     (1<<1)
#define CHECKBOX_REDRAW_BACKGROUND	  (1<<2)


// Size
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

// Widget-specific events
#define CHECKBOX_CHECKED_CHANGED    (0xC0 + 0x00)


// Widget-specific keys
#define CHECKBOX_KEY_OK     0x01

//typedef struct {
//    uint8_t key_ok : 1;
//} checkboxKeyState_t;



void guiCheckBox_Initialize(guiCheckBox_t *checkBox, guiGenericWidget_t *parent);
void guiCheckbox_SetFocused(guiCheckBox_t *checkbox, uint8_t newFocusedState);
void guiCheckbox_SetChecked(guiCheckBox_t *checkBox, uint8_t newCheckedState);
void guiCheckbox_SetVisible(guiCheckBox_t *checkBox, uint8_t newVisibleState);
uint8_t guiCheckbox_DefaultKeyConverter(guiEvent_t *keyEvent);
uint8_t guiCheckBox_ProcessEvent(guiGenericWidget_t *widget, guiEvent_t event);



#endif
