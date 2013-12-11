#ifndef __GUI_BUTTON_H_
#define __GUI_BUTTON_H_

#include <stdint.h>
#include "guiWidgets.h"


// Redraw flags:
#define BUTTON_REDRAW_FOCUS     (1<<0)
#define BUTTON_REDRAW_STATE     (1<<1)
#define BUTTON_REDRAW_BACKGROUND     (1<<2)



// Widget-specific events
#define BUTTON_PRESSED_CHANGED    (0xC0 + 0x00)


#define BUTTON_FOCUS_RECT_MARGIN    2


void guiButton_Initialize(guiButton_t *button, guiGenericWidget_t *parent);

//void guiButton_SetRedrawFlags(guiButton_t *button, uint8_t flags);




#endif
