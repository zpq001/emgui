#ifndef __GUI_FORM_H_
#define __GUI_FORM_H_

#include <stdint.h>
#include "guiWidgets.h"


// Redraw flags:
#define FORM_REDRAW_FOCUS       (1<<0)
#define FORM_REDRAW_BACKGROUND  (1<<1)



void guiForm_Initialize(guiForm_t *form);





#endif
