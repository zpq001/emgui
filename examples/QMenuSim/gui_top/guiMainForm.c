/**********************************************************
    Module guiMainForm




**********************************************************/

#include <stdio.h>      // due to printf
#include <stdint.h>

#include "guiFonts.h"
#include "guiGraphPrimitives.h"
#include "guiGraphHAL.h"
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

    guiTextLabel_Initialize(&textLabel1, (guiGenericWidget_t *)&guiMainForm);
    textLabel1.tabIndex = 1;
    textLabel1.acceptFocus = 1;
    textLabel1.acceptFocusByTab = 1;
    textLabel1.x = 128 + 50;
    textLabel1.y = 114;
    textLabel1.width = 78;
    textLabel1.height = 14;
    textLabel1.alignment = ALIGN_CENTER;
    textLabel1.text = textLabel1_data;

    // Show subForm1
    guiSubForm1.isVisible = 1;
    guiSubForm1.isFocused = 1;
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
            LCD_SetPixelOutputMode(PIXEL_MODE_REWRITE);
            LCD_FillWholeBuffer(0);
            LCD_SetLineStyle(LINE_STYLE_SOLID);
            LCD_DrawHorLine(0,110,255,1);
            guiMainForm.redrawRequired = 0;
            break;
    }
    return 0;
}

