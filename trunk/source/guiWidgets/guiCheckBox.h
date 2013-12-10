#ifndef __GUI_CHECK_BOX_H_
#define __GUI_CHECK_BOX_H_

#include <stdint.h>
#include "guiWidgets.h"


// Redraw flags:
#define CHECKBOX_REDRAW_FOCUS     (1<<0)
#define CHECKBOX_REDRAW_STATE     (1<<1)
#define CHECKBOX_REDRAW_BACKGROUND	  (1<<2)





void guiCheckBox_Initialize(guiCheckBox_t *checkBox, guiGenericWidget_t *parent);
void guiCheckBox_SetRedrawFlags(guiCheckBox_t *checkBox, uint8_t flags);




#endif
