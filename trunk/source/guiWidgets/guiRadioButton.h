#ifndef __GUI_RADIO_BUTTON_H_
#define __GUI_RADIO_BUTTON_H_

#include <stdint.h>
#include "guiWidgets.h"


// Appearance
//#define BUTTON_FOCUS_RECT_MARGIN    2

#define RADIOBUTTON_RADIUS  6
#define RADIOBUTTON_CHECK_RADIUS  2
#define RADIOBUTTON_TEXT_MARGIN  5


// Widget-specific events
#define RADIOBUTTON_CHECKED_CHANGED    (0xC0 + 0x00)



// Widget-specific keys
#define RADIOBUTTON_KEY_SELECT     0x01




// Widget-specific state checks
#define RADIOBUTTON_ACCEPTS_FOCUS_EVENT(button)  ( (button->isVisible) && (1) )    // TODO - add isEnabled
#define RADIOBUTTON_ACCEPTS_KEY_EVENT(button)    ( (button->isFocused) && \
                                                   (button->isVisible) )           // TODO - add isEnabled
#define RADIOBUTTON_ACCEPTS_TOUCH_EVENT(button)  ( (button->isVisible) )           // TODO - add isEnabled




void guiRadioButton_Initialize(guiRadioButton_t *button, guiGenericWidget_t *parent);
uint8_t guiRadioButton_ProcessEvent(guiGenericWidget_t *widget, guiEvent_t event);

//uint8_t guiButton_SetPressed(guiButton_t *button, uint8_t newPressedState);
//void guiButton_Click(guiButton_t *button);
//uint8_t guiButton_ProcessKey(guiButton_t *button, uint8_t key, uint8_t enableClick);
//uint8_t guiButton_ProcessEvent(guiGenericWidget_t *widget, guiEvent_t event);




#endif
