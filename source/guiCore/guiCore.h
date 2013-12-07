#ifndef __GUI_CORE_H_
#define __GUI_CORE_H_

#include <stdint.h>
#include "guiForm.h"
#include "guiEvents.h"
#include "guiWidgets.h"


#define GUI_CORE_QUEUE_SIZE 10

typedef struct {
    guiGenericWidget_t *target;
    guiEvent_t event;
} guiMsg_t;

typedef struct {
    uint8_t head;
    uint8_t tail;
    uint8_t count;
    guiMsg_t queue[GUI_CORE_QUEUE_SIZE];
} guiMsgQueue_t;


#define GUI_EVENT_PASS_TO_PARENT    0x00
#define GUI_EVENT_ACCEPTED          0x01

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

uint8_t guiCore_AddMessageToQueue(guiGenericWidget_t *target, guiEvent_t event);
uint8_t guiCore_GetMessageFromQueue(guiGenericWidget_t **target, guiEvent_t *event);

void guiCore_Init(guiGenericWidget_t *initialForm);
void guiCore_RedrawAll(void);
void guiCore_InvalidateRect(guiGenericWidget_t *widget, int16_t x1, int16_t y1, uint16_t x2, uint16_t y2);


void guiCore_ProcessEvent(guiEvent_t event);
/*
void guiCore_RequestSwitchForm(guiForm_t* pFormToSwitch);
void guiCore_RequestFullRedraw(void);

void guiCore_SelectWidget(guiWidgetCollection_t *pCollection, guiGenericWidget_t *pWidgetToSelect);
void guiCore_SelectNextWidget(guiWidgetCollection_t *pCollection, int8_t tabDir);

uint8_t guiCore_CallEventHandler(guiGenericWidget_t *pWidget, uint8_t eventType);
*/
#endif
