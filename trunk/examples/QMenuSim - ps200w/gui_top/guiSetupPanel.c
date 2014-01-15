/**********************************************************
    Module guiSetupPanel




**********************************************************/


#include <stdio.h>      // due to printf
#include <stdint.h>

#include "guiFonts.h"
#include "guiGraphHAL.h"
#include "guiGraphPrimitives.h"
#include "guiGraphWidgets.h"
#include "guiImages.h"

#include "guiCore.h"
#include "guiEvents.h"
#include "guiWidgets.h"
#include "guiPanel.h"
#include "guiTextLabel.h"
#include "guiSpinBox.h"
#include "guiStringList.h"

// Other forms and panels - in order to switch between them
#include "guiMasterPanel.h"
#include "guiSetupPanel.h"

#include "guiTop.h"



static uint8_t guiSetupPanel_ProcessEvents(struct guiGenericWidget_t *widget, guiEvent_t event);


//--------- Form elements ---------//
guiStringList_t setupList;
#define SETUP_LIST_ELEMENTS_COUNT 6
char *setupListElements[SETUP_LIST_ELEMENTS_COUNT];


//--------- Setup panel  ----------//
#define SETUP_PANEL_ELEMENTS_COUNT 8
guiPanel_t     guiSetupPanel;
static void *guiSetupPanelElements[SETUP_PANEL_ELEMENTS_COUNT];



//-------------------------------------------------------//
//  Panel initialization
//
//-------------------------------------------------------//
void guiSetupPanel_Initialize(guiGenericWidget_t *parent)
{
    // Initialize
    guiPanel_Initialize(&guiSetupPanel, parent);
    guiSetupPanel.processEvent = guiSetupPanel_ProcessEvents;     // redefine standard panel message processing funtion
    guiSetupPanel.widgets.count = SETUP_PANEL_ELEMENTS_COUNT;
    guiSetupPanel.widgets.elements = guiSetupPanelElements;
    guiSetupPanel.widgets.elements[0] = &setupList;
    guiSetupPanel.widgets.elements[1] = 0;
    guiSetupPanel.widgets.elements[2] = 0;
    guiSetupPanel.widgets.elements[3] = 0;
    guiSetupPanel.widgets.elements[4] = 0;
    guiSetupPanel.widgets.elements[5] = 0;
    guiSetupPanel.widgets.elements[6] = 0;
    guiSetupPanel.widgets.elements[7] = 0;
    guiSetupPanel.x = 0;
    guiSetupPanel.y = 0;
    guiSetupPanel.width = 96 * 2;
    guiSetupPanel.height = 68;
    guiSetupPanel.showFocus = 0;
    guiSetupPanel.focusFallsThrough = 0;

    guiStringList_Initialize(&setupList, (guiGenericWidget_t *)&guiSetupPanel );
    setupList.font = &font_h10;
    setupList.textAlignment = ALIGN_CENTER;
    setupList.hasFrame = 1;
    setupList.x = 2;
    setupList.y = 12;
    setupList.width = 96 - 4;
    setupList.height = 68 - 14;
    setupList.stringCount = SETUP_LIST_ELEMENTS_COUNT;
    setupList.strings = setupListElements;
    setupList.strings[0] = "0000";
    setupList.strings[1] = "1111";
    setupList.strings[2] = "2222";
    setupList.strings[3] = "3333";
    setupList.strings[4] = "4444";
    setupList.strings[5] = "5555";
}




static uint8_t guiSetupPanel_ProcessEvents(struct guiGenericWidget_t *widget, guiEvent_t event)
{
    uint8_t processResult = GUI_EVENT_ACCEPTED;
    switch (event.type)
    {
        case GUI_EVENT_DRAW:
            guiGraph_DrawPanel(&guiSetupPanel);
            if (guiSetupPanel.redrawForced)
            {
                // Draw static elements
                LCD_SetPixelOutputMode(PIXEL_MODE_REWRITE);
                LCD_SetFont(&font_h10_bold);
                LCD_PrintString("Settings", 22, 0, IMAGE_MODE_NORMAL);
                //LCD_SetFont(&font_h11);
                //LCD_PrintString("TODO!", 20, 30, IMAGE_MODE_NORMAL);
            }
            // Reset flags - redrawForced will be reset by core
            guiSetupPanel.redrawFocus = 0;
            guiSetupPanel.redrawRequired = 0;
            break;
        case GUI_EVENT_FOCUS:
            processResult = guiPanel_ProcessEvent(widget, event);
            if (processResult == GUI_EVENT_ACCEPTED)
                guiCore_RequestFocusNextWidget((guiGenericContainer_t *)&guiSetupPanel,1);
            break;
        case GUI_EVENT_KEY:
            if ((event.spec == GUI_KEY_EVENT_DOWN) && (event.lparam == GUI_KEY_ESC))
            {

            }
            if ((event.spec == GUI_KEY_EVENT_DOWN) && (event.lparam == GUI_KEY_ENCODER))
            {

            }
            // fall down to default
        default:
            processResult = guiPanel_ProcessEvent(widget, event);
    }

    return processResult;
}



