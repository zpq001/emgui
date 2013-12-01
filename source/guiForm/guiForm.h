#ifndef __GUI_FORM_H_
#define __GUI_FORM_H_

#include <stdint.h>
#include "guiEvents.h"
#include "guiWidgetCommon.h"


#define GFM_DRAW        1
#define GFM_SELECT        1

// Form flags - are set during event processing
#define GUI_FORM_FLAG_REDRAW_ALL         (1<<0)

/*
typedef struct guiForm_t {
    void (*processEvent)(guiEvent_t event);
    void (*drawStaticFunction)(void);
    uint8_t flags;
    guiGenericWidget_t *pSelectedWidget;
    uint8_t guiElementsCount;
    guiGenericWidget_t *guiElements[];
} guiForm_t;      // Any form
*/

void guiForm_Initialize(guiForm_t *pForm);
void guiForm_SelectWidget(guiForm_t *pForm, guiGenericWidget_t *pWidgetToSelect);
void guiForm_SelectNextWidget(guiForm_t *pForm, int8_t tabDir);
void guiForm_Draw(guiForm_t *pForm);


#endif
