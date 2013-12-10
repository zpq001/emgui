#ifndef __GUI_TEXT_LABEL_H_
#define __GUI_TEXT_LABEL_H_

#include <stdint.h>
#include "guiWidgets.h"


// Redraw flags:
#define TEXT_LABEL_REDRAW_FOCUS     (1<<0)
#define TEXT_LABEL_REDRAW_TEXT      (1<<1)
#define TEXT_LABEL_TEXT_MARGIN  2




void guiTextLabel_Initialize(guiTextLabel_t *textLabel, guiGenericWidget_t *parent);
void guiTextLabel_SetRedrawFlags(guiTextLabel_t *textLabel, uint8_t flags);




#endif
