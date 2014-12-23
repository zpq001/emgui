#ifndef __GUI_EVENTS_H_
#define __GUI_EVENTS_H_

#include <stdint.h>

// Event types
#define GUI_COMMON_EVENTS   0           // Event types, common for whole GUI, should start with this value
#define GUI_CUSTOM_EVENTS   0x20        // Custom user-defined event types

enum guiCommonEventTypes {
    GUI_EVENT_INIT = GUI_COMMON_EVENTS,
    GUI_EVENT_DRAW,
    GUI_EVENT_UPDATE,
    GUI_EVENT_SHOW,
    GUI_EVENT_HIDE,
    GUI_EVENT_FOCUS,
    GUI_EVENT_UNFOCUS,
    GUI_EVENT_TOUCH,
    GUI_EVENT_KEY,
    //GUI_EVENT_ENCODER,
    GUI_EVENT_TIMER
};

// Widget event handler types
#define GUI_COMMON_WIDGET_HANDLERS      0       // Event handler types, common for all widgets. Unique.
#define GUI_SPECIFIC_WIDGET_HANDLERS    0x20    // Event handler types, widget-specific. May overlap between different widgets.
#define GUI_CUSTOM_HANDLERS             0x80    // Custom user-defined handler types

enum guiCommonWidgetHandlerTypes {
    WIDGET_ON_VISIBLE_CHANGED = GUI_COMMON_WIDGET_HANDLERS,
    WIDGET_ON_FOCUS_CHANGED,
    WIDGET_ON_DRAW_EVENT,
    WIDGET_ON_KEY_EVENT,
    WIDGET_ON_TOUCH_EVENT,
    WIDGET_ON_UNKNOWN_EVENT
};



// Event struct, common for all GUI elements
typedef struct {
    uint8_t type;
    uint8_t spec;
    union {
        struct {
            uint16_t lparam;
            uint16_t hparam;
        } params;
        void *data;     // May be used for passing some data to widgets instead of params
    } payload;
} guiEvent_t;



// Events are found in guiCore.c
extern const guiEvent_t guiEvent_DRAW;
extern const guiEvent_t guiEvent_DRAW_ALL;
extern const guiEvent_t guiEvent_SELECT;
extern const guiEvent_t guiEvent_DESELECT;
extern const guiEvent_t guiEvent_UPDATE;
extern const guiEvent_t guiEvent_HIDE;
extern const guiEvent_t guiEvent_SHOW;



#endif
