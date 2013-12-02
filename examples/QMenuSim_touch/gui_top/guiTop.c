#include <stdio.h>

#include "guiTop.h"
#include "guiGraphHAL.h"

// Callback functions
cbLogPtr addLogCallback;
cbLcdUpdatePtr updateLcdCallback;




//guiEventArgButtons_t argButtons;



//-----------------------------------//
// Callbacks
void registerLogCallback(cbLogPtr fptr)
{
    addLogCallback = fptr;
}

void registerLcdUpdateCallback(cbLcdUpdatePtr fptr)
{
    updateLcdCallback = fptr;
}

void guiLogEvent(char *string)
{
    addLogCallback(LOG_FROM_BOTTOM, string);
}

void guiDrawIsComplete(void)
{
    updateLcdCallback(guiLcdBuffer);
}
//-----------------------------------//




//-----------------------------------//
// Commands to GUI

void guiInitialize(void)
{
    uint32_t i = 0;
    while(i < (LCD_XSIZE * LCD_YSIZE))
        guiLcdBuffer[i++] = 0x00000000;

    guiDrawIsComplete();

    //guiMainForm_Initialize();
    //guiSetupForm_Initialize();
    //guiCore_Init(&guiMainForm);
}



void guiDrawAll(void)
{
     addLogCallback(LOG_FROM_TOP, "Requesting GUI redraw procedure");
   
    // GUI function call
    //guiCore_RedrawAll();
}



void guiTouchMoved(int x, int y)
{
    guiLcdBuffer[y * LCD_XSIZE + x] = 0x00FF00;
}

void guiTouchPressed(int x, int y)
{
    guiLcdBuffer[y * LCD_XSIZE + x] = 0x0000FF;
    guiDrawIsComplete();
}

void guiTouchReleased(int x, int y)
{
    guiLcdBuffer[y * LCD_XSIZE + x] = 0x00FFFF;
    guiDrawIsComplete();
}


void guiButtonClicked(uint32_t buttonCode)
{
 //  guiEvent_t bEvent;
    addLogCallback(LOG_FROM_TOP, "Generated button event");
 /*
    bEvent.type = GUI_EVENT_BUTTONS_ENCODER;
    bEvent.args = &argButtons;
    argButtons.buttonCode = buttonCode;
    argButtons.encoderDelta = 0;

    guiCore_ProcessEvent(bEvent);
	*/
}

void guiEncoderRotated(int32_t delta)
{

//    guiEvent_t bEvent;
    addLogCallback(LOG_FROM_TOP, "Generated encoder event");
/*
    bEvent.type = GUI_EVENT_BUTTONS_ENCODER;
    bEvent.args = &argButtons;
    argButtons.buttonCode = 0;
    argButtons.encoderDelta = delta;

    guiCore_ProcessEvent(bEvent);
	*/
}

//-----------------------------------//





