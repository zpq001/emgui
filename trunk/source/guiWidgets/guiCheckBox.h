#ifndef __GUI_CHECK_BOX_H_
#define __GUI_CHECK_BOX_H_

#include <stdint.h>
#include "guiWidgets.h"

// Appearance
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
#define CHECKBOX_KEY_SELECT     0x01

// Widget-specific state checks
#define CHECKBOX_ACCEPTS_FOCUS_EVENT(checkBox)  ( (checkBox->isVisible) && (1) )    // TODO - add isEnabled
#define CHECKBOX_ACCEPTS_KEY_EVENT(checkBox)    ( (checkBox->isFocused) && \
                                                  (checkBox->isVisible) )           // TODO - add isEnabled
#define CHECKBOX_ACCEPTS_TOUCH_EVENT(checkBox)  ( (checkBox->isVisible) )           // TODO - add isEnabled



void guiCheckBox_Initialize(guiCheckBox_t *checkBox, guiGenericWidget_t *parent);
uint8_t guiCheckbox_SetChecked(guiCheckBox_t *checkBox, uint8_t newCheckedState);
uint8_t guiCheckbox_ProcessKey(guiCheckBox_t *checkBox, uint8_t key);
uint8_t guiCheckBox_ProcessEvent(guiGenericWidget_t *widget, guiEvent_t event);



#endif
