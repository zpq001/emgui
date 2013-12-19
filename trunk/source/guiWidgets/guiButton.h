#ifndef __GUI_BUTTON_H_
#define __GUI_BUTTON_H_

#include <stdint.h>
#include "guiWidgets.h"


// Widget-specific events
#define BUTTON_PRESSED_CHANGED    (0xC0 + 0x00)
#define BUTTON_CLICKED            (0xC0 + 0x01)



// Widget-specific keys
#define BUTTON_KEY_PRESS     0x01
#define BUTTON_KEY_RELEASE   0x02




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
