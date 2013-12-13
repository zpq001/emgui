#ifndef __GUI_PANEL_H_
#define __GUI_PANEL_H_

#include <stdint.h>
#include "guiWidgets.h"


// Redraw flags:
#define PANEL_REDRAW_FOCUS       (1<<0)
#define PANEL_REDRAW_BACKGROUND  (1<<1)



void guiPanel_Initialize(guiPanel_t *panel);





#endif
