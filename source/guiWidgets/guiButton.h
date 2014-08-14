#ifndef __GUI_BUTTON_H_
#define __GUI_BUTTON_H_

#include "guiWidgets.h"
#include "guiFonts.h"

// Widget type ID - must be unique!
#define WT_BUTTON       0x02


typedef struct guiButton_t {
    //----- Inherited from generic widget -----//
    GENERIC_WIDGET_PATTERN
    //------- Widget - specific fields --------//
    char *text;
    const tFont *font;
    uint8_t textAlignment;
    uint8_t redrawPressedState : 1;
    uint8_t isPressed : 1;
    uint8_t isToggle : 1;
    uint8_t isPressOnly : 1;
} guiButton_t;






// Widget-specific events
#define BUTTON_PRESSED_CHANGED    (0xC0 + 0x00)
#define BUTTON_CLICKED            (0xC0 + 0x01)


// Widget-specific virtual keys
enum guiButtonVirtualKeys {
    BUTTON_KEY_PRESS = 0x01,
    BUTTON_KEY_RELEASE
};

// Translated key event struct
typedef struct {
    uint8_t key;
} guiButtonTranslatedKey_t;






// Widget-specific state checks
#define BUTTON_ACCEPTS_FOCUS_EVENT(button)  ( (button->isVisible) && (1) )    // TODO - add isEnabled
#define BUTTON_ACCEPTS_KEY_EVENT(button)    ( (button->isFocused) && \
                                              (button->isVisible) )           // TODO - add isEnabled
#define BUTTON_ACCEPTS_TOUCH_EVENT(button)  ( (button->isVisible) )           // TODO - add isEnabled




void guiButton_Initialize(guiButton_t *button, guiGenericWidget_t *parent);

uint8_t guiButton_SetPressed(guiButton_t *button, uint8_t newPressedState);
void guiButton_Click(guiButton_t *button);
uint8_t guiButton_ProcessKey(guiButton_t *button, uint8_t key, uint8_t enableClick);
uint8_t guiButton_ProcessEvent(guiGenericWidget_t *widget, guiEvent_t event);




#endif
