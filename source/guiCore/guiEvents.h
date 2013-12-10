#ifndef __GUI_EVENTS_H_
#define __GUI_EVENTS_H_

#include <stdint.h>


// Event types for widgets
#define GUI_EVENT_DRAW         0x01
#define GUI_EVENT_UPDATE       0x04
#define GUI_EVENT_BUTTONS_ENCODER       0x05
#define GUI_EVENT_HIDE          0x06
#define GUI_EVENT_SHOW          0x07
#define GUI_EVENT_UNFOCUS       0x08
#define GUI_EVENT_FOCUS         0x09

// Event types for callbacks (common widget event handlers)
#define GUI_ON_FOCUS_CHANGED    0x80
#define GUI_ON_DRAW             0x81
#define GUI_ON_VISIBLE_CHANGED  0x82


// Temporary
#define GUI_BTN_ESC     (1<<8)
#define GUI_BTN_LEFT    (1<<9)
#define GUI_BTN_RIGHT   (1<<10)
#define GUI_BTN_OK      (1<<11)


// Event struct, common for all GUI elements
typedef struct {
    uint8_t type;
    void *args;
} guiEvent_t;


// Event args for buttons and encoder
typedef struct {
    uint16_t buttonCode;
    int16_t encoderDelta;
} guiEventArgButtons_t;


// Events are found in guiEvents.c
extern const guiEvent_t guiEvent_DRAW;
extern const guiEvent_t guiEvent_DRAW_ALL;
extern const guiEvent_t guiEvent_SELECT;
extern const guiEvent_t guiEvent_DESELECT;
extern const guiEvent_t guiEvent_UPDATE;
extern const guiEvent_t guiEvent_HIDE;
extern const guiEvent_t guiEvent_SHOW;




#endif
