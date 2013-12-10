#ifndef __GUI_CHECK_BOX_H_
#define __GUI_CHECK_BOX_H_

#include <stdint.h>
#include "guiWidgets.h"


// Redraw flags:
#define CHECKBOX_REDRAW_FOCUS     (1<<0)
#define CHECKBOX_REDRAW_STATE     (1<<1)
#define CHECKBOX_REDRAW_BACKGROUND	  (1<<2)


// Size
#define CHECKBOX_GRAPH_XSIZE  10
#define CHECKBOX_GRAPH_YSIZE  10
#define CHECKBOX_TEXT_MARGIN  4

#define CHECKBOX_IMG_CHECKED  checkbox_10x10_checked
#define CHECKBOX_IMG_EMPTY  checkbox_10x10_empty

// Widget-specific events
#define CHECKBOX_CHECKED_CHANGED    (0xC0 + 0x00)


void guiCheckBox_Initialize(guiCheckBox_t *checkBox, guiGenericWidget_t *parent);
void guiCheckBox_SetRedrawFlags(guiCheckBox_t *checkBox, uint8_t flags);




#endif
