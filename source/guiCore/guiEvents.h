#ifndef __GUI_EVENTS_H_
#define __GUI_EVENTS_H_

#include <stdint.h>


// Event types for widgets
#define GUI_EVENT_DRAW         0x01
#define GUI_EVENT_UPDATE       0x04
//#define GUI_EVENT_BUTTONS_ENCODER       0x05
#define GUI_EVENT_HIDE          0x06
#define GUI_EVENT_SHOW          0x07
#define GUI_EVENT_UNFOCUS       0x08
#define GUI_EVENT_FOCUS         0x09
#define GUI_EVENT_TOUCH         0x0A
#define GUI_EVENT_KEY           0x0B
#define GUI_EVENT_ENCODER       0x0C

// Event types for callbacks (common widget event handlers)
#define GUI_ON_FOCUS_CHANGED    0x80
#define GUI_ON_DRAW             0x81
#define GUI_ON_VISIBLE_CHANGED  0x82
#define GUI_ON_TOUCH_EVENT      0x83

// Event types, specific for widgets start with 0xC0 and can overlap for different widgets
// those types are declared in widget's header files.








// Event struct, common for all GUI elements
typedef struct {
    uint8_t type;
    uint8_t spec;
    uint16_t lparam;
    uint16_t hparam;
    //void *args;
} guiEvent_t;









// Events are found in guiEvents.c
extern const guiEvent_t guiEvent_DRAW;
extern const guiEvent_t guiEvent_DRAW_ALL;
extern const guiEvent_t guiEvent_SELECT;
extern const guiEvent_t guiEvent_DESELECT;
extern const guiEvent_t guiEvent_UPDATE;
extern const guiEvent_t guiEvent_HIDE;
extern const guiEvent_t guiEvent_SHOW;




#endif
