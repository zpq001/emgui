#ifndef __GUI_CORE_H_
#define __GUI_CORE_H_

#include <stdint.h>
#include "guiConfig.h"
#include "guiEvents.h"
#include "guiWidgets.h"


typedef struct {
    guiGenericWidget_t *target;
    guiEvent_t event;
} guiMsg_t;

typedef struct {
    uint8_t head;
    uint8_t tail;
    uint8_t count;
    guiMsg_t queue[emGUI_CORE_QUEUE_SIZE];
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

// Invocation types
enum guiInvokeTypes {INVOKE_DIRECT, INVOKE_QUEUED};

// States
enum guiFocusStates {WIDGET_UNFOCUSED = 0, WIDGET_FOCUSED = 1};
enum guiVisibleStates {WIDGET_INVISIBLE = 0, WIDGET_VISIBLE = 1};

// Set visible by tag mode argument
enum guiVisibleByTagMode {
    SHOW_IN_RANGE = 0x01,     HIDE_IN_RANGE = 0x02,
    SHOW_OUT_OF_RANGE = 0x04, HIDE_OUT_OF_RANGE = 0x08
};

// Check tabIndex result
#define TABINDEX_IS_MAX     2
#define TABINDEX_IS_MIN     1
#define TABINDEX_IS_NORM    0



//-----------------------------------//
// Keyboard support

// Keyboard codes are design-specific and should be defined in
// one of top-level modules
// If you want to override defalut GUI keys, define USE_CUSTOM_KEYS in guiConfig.h

#ifndef USE_CUSTOM_KEYS
#define USE_CUSTOM_KEYS

// Key event specifications
#define GUI_KEY_EVENT_DOWN      0x01        // A key has been pressed
#define GUI_KEY_EVENT_UP        0x02        // A key has been released
#define GUI_KEY_EVENT_UP_SHORT  0x03
#define GUI_KEY_EVENT_UP_LONG   0x04
#define GUI_KEY_EVENT_HOLD      0x05
#define GUI_KEY_EVENT_REPEAT    0x06
#define GUI_ENCODER_EVENT       0x07        // Encoder rotated

// Button codes
#define GUI_KEY_ESC     0x01
#define GUI_KEY_OK      0x02
#define GUI_KEY_LEFT    0x03
#define GUI_KEY_RIGHT   0x04
#define GUI_KEY_UP      0x05
#define GUI_KEY_DOWN    0x06
#define GUI_KEY_ENCODER 0x07

#endif


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



//-----------------------------------//
// GUI errors
#define emGUI_ERROR_OUT_OF_HEAP                 0x01
#define emGUI_ERROR_OUT_OF_PREALLOCATED_MEMORY  0x02
#define emGUI_ERROR_NULL_REF                    0x03


//-----------------------------------//
// Handler call specifiers
#define CALL_HANDLER    1
#define NO_HANDLER      0



void guiCore_AllocateWidgetCollection(guiGenericContainer_t *container, uint16_t count);
void guiCore_AllocateHandlers(void *widget, uint16_t count);
uint8_t guiCore_AddHandler(void *widget, uint8_t handlerType, eventHandler_t handler);



//===================================================================//
//                 GUI core message queue functions
//===================================================================//
uint8_t guiCore_AddMessageToQueue(const guiGenericWidget_t *target, const guiEvent_t *event);
uint8_t guiCore_GetMessageFromQueue(guiGenericWidget_t **target, guiEvent_t *event);
void guiCore_ProcessMessageQueue(void);
void guiCore_PostEventToFocused(guiEvent_t event);
// Common error handler
void guiCore_Error(uint8_t errCode);


//===================================================================//
//                      Top GUI core functions
//===================================================================//
void guiCore_Init(guiGenericWidget_t *guiRootWidget);
void guiCore_RedrawAll(void);
void guiCore_ProcessTouchEvent(int16_t x, int16_t y, uint8_t touchState);
void guiCore_ProcessKeyEvent(uint16_t code, uint8_t spec);
void guiCore_ProcessEncoderEvent(int16_t increment);

void guiCore_BroadcastEvent(guiEvent_t event, uint8_t(*validator)(guiGenericWidget_t *widget));
void guiCore_UpdateAll(void);
uint8_t guiCore_UpdateValidator(guiGenericWidget_t *widget);


//===================================================================//
//                    Drawing and touch support                      //
//                       geometry functions                          //
//===================================================================//
void guiCore_InvalidateRect(guiGenericWidget_t *widget, int16_t x1, int16_t y1, uint16_t x2, uint16_t y2);
uint8_t guiCore_CheckWidgetOvelap(guiGenericWidget_t *widget, rect16_t *rect);
void guiCore_ConvertToAbsoluteXY(guiGenericWidget_t *widget, int16_t *x, int16_t *y);
void guiCore_ConvertToRelativeXY(guiGenericWidget_t *widget, int16_t *x, int16_t *y);
guiGenericWidget_t *guiCore_GetTouchedWidgetAtXY(guiGenericWidget_t *widget, int16_t x, int16_t y);
uint8_t guiCore_IsWidgetVisible(guiGenericWidget_t *widget);
void guiCore_DecodeWidgetTouchEvent(guiGenericWidget_t *widget, guiEvent_t *touchEvent, widgetTouchState_t *decodedTouchState);
void guiCore_DecodeContainerTouchEvent(guiGenericWidget_t *widget, guiEvent_t *touchEvent, containerTouchState_t *decodedTouchState);


//===================================================================//
//                   Widget collections management                   //
//===================================================================//
uint8_t guiCore_AddWidgetToCollection(guiGenericWidget_t *widget, guiGenericContainer_t *container);
void guiCore_SetFocusOnNextWidget(guiGenericContainer_t *container, int8_t tabDir, uint8_t invokeType);
uint8_t guiCore_GetWidgetIndex(guiGenericWidget_t *widget);
uint8_t guiCore_CheckWidgetTabIndex(guiGenericWidget_t *widget);


//===================================================================//
//                   General widget API fucntions                    //
//===================================================================//
uint8_t guiCore_AcceptVisibleState(void *widget, uint8_t newVisibleState);
uint8_t guiCore_AcceptFocusedState(void *widget, uint8_t newFocusedState);
void guiCore_SetVisible(void *widget, uint8_t newVisibleState, uint8_t invokeType);
void guiCore_SetVisibleByTag(guiWidgetCollection_t *collection, uint8_t minTag, uint8_t maxTag, uint8_t mode, uint8_t invokeType);
void guiCore_SetVisibleExclusively(void *widget, uint8_t invokeType);
void guiCore_SetFocusOn(void *newFocusedWidget, uint8_t invokeType);
uint8_t guiCore_CallHandler(void *widget, uint8_t handlerType, guiEvent_t *event);




#endif
