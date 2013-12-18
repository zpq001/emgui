#ifndef __GUI_PANEL_H_
#define __GUI_PANEL_H_

#include <stdint.h>
#include "guiWidgets.h"


// Redraw flags:
//#define PANEL_REDRAW_FOCUS       (1<<0)
#define PANEL_REDRAW_BACKGROUND  (1<<1)

#define PANEL_FOCUS_RECT_MARGIN    2


// Widget-specific keys
#define PANEL_KEY_SELECT    0x01
#define PANEL_KEY_ESC       0x02
#define PANEL_KEY_PREV      0x03
#define PANEL_KEY_NEXT      0x04


// Widget-specific state checks
#define PANEL_ACCEPTS_FOCUS_EVENT(panel)  ( (panel->isVisible) && (1) )    // TODO - add isEnabled
#define PANEL_ACCEPTS_KEY_EVENT(panel)    ( (panel->isVisible) )           // TODO - add isEnabled
#define PANEL_ACCEPTS_ENCODER_EVENT(panel) ( (panel->isVisible) )           // TODO - add isEnabled
#define PANEL_ACCEPTS_TOUCH_EVENT(panel)  ( (panel->isVisible) )           // TODO - add isEnabled


void guiPanel_Initialize(guiPanel_t *panel, guiGenericWidget_t *parent);
uint8_t guiPanel_ProcessKey(guiPanel_t *panel, uint8_t key);
uint8_t guiPanel_ProcessEvent(guiGenericWidget_t *widget, guiEvent_t event);




#endif
