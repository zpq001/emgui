#ifndef __GUI_CORE_H_
#define __GUI_CORE_H_

#include <stdint.h>
#include "guiForm.h"
#include "guiEvents.h"



/*
#define ITEMS_IN_RANGE_ARE_VISIBLE          0x01
#define ITEMS_IN_RANGE_ARE_INVISIBLE        0x02
#define ITEMS_OUT_OF_RANGE_ARE_VISIBLE      0x04
#define ITEMS_OUT_OF_RANGE_ARE_INVISIBLE    0x08

void guiCore_SetVisibleByTag(guiWidgetCollection_t *pCollection, uint8_t minTag, uint8_t maxTag, uint8_t mode);
*/


//extern guiForm_t *currentForm;
//extern uint8_t globalRedrawFlags;

//extern SoftTimer8b_t blinkTimer;

void guiCore_Init(guiForm_t *initialForm);
void guiCore_RedrawAll(void);

/*
void guiCore_ProcessEvent(guiEvent_t event);
void guiCore_RequestSwitchForm(guiForm_t* pFormToSwitch);
void guiCore_RequestFullRedraw(void);

void guiCore_SelectWidget(guiWidgetCollection_t *pCollection, guiGenericWidget_t *pWidgetToSelect);
void guiCore_SelectNextWidget(guiWidgetCollection_t *pCollection, int8_t tabDir);

uint8_t guiCore_CallEventHandler(guiGenericWidget_t *pWidget, uint8_t eventType);
*/
#endif
