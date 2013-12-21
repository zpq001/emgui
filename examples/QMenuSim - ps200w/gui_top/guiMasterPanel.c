/**********************************************************
    Module guiMasterPanel




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
#include "guiPanel.h"
#include "guiTextLabel.h"

// Other forms and panels - in order to switch between them
#include "guiMasterPanel.h"
#include "guiMasterPanel.h"



static uint8_t guiMasterPanel_ProcessEvents(struct guiGenericWidget_t *widget, guiEvent_t event);



//--------- Form elements ---------//
static guiTextLabel_t textLabel_voltage;        // Measured voltage
static char label_voltage_data[10];
static guiTextLabel_t textLabel_current;        // Measured current
static char label_current_data[10];
static guiTextLabel_t textLabel_power;          // Measured power
static char label_power_data[10];
static guiTextLabel_t textLabel_temperature;    // Converter temperature
static char label_temperature_data[10];
static guiTextLabel_t textLabel_channel;        // Feedback channel
static char label_channel_data[10];



//--------- Master panel  ---------//
#define MASTER_PANEL_ELEMENTS_COUNT 4
guiPanel_t     guiMasterPanel;
static void *guiMasterPanelElements[MASTER_PANEL_ELEMENTS_COUNT];



//-------------------------------------------------------//
//  Panel initialization
//
//-------------------------------------------------------//
void guiMasterPanel_Initialize(guiGenericWidget_t *parent)
{
    // Initialize form
    guiPanel_Initialize(&guiMasterPanel, parent);
    guiMasterPanel.processEvent = guiMasterPanel_ProcessEvents;     // redefine standard panel message processing funtion
    guiMasterPanel.widgets.count = MASTER_PANEL_ELEMENTS_COUNT;
    guiMasterPanel.widgets.elements = guiMasterPanelElements;
    guiMasterPanel.widgets.elements[0] = &textLabel_voltage;
    guiMasterPanel.widgets.elements[1] = &textLabel_current;
    guiMasterPanel.widgets.elements[2] = &textLabel_power;
    guiMasterPanel.widgets.elements[3] = &textLabel_temperature;
    guiMasterPanel.x = 0;
    guiMasterPanel.y = 0;
    guiMasterPanel.width = 96 * 2;
    guiMasterPanel.height = 68;
    guiMasterPanel.showFocus = 0;

    // Initialize text label for measured voltage display
    guiTextLabel_Initialize(&textLabel_voltage, (guiGenericWidget_t *)&guiMasterPanel);
    textLabel_voltage.x = 2;
    textLabel_voltage.y = 1;
    textLabel_voltage.width = 94;
    textLabel_voltage.height = 32;
    textLabel_voltage.textAlignment = ALIGN_TOP_LEFT;
    textLabel_voltage.text = label_voltage_data;
    textLabel_voltage.font = &font_h32;

    // Initialize text label for measured current display
    guiTextLabel_Initialize(&textLabel_current, (guiGenericWidget_t *)&guiMasterPanel);
    textLabel_current.x = 96 + 2;
    textLabel_current.y = 1;
    textLabel_current.width = 94;
    textLabel_current.height = 32;
    textLabel_current.textAlignment = ALIGN_TOP_LEFT;
    textLabel_current.text = label_current_data;
    textLabel_current.font = &font_h32;

    // Initialize text label for measured power display
    guiTextLabel_Initialize(&textLabel_power, (guiGenericWidget_t *)&guiMasterPanel);
    textLabel_power.x = 96 + 45;
    textLabel_power.y = 56;
    textLabel_power.width = 50;
    textLabel_power.height = 12;
    textLabel_power.textAlignment = ALIGN_TOP_RIGHT;
    textLabel_power.text = label_power_data;
    textLabel_power.font = &font_h12;

    // Initialize text label for measured power display
    guiTextLabel_Initialize(&textLabel_temperature, (guiGenericWidget_t *)&guiMasterPanel);
    textLabel_temperature.x = 55;
    textLabel_temperature.y = 56;
    textLabel_temperature.width = 40;
    textLabel_temperature.height = 12;
    textLabel_temperature.textAlignment = ALIGN_TOP_LEFT;
    textLabel_temperature.text = label_temperature_data;
    textLabel_temperature.font = &font_h12;


#if 0
    textLabel_voltage.hasFrame = 1;
    textLabel_voltage.showFocus = 1;
    textLabel_current.hasFrame = 1;
    textLabel_current.showFocus = 1;
    textLabel_power.hasFrame = 1;
    textLabel_power.showFocus = 1;
    textLabel_temperature.hasFrame = 1;
    textLabel_temperature.showFocus = 1;

#endif
}




static uint8_t guiMasterPanel_ProcessEvents(struct guiGenericWidget_t *widget, guiEvent_t event)
{
    uint8_t processResult = GUI_EVENT_ACCEPTED;
    switch (event.type)
    {
        case GUI_EVENT_DRAW:
            guiGraph_DrawPanel(&guiMasterPanel);

            if (guiMasterPanel.redrawForced)
            {
                // Draw static elements
                LCD_SetPixelOutputMode(PIXEL_MODE_REWRITE);
                LCD_SetLineStyle(LINE_STYLE_SOLID);
                LCD_DrawHorLine(0, 54, 96*2, 1);
                LCD_DrawVertLine(48, 55, 13, 1);
                LCD_DrawVertLine(96+42, 55 , 13, 1);
            }
            // Reset flags - redrawForced will be reset by core
            guiMasterPanel.redrawFocus = 0;
            guiMasterPanel.redrawRequired = 0;
            break;
        case GUI_EVENT_SHOW:
            processResult = guiPanel_ProcessEvent(widget, event);
            updateVoltageIndicator();
            updateCurrentIndicator();
            updateTemperatureIndicator();
            updatePowerIndicator();
            break;
        //case GUI_EVENT_KEY:
        default:
            processResult = guiPanel_ProcessEvent(widget, event);
    }

    return processResult;
}





void updateVoltageIndicator(void)
{
    sprintf(textLabel_voltage.text, "86.23v");
    textLabel_voltage.redrawText = 1;
    textLabel_voltage.redrawRequired = 1;
}

void updateCurrentIndicator(void)
{
    sprintf(textLabel_current.text, "51.04a");
    textLabel_current.redrawText = 1;
    textLabel_current.redrawRequired = 1;
}

void updateTemperatureIndicator(void)
{
    sprintf(textLabel_temperature.text, "%2.0f%cC", 25.4f, 0xb0);
    textLabel_temperature.redrawText = 1;
    textLabel_temperature.redrawRequired = 1;
}

void updatePowerIndicator(void)
{
    sprintf(textLabel_power.text, "%2.1fW", 18.3f);
    textLabel_power.redrawText = 1;
    textLabel_power.redrawRequired = 1;
}


