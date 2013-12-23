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
#include "guiSpinBox.h"

// Other forms and panels - in order to switch between them
#include "guiMasterPanel.h"
#include "guiMasterPanel.h"

#include "guiTop.h"



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
static guiTextLabel_t textLabel_currLimit;      // Current limit
static char label_currLimit_data[10];
static guiSpinBox_t spinBox_voltage;            // Voltage setting



//--------- Master panel  ---------//
#define MASTER_PANEL_ELEMENTS_COUNT 7
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
    guiMasterPanel.widgets.elements[4] = &textLabel_channel;
    guiMasterPanel.widgets.elements[5] = &textLabel_currLimit;      // focusable!
    guiMasterPanel.widgets.elements[6] = &spinBox_voltage;          // focusable
    guiMasterPanel.x = 0;
    guiMasterPanel.y = 0;
    guiMasterPanel.width = 96 * 2;
    guiMasterPanel.height = 68;
    guiMasterPanel.showFocus = 0;

    // Initialize text label for measured voltage display
    guiTextLabel_Initialize(&textLabel_voltage, (guiGenericWidget_t *)&guiMasterPanel);
    textLabel_voltage.x = 1;
    textLabel_voltage.y = 1;
    textLabel_voltage.width = 94;
    textLabel_voltage.height = 32;
    textLabel_voltage.textAlignment = ALIGN_TOP_RIGHT;
    textLabel_voltage.text = label_voltage_data;
    textLabel_voltage.font = &font_h32;

    // Initialize text label for measured current display
    guiTextLabel_Initialize(&textLabel_current, (guiGenericWidget_t *)&guiMasterPanel);
    textLabel_current.x = 96 + 1;
    textLabel_current.y = 1;
    textLabel_current.width = 94;
    textLabel_current.height = 32;
    textLabel_current.textAlignment = ALIGN_TOP_RIGHT;
    textLabel_current.text = label_current_data;
    textLabel_current.font = &font_h32;

    // Initialize text label for measured power display
    guiTextLabel_Initialize(&textLabel_power, (guiGenericWidget_t *)&guiMasterPanel);
    textLabel_power.x = 96 + 45;
    textLabel_power.y = 57;
    textLabel_power.width = 50;
    textLabel_power.height = 11;
    textLabel_power.textAlignment = ALIGN_TOP_RIGHT;
    textLabel_power.text = label_power_data;
    textLabel_power.font = &font_h11;

    // Initialize text label for temperature display
    guiTextLabel_Initialize(&textLabel_temperature, (guiGenericWidget_t *)&guiMasterPanel);
    textLabel_temperature.x = 55;
    textLabel_temperature.y = 57;
    textLabel_temperature.width = 40;
    textLabel_temperature.height = 11;
    textLabel_temperature.textAlignment = ALIGN_TOP_LEFT;
    textLabel_temperature.text = label_temperature_data;
    textLabel_temperature.font = &font_h11;

    // Initialize text label for feedback channel display
    guiTextLabel_Initialize(&textLabel_channel, (guiGenericWidget_t *)&guiMasterPanel);
    textLabel_channel.x = 1;
    textLabel_channel.y = 57;
    textLabel_channel.width = 45;
    textLabel_channel.height = 11;
    textLabel_channel.textAlignment = ALIGN_TOP_LEFT;
    textLabel_channel.text = label_channel_data;
    textLabel_channel.font = &font_h11;

    // Initialize text label for current limit display and control
    guiTextLabel_Initialize(&textLabel_currLimit, (guiGenericWidget_t *)&guiMasterPanel);
    textLabel_currLimit.x = 96+1;
    textLabel_currLimit.y = 57;
    textLabel_currLimit.width = 40;
    textLabel_currLimit.height = 11;
    textLabel_currLimit.textAlignment = ALIGN_TOP_LEFT;
    textLabel_currLimit.text = label_currLimit_data;
    textLabel_currLimit.font = &font_h11;
    textLabel_currLimit.acceptFocusByTab = 1;
    textLabel_currLimit.tabIndex = 10;
    textLabel_currLimit.showFocus = 1;
    // TODO - add handlers

    guiSpinBox_Initialize(&spinBox_voltage, (guiGenericWidget_t *)&guiMasterPanel);
    spinBox_voltage.x = 20;
    spinBox_voltage.y = 34;
    spinBox_voltage.width = 50;
    spinBox_voltage.height = 20;
    spinBox_voltage.tabIndex = 11;
    spinBox_voltage.font = &font_h11;
    spinBox_voltage.dotPosition = 2;
    spinBox_voltage.activeDigit = 2;
    spinBox_voltage.minDigitsToDisplay = 3;
    spinBox_voltage.restoreValueOnEscape = 1;



#if 1
    textLabel_voltage.hasFrame = 1;
    textLabel_voltage.showFocus = 1;
    textLabel_current.hasFrame = 1;
    textLabel_current.showFocus = 1;
    textLabel_power.hasFrame = 1;
    textLabel_power.showFocus = 1;
    textLabel_temperature.hasFrame = 1;
    textLabel_temperature.showFocus = 1;
    textLabel_channel.hasFrame = 1;
    textLabel_channel.showFocus = 1;
    textLabel_currLimit.hasFrame = 1;
    textLabel_currLimit.showFocus = 1;
    spinBox_voltage.hasFrame = 1;
    spinBox_voltage.showFocus = 1;
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
                LCD_DrawHorLine(0, 55, 96*2, 1);
                LCD_DrawVertLine(48, 56, 13, 1);
                LCD_DrawVertLine(96+42, 56 , 13, 1);
            }
            // Reset flags - redrawForced will be reset by core
            guiMasterPanel.redrawFocus = 0;
            guiMasterPanel.redrawRequired = 0;
            break;
        //case GUI_EVENT_KEY:
        default:
            processResult = guiPanel_ProcessEvent(widget, event);
    }

    return processResult;
}





void setVoltageIndicator(uint16_t value)
{
    sprintf(textLabel_voltage.text, "%2.2fv", (float)value/1000);
    textLabel_voltage.redrawText = 1;
    textLabel_voltage.redrawRequired = 1;
}

void setVoltageSetting(uint16_t value)
{
    // FIXME
    guiSpinBox_SetValue(&spinBox_voltage, value/10);

}

void setCurrentIndicator(uint16_t value)
{
    sprintf(textLabel_current.text, "%2.2fa", (float)value/1000);
    textLabel_current.redrawText = 1;
    textLabel_current.redrawRequired = 1;
}

void setPowerIndicator(uint32_t value)
{
    sprintf(textLabel_power.text, "%3.2fW", (float)value/1000 );
    textLabel_power.redrawText = 1;
    textLabel_power.redrawRequired = 1;
}

void setTemperatureIndicator(int16_t value)
{
    sprintf(textLabel_temperature.text, "%2d%cC", value, 0xb0);
    textLabel_temperature.redrawText = 1;
    textLabel_temperature.redrawRequired = 1;
}

void setFeedbackChannelIndicator(uint8_t channel)
{
    if (channel == CHANNEL_5V)
        sprintf(textLabel_channel.text, "Ch.5V");
    else
        sprintf(textLabel_channel.text, "Ch.12V");
}

void setCurrentLimitIndicator(uint8_t current_limit)
{
    if (current_limit == CURRENT_LIM_LOW)
        sprintf(textLabel_currLimit.text, "20A");
    else
        sprintf(textLabel_currLimit.text, "40A");
}



