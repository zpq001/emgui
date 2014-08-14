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

//#include "guiMainForm.h"
//#include "guiMasterPanel.h"
//#include "guiSetupPanel.h"



// Callback functions - should not be used until initialized
static cbLogPtr addLogCallback = 0;
static cbLcdUpdatePtr updateLcdCallback = 0;


//-----------------------------------------------------------------//
// Callbacks top->GUI
// This functions are called by top level once during initialization
// to setup necessary callbacks
//-----------------------------------------------------------------//

// Setup callback for logging events
void registerLogCallback(cbLogPtr fptr)
{
    addLogCallback = fptr;
}

// Setup callback for updating display in simulator
void registerLcdUpdateCallback(cbLcdUpdatePtr fptr)
{
    updateLcdCallback = fptr;
}


//-----------------------------------------------------------------//
// Callbacks GUI->top
// This functions are called by guiTop or underlying modules
//-----------------------------------------------------------------//

// Function to log gui events
void guiLogEvent(char *string)
{
    if (addLogCallback)
    {
        addLogCallback(LOG_FROM_BOTTOM, string);
    }
    else
    {
        // Error! Call registerLogCallback() first
    }
}

// Updating simulator display
static void guiDrawIsComplete(void)
{
    if (updateLcdCallback)
    {
        updateLcdCallback(lcdBuffer);
    }
    else
    {
        // Error! Call registerLcdUpdateCallback() first
    }
}




//-----------------------------------------------------------------//
// Control interface for top level
//
//-----------------------------------------------------------------//


// Initialization of GUI
void guiInitialize(void)
{
    addLogCallback(LOG_FROM_TOP, "Initializing");
    //guiMainForm_Initialize();
    //guiCore_Init((guiGenericWidget_t *)&guiMainForm);
    // TODO
}


// Drawing of GUI
void guiDrawAll(void)
{
    addLogCallback(LOG_FROM_TOP, "Redrawing GUI");

    //guiCore_RedrawAll();
    lcdBuffer[0] = 0xF7;

    guiDrawIsComplete();
}


// Button event
void guiButtonEvent(uint16_t buttonCode, uint8_t eventType)
{
    guiCore_ProcessKeyEvent(buttonCode, eventType);
}


// Encoder event
void guiEncoderRotated(int32_t delta)
{
    addLogCallback(LOG_FROM_TOP, "Generated encoder event");
    guiCore_ProcessEncoderEvent((int16_t) delta);
}



