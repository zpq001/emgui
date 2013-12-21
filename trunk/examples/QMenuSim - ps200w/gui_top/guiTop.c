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

// Callback functions
cbLogPtr addLogCallback;
cbLcdUpdatePtr updateLcdCallback;

// Temporary display buffers, used for splitting GUI buffer into two separate LCD's
uint8_t lcd0_buffer[DISPLAY_BUFFER_SIZE];
uint8_t lcd1_buffer[DISPLAY_BUFFER_SIZE];


uint8_t timeHours;
uint8_t timeMinutes;
uint8_t timeSeconds;






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

    guiMainForm_Initialize();

    guiCore_Init((guiGenericWidget_t *)&guiMainForm);
}



void guiDrawAll(void)
{
     addLogCallback(LOG_FROM_TOP, "Redrawing GUI");
   
     // GUI function call
     //guiCore_RedrawAll();

/*
     LCD_SetPixelOutputMode(PIXEL_MODE_REWRITE);
     LCD_FillRect(50,0,69,128,FILL_WITH_BLACK);

     LCD_currentFont = &font_h12;

     LCD_PrintString("rewrite, normal", 10, 5, IMAGE_MODE_NORMAL);
     LCD_PrintString("rewrite, inverse", 10, 20, IMAGE_MODE_INVERSE);

     LCD_SetPixelOutputMode(PIXEL_MODE_AND);
     LCD_PrintString("mode AND, normal", 10, 35, IMAGE_MODE_NORMAL);
     LCD_PrintString("mode AND, inverse", 10, 50, IMAGE_MODE_INVERSE);

     LCD_SetPixelOutputMode(PIXEL_MODE_OR);
     LCD_PrintString("mode OR, normal", 10, 65, IMAGE_MODE_NORMAL);
     LCD_PrintString("mode OR, inverse", 10, 80, IMAGE_MODE_INVERSE);

     LCD_SetPixelOutputMode(PIXEL_MODE_XOR);
     LCD_PrintString("mode XOR, normal", 10, 95, IMAGE_MODE_NORMAL);
     LCD_PrintString("mode XOR, inverse", 10, 110, IMAGE_MODE_INVERSE);
*/
/*
     LCD_SetPixelOutputMode(PIXEL_MODE_REWRITE);
     LCD_lineStyle = LCD_LINE_DOTTED;
     LCD_DrawHorLine(20,50,105,1);
     LCD_DrawVertLine(10,50,60,1);

     LCD_lineStyle = LCD_LINE_DASHED;
     LCD_DrawHorLine(20,52,105,1);
     LCD_DrawVertLine(12,50,60,1);

     LCD_lineStyle = LCD_LINE_DOTTED;
     LCD_DrawRect(128 + 5, 5, 120, 120, 1);
     LCD_lineStyle = LCD_LINE_DASHED;
     LCD_DrawRect(128 + 10, 10, 110, 110, 1);
*/
/*
    guiTextLabel_Initialize(&label1,0);
    label1.text = "12345";
    label1.x = 50;
    label1.y = 50;
    label1.width = 22;
    label1.height = 22;
    //label1.alignment = ALIGN_TOP_LEFT;
    //label1.alignment = ALIGN_TOP_RIGHT;
    //label1.alignment = ALIGN_TOP;
    //label1.alignment = ALIGN_BOTTOM_LEFT;
    //label1.alignment = ALIGN_BOTTOM_RIGHT;
    //label1.alignment = ALIGN_BOTTOM;
    label1.alignment = ALIGN_CENTER;

    guiGraph_DrawTextLabel(&label1);
*/

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




