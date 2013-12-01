#include <stdio.h>

#include "menu_top.h"

#include "guiEvents.h"
#include "guiCore.h"
#include "guiTextLabel.h"
#include "guiGraphCommon.h"
#include "guiWidgetCommon.h"
#include "guiFonts.h"

#include "guiConfig.h"

// Forms
#include "guiMainForm.h"
#include "guiSetupForm.h"

// Callback functions
cbFuncPtr addLogCallback;
cbLcdUpdatePtr updateLcdCallback;


// Graphics configuration is set in file guiConfig.h

// Display buffer
uint8_t display_buffer[DISPLAY_BUFFER_SIZE];
uint16_t lcd0_buffer[LCD_BUFFER_SIZE];
uint16_t lcd1_buffer[LCD_BUFFER_SIZE];


guiEventArgButtons_t argButtons;




void guiInitialize(void)
{
    guiMainForm_Initialize();
    guiSetupForm_Initialize();
    guiCore_Init(&guiMainForm);
}



void guiDrawAll(void)
{
     addLogCallback(LOG_FROM_TOP, "Requesting GUI redraw procedure");
   
    // GUI function call
    guiCore_RedrawAll();
}

void guiDrawIsCompleteCallback(void)
{
    int i,j;
    int lcd_buf_index;
    int gui_buf_index;

    addLogCallback(LOG_FROM_BOTTOM, "GUI redraw completed!");

    // Split whole GUI buffer into two separate buffers per LCD
    lcd_buf_index = 0;
    for (j=0; j<9; j++)
    {
        for (i=0; i<LCD_XSIZE; i++)
        {
            gui_buf_index = j * (LCD_XSIZE*2) + i;
            lcd0_buffer[lcd_buf_index] = (uint8_t)display_buffer[gui_buf_index];
            lcd1_buffer[lcd_buf_index] = (uint8_t)display_buffer[gui_buf_index + LCD_XSIZE];
            lcd_buf_index++;
        }
    }
    updateLcdCallback(0,lcd0_buffer);
    updateLcdCallback(1,lcd1_buffer);
}


void guiButtonClicked(uint32_t buttonCode)
{
    guiEvent_t bEvent;
    addLogCallback(LOG_FROM_TOP, "Generated button event");

    bEvent.type = GUI_EVENT_BUTTONS_ENCODER;
    bEvent.args = &argButtons;
    argButtons.buttonCode = buttonCode;
    argButtons.encoderDelta = 0;

    guiCore_ProcessEvent(bEvent);
}

void guiEncoderRotated(int32_t delta)
{
    guiEvent_t bEvent;
    addLogCallback(LOG_FROM_TOP, "Generated encoder event");

    bEvent.type = GUI_EVENT_BUTTONS_ENCODER;
    bEvent.args = &argButtons;
    argButtons.buttonCode = 0;
    argButtons.encoderDelta = delta;

    guiCore_ProcessEvent(bEvent);
}


void guiLogEvent(char *string)
{
    addLogCallback(LOG_FROM_BOTTOM, string);
}



void registerLogCallback(cbFuncPtr fptr)
{
    addLogCallback = fptr;
}

void registerLcdUpdateCallback(cbLcdUpdatePtr fptr)
{
    updateLcdCallback = fptr;
}

