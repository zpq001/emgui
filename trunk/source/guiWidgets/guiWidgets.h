/**********************************************************
    Module guiWidgets contains widget typedefs and
  common data



**********************************************************/

#ifndef __GUI_WIDGETS_H_
#define __GUI_WIDGETS_H_

#include <stdint.h>
#include "guiEvents.h"
#include "guiFonts.h"

// Event handler record
typedef struct {
    uint8_t eventType;                  // Event type
    void (*handler)(void *pSender);     // Related function pointer
} guiWidgetHandler_t;

// Event handlers table
typedef struct {
    uint8_t count;                      // Count of handler records
    guiWidgetHandler_t *elements;       // Pointer to array of handler records
} guiHandlerTable_t;

// Widget collection type - used by containers
typedef struct {
    uint8_t count;
    uint8_t focusedIndex;
    uint8_t traverseIndex;
    void **elements;
} guiWidgetCollection_t;




// TODO - add hasFrame to textLabel?

// Basic widget type - all widget types MUST have all fileds in their typedef beginning
typedef struct guiGenericWidget_t {
    // Pointer to parent widget
    struct guiGenericWidget_t *parent;
    // Bit properties:
    uint8_t acceptFocus : 1;
    uint8_t acceptFocusByTab : 1;
    uint8_t isContainer : 1;
    // Bit state flags:
    uint8_t isFocused : 1;
    uint8_t isVisible : 1;
    // Properties
    uint8_t tag;
    uint8_t tabIndex;
    // Event processing function
    uint8_t (*processEvent)(struct guiGenericWidget_t *pWidget, guiEvent_t event);
    // Handler table
    guiHandlerTable_t handlers;
} guiGenericWidget_t;


typedef struct guiGenericContainer_t {
    //----- Inherited from generic widget -----//
    // Pointer to parent widget
    struct guiGenericWidget_t *parent;
    // Bit properties:
    uint8_t acceptFocus : 1;
    uint8_t acceptFocusByTab : 1;
    uint8_t isContainer : 1;
    // Bit state flags:
    uint8_t isFocused : 1;
    uint8_t isVisible : 1;
    // Properties
    uint8_t tag;
    uint8_t tabIndex;
    // Event processing function
    uint8_t (*processEvent)(struct guiGenericWidget_t *pWidget, guiEvent_t event);
    // Handler table
    guiHandlerTable_t handlers;
    //-----------------------------------------//

    guiWidgetCollection_t widgets;

} guiGenericContainer_t;


typedef struct guiForm_t {
    //----- Inherited from generic widget -----//
    // Pointer to parent widget
    struct guiGenericWidget_t *parent;
    // Bit properties:
    uint8_t acceptFocus : 1;
    uint8_t acceptFocusByTab : 1;
    uint8_t isContainer : 1;
    // Bit state flags:
    uint8_t isFocused : 1;
    uint8_t isVisible : 1;
    // Properties
    uint8_t tag;
    uint8_t tabIndex;
    // Event processing function
    uint8_t (*processEvent)(struct guiGenericWidget_t *pWidget, guiEvent_t event);
    // Handler table
    guiHandlerTable_t handlers;
    //-----------------------------------------//

    guiWidgetCollection_t widgets;
    uint8_t redrawFlags;

} guiForm_t;




typedef struct guiTextLabel_t {
    //----- Inherited from generic widget -----//
    // Pointer to parent widget
    struct guiGenericWidget_t *parent;
    // Bit properties:
    uint8_t acceptFocus : 1;
    uint8_t acceptFocusByTab : 1;
    uint8_t isContainer : 1;
    // Bit state flags:
    uint8_t isFocused : 1;
    uint8_t isVisible : 1;
    // Properties
    uint8_t tag;
    uint8_t tabIndex;
    // Event processing function
    uint8_t (*processEvent)(struct guiGenericWidget_t *pWidget, guiEvent_t event);
    // Handler table
    guiHandlerTable_t handlers;
    //-----------------------------------------//

    uint8_t redrawFlags;
    int16_t x;
    int16_t y;
    uint16_t width;
    uint16_t height;
    uint8_t alignment;
    const tFont *font;
    char *text;

} guiTextLabel_t;












#endif
