/**********************************************************
    Module guiMainForm




**********************************************************/

#include <stdio.h>      // due to printf
#include <stdint.h>

#include "guiFonts.h"
#include "guiGraphHAL.h"
#include "guiGraphPrimitives.h"
#include "guiGraphWidgets.h"

#include "guiCore.h"
#include "guiEvents.h"
#include "guiWidgets.h"
#include "guiTextLabel.h"
#include "guiForm.h"


// Other forms - in order to switch between them
#include "guiMainForm.h"
#include "guiSubForm1.h"

extern void guiLogEvent(char *string);
extern uint8_t timeHours;
extern uint8_t timeMinutes;
extern uint8_t timeSeconds;


static uint8_t guiMainForm_ProcessEvents(guiGenericWidget_t *pWidget, guiEvent_t event);


//--------- Form elements ---------//
static guiTextLabel_t textLabel1;
static char textLabel1_data[50];


//----------- GUI Form  -----------//
guiForm_t     guiMainForm;
static void *guiMainFormElements[2];


void guiMainForm_Initialize(void)
{
    // Initialize gui elements

    guiForm_Initialize(&guiMainForm);
    guiMainForm.processEvent = guiMainForm_ProcessEvents;
    guiMainForm.widgets.count = 2;
    guiMainForm.widgets.elements = guiMainFormElements;
    guiMainForm.widgets.elements[0] = &guiSubForm1;
    guiMainForm.widgets.elements[1] = &textLabel1;
    guiMainForm.isVisible = 1;
    guiMainForm.redrawRequired = 1;
    guiMainForm.redrawForced = 1;
    guiMainForm.x = 0;
    guiMainForm.y = 0;
    guiMainForm.width = 255;
    guiMainForm.height = 128;

    guiTextLabel_Initialize(&textLabel1, (guiGenericWidget_t *)&guiMainForm);
    textLabel1.tabIndex = 1;
    textLabel1.acceptFocus = 1;
    textLabel1.acceptFocusByTab = 1;
    textLabel1.x = 128 + 50;
    textLabel1.y = 112;
    textLabel1.width = 70;
    textLabel1.height = 14;
    textLabel1.alignment = ALIGN_CENTER;
    textLabel1.text = textLabel1_data;

    // Show subForm1
    guiSubForm1.isVisible = 1;
    guiSubForm1.isFocused = 1;
    guiSubForm1.redrawRequired = 1;
    guiSubForm1.redrawForced = 1;
}


static uint8_t guiMainForm_ProcessEvents(struct guiGenericWidget_t *pWidget, guiEvent_t event)
{
    // Process GUI messages - select, draw, etc
    switch(event.type)
    {
          case GUI_EVENT_UPDATE:
            sprintf(textLabel1.text, "%2d:%02d:%02d", timeHours, timeMinutes, timeSeconds);
            guiTextLabel_SetRedrawFlags(&textLabel1, TEXT_LABEL_REDRAW_TEXT);
            guiSubForm1.processEvent((guiGenericWidget_t *)&guiSubForm1, guiEvent_UPDATE);  //
            break;
          case GUI_EVENT_DRAW:
            // Check if full redraw is required
            if (guiMainForm.redrawForced)
            {
                // Widget must be fully redrawn - set all flags
                guiMainForm.redrawFlags = FORM_REDRAW_FOCUS |
                                         FORM_REDRAW_BACKGROUND;
            }
            guiGraph_DrawForm(&guiMainForm);
            // Draw static elemens
            if (guiMainForm.redrawFlags & FORM_REDRAW_BACKGROUND)
                LCD_DrawHorLine(0,110,255,1);
            // Reset flags
            guiMainForm.redrawFlags = 0;
            guiMainForm.redrawRequired = 0;
            break;
        case GUI_EVENT_FOCUS:
            guiCore_RequestFocusChange((guiGenericWidget_t *)&guiSubForm1);

            break;
        case GUI_EVENT_UNFOCUS:

            break;
    }
    return GUI_EVENT_ACCEPTED;
}


