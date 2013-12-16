#ifndef __GUI_PANEL_H_
#define __GUI_PANEL_H_

#include <stdint.h>
#include "guiWidgets.h"


// Redraw flags:
#define PANEL_REDRAW_FOCUS       (1<<0)
#define PANEL_REDRAW_BACKGROUND  (1<<1)

#define PANEL_FOCUS_RECT_MARGIN    2

void guiPanel_Initialize(guiPanel_t *panel, guiGenericWidget_t *parent);
void guiPanel_SetFocused(guiPanel_t *panel, uint8_t newFocusedState);
uint8_t guiPanel_ProcessEvent(guiGenericWidget_t *widget, guiEvent_t event);




#endif
