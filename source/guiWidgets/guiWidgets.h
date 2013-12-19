/**********************************************************
    Module guiWidgets contains widget typedefs and
  common data



**********************************************************/

#ifndef __GUI_WIDGETS_H_
#define __GUI_WIDGETS_H_

#include <stdint.h>
#include "guiEvents.h"
#include "guiFonts.h"
#include "guiGraphPrimitives.h"


// Widget types
#define WT_PANEL       0x01
#define WT_BUTTON      0x02
#define WT_CHECKBOX    0x03
#define WT_RADIOBUTTON 0x04
#define WT_TEXTLABEL   0x05




// Event handler record
typedef struct {
    uint8_t eventType;                                         // Event type
    uint8_t (*handler)(void *sender, guiEvent_t *event);       // Related callback function pointer
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





// Basic widget type - all widget types MUST have all fileds in their typedef beginning
typedef struct guiGenericWidget_t {
    // Widget type (starting with WT_)
    uint8_t type;
    // Pointer to parent widget
    struct guiGenericWidget_t *parent;
    // Bit properties:
    uint8_t acceptFocus : 1;
    uint8_t acceptFocusByTab : 1;
    uint8_t acceptTouch : 1;
    uint8_t isContainer : 1;
    // Bit state flags:
    uint8_t isFocused : 1;
    uint8_t isVisible : 1;
    uint8_t redrawRequired : 1;     // If this flag is set, widget will be sent DRAW event.
                                    // Widget should set this flag itself.
    uint8_t redrawForced : 1;       // This flag is set by GUI core when widget must be redrawn
                                    // redrawRequired is set along with redrawForced.
    uint8_t redrawFocus : 1;        // Flag is set when widget focus must be redrawn.
                                    // redrawRequired is set along with redrawFocus.
    uint8_t keepTouch : 1;
    // Properties
    uint8_t tag;
    uint8_t tabIndex;
    int16_t x;
    int16_t y;
    uint16_t width;
    uint16_t height;
    // Event processing function
    uint8_t (*processEvent)(struct guiGenericWidget_t *pWidget, guiEvent_t event);
    // Handler table
    guiHandlerTable_t handlers;
} guiGenericWidget_t;


typedef struct guiGenericContainer_t {
    //----- Inherited from generic widget -----//
    // Widget type (starting with WT_)
    uint8_t type;
    // Pointer to parent widget
    struct guiGenericWidget_t *parent;
    // Bit properties:
    uint8_t acceptFocus : 1;
    uint8_t acceptFocusByTab : 1;
    uint8_t acceptTouch : 1;
    uint8_t isContainer : 1;
    // Bit state flags:
    uint8_t isFocused : 1;
    uint8_t isVisible : 1;
    uint8_t redrawRequired : 1;
    uint8_t redrawForced : 1;
    uint8_t redrawFocus : 1;
    uint8_t keepTouch : 1;
    // Properties
    uint8_t tag;
    uint8_t tabIndex;
    int16_t x;
    int16_t y;
    uint16_t width;
    uint16_t height;
    // Event processing function
    uint8_t (*processEvent)(struct guiGenericWidget_t *pWidget, guiEvent_t event);
    // Handler table
    guiHandlerTable_t handlers;
    //-----------------------------------------//

    guiWidgetCollection_t widgets;

} guiGenericContainer_t;


typedef struct guiForm_t {
    //----- Inherited from generic widget -----//
    // Widget type (starting with WT_)
    uint8_t type;
    // Pointer to parent widget
    struct guiGenericWidget_t *parent;
    // Bit properties:
    uint8_t acceptFocus : 1;
    uint8_t acceptFocusByTab : 1;
    uint8_t acceptTouch : 1;
    uint8_t isContainer : 1;
    // Bit state flags:
    uint8_t isFocused : 1;
    uint8_t isVisible : 1;
    uint8_t redrawRequired : 1;
    uint8_t redrawForced : 1;
    uint8_t redrawFocus : 1;
    uint8_t keepTouch : 1;
    // Properties
    uint8_t tag;
    uint8_t tabIndex;
    int16_t x;
    int16_t y;
    uint16_t width;
    uint16_t height;
    // Event processing function
    uint8_t (*processEvent)(struct guiGenericWidget_t *pWidget, guiEvent_t event);
    // Handler table
    guiHandlerTable_t handlers;
    //-----------------------------------------//

    guiWidgetCollection_t widgets;
    uint8_t redrawFlags;
    uint8_t hasFrame : 1;
    uint8_t focusFallsThrough : 1;


} guiForm_t;


typedef struct guiPanel_t {
    //----- Inherited from generic widget -----//
    // Widget type (starting with WT_)
    uint8_t type;
    // Pointer to parent widget
    struct guiGenericWidget_t *parent;
    // Bit properties:
    uint8_t acceptFocus : 1;
    uint8_t acceptFocusByTab : 1;
    uint8_t acceptTouch : 1;
    uint8_t isContainer : 1;
    // Bit state flags:
    uint8_t isFocused : 1;
    uint8_t isVisible : 1;
    uint8_t redrawRequired : 1;
    uint8_t redrawForced : 1;
    uint8_t redrawFocus : 1;
    uint8_t keepTouch : 1;
    // Properties
    uint8_t tag;
    uint8_t tabIndex;
    int16_t x;
    int16_t y;
    uint16_t width;
    uint16_t height;
    // Event processing function
    uint8_t (*processEvent)(struct guiGenericWidget_t *pWidget, guiEvent_t event);
    // Handler table
    guiHandlerTable_t handlers;
    //-----------------------------------------//

    guiWidgetCollection_t widgets;
    uint8_t focusFallsThrough : 1;
    uint8_t frame : 3;
    uint8_t showFocus : 1;
    uint8_t useDefaultKeyHandler : 1;
    uint8_t useDefaultEncoderHandler : 1;

} guiPanel_t;



typedef struct guiTextLabel_t {
    //----- Inherited from generic widget -----//
    // Widget type (starting with WT_)
    uint8_t type;
    // Pointer to parent widget
    struct guiGenericWidget_t *parent;
    // Bit properties:
    uint8_t acceptFocus : 1;
    uint8_t acceptFocusByTab : 1;
    uint8_t acceptTouch : 1;
    uint8_t isContainer : 1;
    // Bit state flags:
    uint8_t isFocused : 1;
    uint8_t isVisible : 1;
    uint8_t redrawRequired : 1;
    uint8_t redrawForced : 1;
    uint8_t redrawFocus : 1;
    uint8_t keepTouch : 1;
    // Properties
    uint8_t tag;
    uint8_t tabIndex;
    int16_t x;
    int16_t y;
    uint16_t width;
    uint16_t height;
    // Event processing function
    uint8_t (*processEvent)(struct guiGenericWidget_t *pWidget, guiEvent_t event);
    // Handler table
    guiHandlerTable_t handlers;
    //-----------------------------------------//

    uint8_t redrawFlags;
    uint8_t alignment;
    const tFont *font;
    char *text;
    uint8_t hasFrame : 1;

} guiTextLabel_t;


typedef struct guiCheckBox_t {
    //----- Inherited from generic widget -----//
    // Widget type (starting with WT_)
    uint8_t type;
    // Pointer to parent widget
    struct guiGenericWidget_t *parent;
    // Bit properties:
    uint8_t acceptFocus : 1;
    uint8_t acceptFocusByTab : 1;
    uint8_t acceptTouch : 1;
    uint8_t isContainer : 1;
    // Bit state flags:
    uint8_t isFocused : 1;
    uint8_t isVisible : 1;
    uint8_t redrawRequired : 1;
    uint8_t redrawForced : 1;
    uint8_t redrawFocus : 1;
    uint8_t keepTouch : 1;
    // Properties
    uint8_t tag;
    uint8_t tabIndex;
    int16_t x;
    int16_t y;
    uint16_t width;
    uint16_t height;
    // Event processing function
    uint8_t (*processEvent)(struct guiGenericWidget_t *pWidget, guiEvent_t event);
    // Handler table
    guiHandlerTable_t handlers;
    //-----------------------------------------//

    uint8_t textAlignment;
    const tFont *font;
    char *text;
    uint8_t hasFrame : 1;
    uint8_t isChecked : 1;
    uint8_t useDefaultKeyHandler : 1;
    uint8_t redrawCheckedState : 1;


} guiCheckBox_t;


typedef struct guiButton_t {
    //----- Inherited from generic widget -----//
    // Widget type (starting with WT_)
    uint8_t type;
    // Pointer to parent widget
    struct guiGenericWidget_t *parent;
    // Bit properties:
    uint8_t acceptFocus : 1;
    uint8_t acceptFocusByTab : 1;
    uint8_t acceptTouch : 1;
    uint8_t isContainer : 1;
    // Bit state flags:
    uint8_t isFocused : 1;
    uint8_t isVisible : 1;
    uint8_t redrawRequired : 1;
    uint8_t redrawForced : 1;
    uint8_t redrawFocus : 1;
    uint8_t keepTouch : 1;
    // Properties
    uint8_t tag;
    uint8_t tabIndex;
    int16_t x;
    int16_t y;
    uint16_t width;
    uint16_t height;
    // Event processing function
    uint8_t (*processEvent)(struct guiGenericWidget_t *pWidget, guiEvent_t event);
    // Handler table
    guiHandlerTable_t handlers;
    //-----------------------------------------//

    uint8_t redrawPressedState : 1;
    uint8_t textAlignment;
    const tFont *font;
    char *text;
    uint8_t isPressed : 1;
    uint8_t useDefaultKeyHandler : 1;
    uint8_t isToggle : 1;
    uint8_t isPressOnly : 1;

} guiButton_t;



typedef struct guiRadioButton_t {
    //----- Inherited from generic widget -----//
    // Widget type (starting with WT_)
    uint8_t type;
    // Pointer to parent widget
    struct guiGenericWidget_t *parent;
    // Bit properties:
    uint8_t acceptFocus : 1;
    uint8_t acceptFocusByTab : 1;
    uint8_t acceptTouch : 1;
    uint8_t isContainer : 1;
    // Bit state flags:
    uint8_t isFocused : 1;
    uint8_t isVisible : 1;
    uint8_t redrawRequired : 1;
    uint8_t redrawForced : 1;
    uint8_t redrawFocus : 1;
    uint8_t keepTouch : 1;
    // Properties
    uint8_t tag;
    uint8_t tabIndex;
    int16_t x;
    int16_t y;
    uint16_t width;
    uint16_t height;
    // Event processing function
    uint8_t (*processEvent)(struct guiGenericWidget_t *pWidget, guiEvent_t event);
    // Handler table
    guiHandlerTable_t handlers;
    //-----------------------------------------//

    uint8_t redrawCheckedState : 1;
    uint8_t textAlignment;
    uint8_t radioIndex;
    const tFont *font;
    char *text;
    uint8_t isChecked : 1;
    uint8_t useDefaultKeyHandler : 1;


} guiRadioButton_t;





//-----------------------------------------//
// Common widget fields and properties




#endif
