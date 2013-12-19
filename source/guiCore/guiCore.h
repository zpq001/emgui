#ifndef __GUI_CORE_H_
#define __GUI_CORE_H_

#include <stdint.h>
#include "guiForm.h"
#include "guiEvents.h"
#include "guiWidgets.h"


#define GUI_CORE_QUEUE_SIZE 20

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


typedef struct {
    int16_t x1;
    int16_t y1;
    int16_t x2;
    int16_t y2;
} rect16_t;


// Event process function result
#define GUI_EVENT_DECLINE       0x00
#define GUI_EVENT_ACCEPTED      0x01

// Set visible by tag mode
#define ITEMS_IN_RANGE_ARE_VISIBLE          0x01
#define ITEMS_IN_RANGE_ARE_INVISIBLE        0x02
#define ITEMS_OUT_OF_RANGE_ARE_VISIBLE      0x04
#define ITEMS_OUT_OF_RANGE_ARE_INVISIBLE    0x08

// Check tabIndex result
#define TABINDEX_IS_MAX     2
#define TABINDEX_IS_MIN     1
#define TABINDEX_IS_NORM    0



//-----------------------------------//
// Keyboard support

// Keyboard codes are design-specific and should be defined in
// one of top-level modules

// Key event specifications
#define DEFAULT_KEY_EVENT_DOWN   0x01        // A key has been pressed
#define DEFAULT_KEY_EVENT_UP     0x02        // A key has been released

// Button codes
#define DEFAULT_KEY_ESC     (1<<0)
#define DEFAULT_KEY_LEFT    (1<<1)
#define DEFAULT_KEY_RIGHT   (1<<2)
#define DEFAULT_KEY_OK      (1<<3)


//-----------------------------------//
// Touch support

// Touch states
#define TOUCH_PRESS     (1<<0)
#define TOUCH_RELEASE   (1<<1)
#define TOUCH_MOVE      (1<<2)

// Decoded touch arguments for a widget
typedef struct {
    int16_t x;                  // X - coordinate, relative to widget
    int16_t y;                  // Y - coordinate, relative to widget
    uint8_t state;              // Touch state
    uint8_t isInsideWidget;     // Set if touch point lies inside widget
} widgetTouchState_t;

// Decoded touch arguments for a container
typedef struct {
    int16_t x;                          // X - coordinate, relative to widget
    int16_t y;                          // Y - coordinate, relative to widget
    uint8_t state;                      // Touch state
    guiGenericWidget_t *widgetAtXY;     // Widget under touch point
} containerTouchState_t;








void guiCore_SetVisibleByTag(guiWidgetCollection_t *collection, uint8_t minTag, uint8_t maxTag, uint8_t mode);

uint8_t guiCore_SetVisible(guiGenericWidget_t *widget, uint8_t newVisibleState);
uint8_t guiCore_SetFocused(guiGenericWidget_t *widget, uint8_t newFocusedState);

//extern guiForm_t *currentForm;
//extern uint8_t globalRedrawFlags;

//extern SoftTimer8b_t blinkTimer;

uint8_t guiCore_AddMessageToQueue(const guiGenericWidget_t *target, const guiEvent_t *event);
uint8_t guiCore_GetMessageFromQueue(guiGenericWidget_t **target, guiEvent_t *event);

void guiCore_Init(guiGenericWidget_t *initialForm);
void guiCore_RedrawAll(void);
uint8_t guiCore_CheckWidgetOvelap(guiGenericWidget_t *widget, rect16_t *rect);
void guiCore_InvalidateRect(guiGenericWidget_t *widget, int16_t x1, int16_t y1, uint16_t x2, uint16_t y2);

void guiCore_ProcessTouchEvent(int16_t x, int16_t y, uint8_t touchState);
void guiCore_ProcessButtonEvent(uint16_t code, uint8_t spec);
void guiCore_ProcessEncoderEvent(int16_t increment);

void guiCore_PostEventToFocused(guiEvent_t event);
void guiCore_ProcessMessageQueue(void);

void guiCore_RequestFocusChange(guiGenericWidget_t *newFocusedWidget);
void guiCore_AcceptFocus(guiGenericWidget_t *widget);

uint8_t guiCore_GetWidgetIndex(guiGenericWidget_t *widget);
uint8_t guiCore_CheckWidgetTabIndex(guiGenericWidget_t *widget);

void guiCore_RequestFocusNextWidget(guiGenericContainer_t *container, int8_t tabDir);
//guiGenericWidget_t *guiCore_GetNextFocusWidget(guiGenericContainer_t *container, int8_t tabDir);

uint8_t guiCore_CallEventHandler(guiGenericWidget_t *widget, guiEvent_t *event);

void guiCore_ConvertToAbsoluteXY(guiGenericWidget_t *widget, int16_t *x, int16_t *y);
void guiCore_ConvertToRelativeXY(guiGenericWidget_t *widget, int16_t *x, int16_t *y);
uint8_t guiCore_CheckWidgetXY(guiGenericWidget_t *widget, int16_t x, int16_t y);
guiGenericWidget_t *guiCore_GetWidgetAtXY(guiGenericWidget_t *container, int16_t x, int16_t y);

void guiCore_DecodeWidgetTouchEvent(guiGenericWidget_t *widget, guiEvent_t *touchEvent, widgetTouchState_t *decodedTouchState);
void guiCore_DecodeContainerTouchEvent(guiGenericWidget_t *widget, guiEvent_t *touchEvent, containerTouchState_t *decodedTouchState);

#endif
