
#ifndef __GUI_WIDGET_COMMON_H_
#define __GUI_WIDGET_COMMON_H_

#include <stdint.h>
#include "guiEvents.h"


#define WF_IS_SELECTED              (1<<0)
#define WF_IS_ACTIVE                (1<<1)
#define WF_LAST_CHANGES_ACCEPTED    (1<<2)
/*
    All widgets have two flags - IS_ACTIVE and IS_SELECTED

    IS_SELECTED means that widget will get events from upper container and process them.
    If a widget is selected, but not active it will not process events that change it's inner data, but
    will draw itself selected, thus allowing upper container to select another widget.
    IS_ACTIVE means that widget does process events that change it's data.
    A widget cannot be active but not selected.

    For example, if a listBox is selected, but not active, it will not process button events.
    If a listBox is selected and active, it accepts button events and change selected index.

    Entering IS_ACTIVE state typically is done by BTN_OK event when widget is selected.
    Leaving IS_ACTIVE state can be done either by BTN_OK or BTN_ESC, allowing saving or discarding recent changes.

    A widget may have WP_SELECT_IS_ACTIVATE property set ??? TODO
*/

// _SELECT_FIRST_ELEMENT_ON_ACTIVATE - TODO

#define EXIT_MODE_CONFIRM    0
#define EXIT_MODE_DECLINE    (1<<7)




#define WF_REDRAW            (1<<0)     // Set if whole widget needs to be redrawed. If widget has children, all of them will be sent DRAW_ALL event
                                        // This flag is common for all widgets
#define WF_REDRAW_CONTENT    (1<<1)     // Set when some internal widget elements need to be redrawed.
#define WF_REDRAW_SELECTION  (1<<2)


//#define WP_IS_SELECTABLE     (1<<0)
#define WP_IS_VISIBLE           (1<<1)
#define WP_SELECT_IS_ACTIVATE   (1<<2)


#define EVENT_FLAG_NOT_USED      0x01
#define EVENT_FLAG_ACCEPTED      0x02





//---------------------------------------------//
//---------------------------------------------//

// Containers are:
//  - form
//  - groupBox

typedef struct {
    uint8_t eventType;
    void (*handler)(void *pSender);
} guiWidgetHandler_t;

typedef struct {
    uint8_t count;
    guiWidgetHandler_t *elements;
} guiHandlerTable_t;

typedef struct {
    uint16_t count;
    void *pSelected;
    void **elements;
} guiWidgetCollection_t;


// Fields withis this structure MUST be located first in exact same order in every widget struct
// http://stackoverflow.com/questions/9747010/does-accessing-the-first-field-of-a-struct-via-a-c-cast-violate-strict-aliasing
// Field description:
//   type:           specifies type of a widget. Depending on this value data gets different processing
//   redrawFlags:    provides information for drawing
//   tabIndex:       if zero, widget cannot be selected by buttons. Otherwise, specifies tab number (like win forms)
//
typedef struct guiGenericWidget_t {
    uint8_t type;
    uint8_t redrawFlags;
    uint8_t tabIndex;
    uint8_t state;
    uint8_t tag;
    uint8_t (*processEvent)(struct guiGenericWidget_t *pWidget, guiEvent_t event);
    guiHandlerTable_t handlers;
    uint8_t properties;
} guiGenericWidget_t;
/*
typedef struct guiGenericContainer_t {
    uint8_t type;
    uint8_t redrawFlags;
    uint8_t tabIndex;
    uint8_t state;
    void (*processEvent)(struct guiGenericContainer_t *pContainer, guiEvent_t event);
    guiHandlerTable_t handlers;
    guiWidgetCollection_t widgets;
} guiGenericContainer_t;
*/

typedef struct {
    uint8_t type;
    uint8_t redrawFlags;
    uint8_t tabIndex;
    uint8_t state;
    uint8_t tag;
    uint8_t (*processEvent)(guiEvent_t event); // CHECKME - args
    guiHandlerTable_t handlers;
    guiWidgetCollection_t widgets;

    uint8_t properties;

} guiForm_t;      // Any form



//---------------------------------------------//
//---------------------------------------------//



// Widget types
#define WT_TEXT_LABEL       2
#define WT_FORM             1
#define WT_LISTBOX          3



#endif

