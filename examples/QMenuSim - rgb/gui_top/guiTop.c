#include <stdio.h>

#include "guiTop.h"
#include "guiFonts.h"
#include "guiGraphHAL.h"
#include "guiGraphPrimitives.h"
#include "guiGraphWidgets.h"

#include "guiCore.h"
#include "guiEvents.h"
#include "guiWidgets.h"
#include "guiForm.h"
#include "guiTextLabel.h"

#include "guiMainForm.h"


// Callback functions
cbLogPtr addLogCallback;
cbLcdUpdatePtr updateLcdCallback;


uint8_t timeHours;
uint8_t timeMinutes;
uint8_t timeSeconds;


guiEventArgButtons_t argButtons;



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
    addLogCallback(LOG_FROM_BOTTOM, "GUI redraw completed!");
    updateLcdCallback(guiLcdBuffer);
}
//-----------------------------------//




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
/*    rect_t rect1;

    fillColor = CL_LIGHT_GREY;
    rect1.x1 = 0;
    rect1.x2 = LCD_XSIZE-1;
    rect1.y1 = 0;
    rect1.y2 = LCD_YSIZE-1;
    LCD_FillRect(&rect1);

    fillColor = CL_GREEN;
    rect1.x1 = 0;
    rect1.x2 = 50;
    rect1.y1 = 0;
    rect1.y2 = 100;
    LCD_FillRect(&rect1);


    guiGraph_DrawButton(100,100);

    LCD_SetFont(&font_h10);

    fontForeColor = CL_RED;
    fontBackColor = CL_YELLOW;
    fontOutputMode = FONT_OUTPUT_SOLID;
    LCD_PrintString("Hello world!",20,20);


    fontForeColor = CL_BLUE;
    fontOutputMode = FONT_OUTPUT_TRANSPARENT;
    LCD_PrintString("Привет мiр!",20,50);

    guiDrawIsComplete();
*/

    timeHours = 0;
    timeMinutes = 0;
    timeSeconds = 0;


    guiMainForm_Initialize();

    guiCore_Init((guiGenericWidget_t *)&guiMainForm);

}



void guiDrawAll(void)
{
     addLogCallback(LOG_FROM_TOP, "Requesting GUI redraw procedure");
   
     guiCore_RedrawAll();
     // Update display(s)
     guiDrawIsComplete();
}



void guiTouchMoved(int x, int y)
{
    LCD_PutPixel(x,y,CL_GREEN);
}

void guiTouchPressed(int x, int y)
{
    LCD_PutPixel(x,y,CL_RED);
    guiDrawIsComplete();
}

void guiTouchReleased(int x, int y)
{
    LCD_PutPixel(x,y,CL_YELLOW);
    guiDrawIsComplete();
}


void guiButtonClicked(uint32_t buttonCode)
{

    guiEvent_t bEvent;
    addLogCallback(LOG_FROM_TOP, "Generated button event");

    bEvent.type = GUI_EVENT_BUTTONS_ENCODER;
    bEvent.args = &argButtons;
    argButtons.buttonCode = buttonCode;
    argButtons.encoderDelta = 0;

    guiCore_PostEventToFocused(bEvent);

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





