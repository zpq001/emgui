#include <stdio.h>

#include "guiTop.h"
#include "guiFonts.h"
#include "guiGraphHAL.h"
#include "guiGraphPrimitives.h"
#include "guiGraphWidgets.h"

#include "guiCore.h"
#include "guiEvents.h"
#include "guiWidgets.h"
#include "guiTextLabel.h"

#include "guiMainForm.h"
#include "guiMasterPanel.h"

// Callback functions
cbLogPtr addLogCallback;
cbLcdUpdatePtr updateLcdCallback;

// Temporary display buffers, used for splitting GUI buffer into two separate LCD's
uint8_t lcd0_buffer[DISPLAY_BUFFER_SIZE];
uint8_t lcd1_buffer[DISPLAY_BUFFER_SIZE];


uint8_t timeHours;
uint8_t timeMinutes;
uint8_t timeSeconds;


//=================================================================//
//=================================================================//
//                      Hardware emulation interface               //
//=================================================================//
uint16_t voltage_adc;		// [mV]
uint16_t set_voltage;
uint16_t current_adc;		// [mA]
uint16_t set_current;
uint32_t power_adc;			// [mW]
int16_t converter_temp_celsius;

uint8_t channel;            // feedback channel
uint8_t current_limit;      // converter max current (20A/40A)
//=================================================================//


//-----------------------------------//
// Callbacks top->GUI
void registerLogCallback(cbLogPtr fptr)
{
    addLogCallback = fptr;
}

void registerLcdUpdateCallback(cbLcdUpdatePtr fptr)
{
    updateLcdCallback = fptr;
}

//-----------------------------------//
// Callbacks GUI->top
void guiLogEvent(char *string)
{
    addLogCallback(LOG_FROM_BOTTOM, string);
}




//-----------------------------------//
// Splitting GUI buffer into two separate LCD's and
// updating displays
//-----------------------------------//
static void guiDrawIsComplete(void)
{
    int i,j;
    int lcd_buf_index;
    int gui_buf_index;
    int num_pages = LCD_YSIZE / 8;
    if (LCD_YSIZE % 8) num_pages++;

    addLogCallback(LOG_FROM_BOTTOM, "GUI redraw completed!");

    // Split whole GUI buffer into two separate buffers per LCD
    lcd_buf_index = 0;
    for (j=0; j<num_pages; j++)
    {
        for (i=0; i<DISPLAY_XSIZE; i++)
        {
            gui_buf_index = j * (DISPLAY_XSIZE*2) + i;
            lcd0_buffer[lcd_buf_index] = (uint8_t)lcdBuffer[gui_buf_index];
            lcd1_buffer[lcd_buf_index] = (uint8_t)lcdBuffer[gui_buf_index + DISPLAY_XSIZE];
            lcd_buf_index++;
        }
    }

    updateLcdCallback(0,lcd0_buffer);
    updateLcdCallback(1,lcd1_buffer);
}



//-----------------------------------//
// Commands to GUI


void guiUpdateTime(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
    timeHours = hours;
    timeMinutes = minutes;
    timeSeconds = seconds;
}


void guiInitialize(void)
{
    timeHours = 0;
    timeMinutes = 0;
    timeSeconds = 0;


    set_voltage = 10000;        // mV
    voltage_adc = set_voltage;
    set_current = 2000;         // mA
    current_adc =  set_current;
    power_adc =       0;        // mW
    converter_temp_celsius = 25;        // Celsius
    current_limit = CURRENT_LIM_LOW;
    channel = CHANNEL_12V;

    guiMainForm_Initialize();
    guiCore_Init((guiGenericWidget_t *)&guiMainForm);


    guiUpdateVoltageSetting();
    guiUpdateCurrentSetting();

    guiUpdateVoltageIndicator();
    guiUpdateCurrentIndicator();
    guiUpdatePowerIndicator();
    guiUpdateTemperatureIndicator();
    guiUpdateChannelSetting();
    guiUpdateCurrentLimit();
}



void guiDrawAll(void)
{
    //addLogCallback(LOG_FROM_TOP, "Redrawing GUI");
    guiCore_RedrawAll();
    // Update display(s)
    guiDrawIsComplete();
}


// No touch support


void guiButtonPressed(uint16_t buttonCode)
{
    guiCore_ProcessKeyEvent(buttonCode, GUI_KEY_EVENT_DOWN);
}


void guiButtonReleased(uint16_t buttonCode)
{
    guiCore_ProcessKeyEvent(buttonCode, GUI_KEY_EVENT_UP);
}


void guiEncoderRotated(int32_t delta)
{
    addLogCallback(LOG_FROM_TOP, "Generated encoder event");
    guiCore_ProcessEncoderEvent((int16_t) delta);
}





//=================================================================//
//=================================================================//
//                      Hardware emulation interface               //
//=================================================================//


//-----------------------------------//
// Voltage

// Read ADC voltage and update LCD indicator
void guiUpdateVoltageIndicator(void)
{
    guiLogEvent("Reading voltage ADC");
    setVoltageIndicator(voltage_adc);
}

// Read voltage setting and update LCD indicator
void guiUpdateVoltageSetting(void)
{
    guiLogEvent("Reading voltage setting");
    setVoltageSetting(set_voltage);
}

// Apply voltage setting from GUI
void applyGuiVoltageSetting(uint16_t new_set_voltage)
{
    guiLogEvent("Writing voltage setting");
    set_voltage = new_set_voltage;
    voltage_adc = set_voltage;

    //------ simulation of actual conveter work ------//
    guiUpdateVoltageIndicator();
}


//-----------------------------------//
// Current

// Read ADC current and update LCD indicator
void guiUpdateCurrentIndicator(void)
{
    guiLogEvent("Reading current ADC");
    setCurrentIndicator(current_adc);
}

// Read current setting and update LCD indicator
void guiUpdateCurrentSetting(void)
{
    guiLogEvent("Reading current setting");
    setCurrentSetting(set_current);
}

// Apply current setting from GUI
void applyGuiCurrentSetting(uint16_t new_set_current)
{
    guiLogEvent("Writing current setting");
    set_current = new_set_current;
    current_adc = set_current;

    //------ simulation of actual conveter work ------//
    guiUpdateCurrentIndicator();
}


//-----------------------------------//
// Feedback channel

// Read selected feedback channel and update LCD
void guiUpdateChannelSetting(void)
{
    guiLogEvent("Reading selected feedback channel");
    setFeedbackChannelIndicator(channel);
}

// Apply new selected feedback channel
/*void applyGuiChannelSetting(uint8_t new_channel)
{
    guiLogEvent("Writing selected feedback channel");
    channel = new_channel;

    // simulation of actual conveter work
    guiUpdateChannelSetting();
}*/


//-----------------------------------//
// Current limit

// Read current limit and update LCD
void guiUpdateCurrentLimit(void)
{
    guiLogEvent("Reading current limit");
    setCurrentLimitIndicator(current_limit);
}

// Apply new selected feedback channel
void applyGuiCurrentLimit(uint8_t new_current_limit)
{
    guiLogEvent("Writing current limit");
    current_limit = new_current_limit;

    //------ simulation of actual conveter work ------//
    guiUpdateCurrentLimit();
}


//-----------------------------------//
// Power

// Read computed power and update LCD indicator
void guiUpdatePowerIndicator(void)
{
    guiLogEvent("Reading power ADC");
    setPowerIndicator(power_adc);
}


//-----------------------------------//
// Temperature

// Read normalized temperature and update LCD indicator
void guiUpdateTemperatureIndicator(void)
{
    guiLogEvent("Reading temperature ADC");
    setTemperatureIndicator(converter_temp_celsius);
}

//=================================================================//

