/**********************************************************
    Module guiCoreTimers

    GUI core timers functions

**********************************************************/

#include <stdint.h>
#include "guiConfig.h"
#include "guiEvents.h"
#include "guiWidgets.h"
#include "guiCore.h"
#include "guiCoreTimers.h"

// Timer notifier type
#define TMR_NOTIFY_WIDGET   0
#define TMR_NOTIFY_HANDLER  1


#ifdef emGUI_USE_TIMERS

// Total count of timers should be defined in guiConfig.h
static guiTimer_t guiTimers[emGUI_TIMERS_COUNT];


//-------------------------------------------------------//
//  Disables all timers
//  May be used for initialization
//-------------------------------------------------------//
void guiCore_DisableAllTimers(void)
{
    uint8_t i;
    for (i=0; i<emGUI_TIMERS_COUNT; i++)
    {
        guiTimers[i].isEnabled = 0;
    }
}


//-------------------------------------------------------//
//  Initializes GUI core timer
//  Timer is identified by timerID which is simply index
//  of an element in guiTimers[]
//  When timer expires, target widget will be sent GUI_EVENT_TIMER
//-------------------------------------------------------//
void guiCore_InitTimer(uint8_t timerID, tmrType_t period, uint8_t runOnce, guiGenericWidget_t *target)
{
    if (timerID >= emGUI_TIMERS_COUNT)
        return;
    guiTimers[timerID].top = period;
    guiTimers[timerID].counter = 0;
    guiTimers[timerID].runOnce = (runOnce) ? 1 : 0;
    guiTimers[timerID].isEnabled = 0;
    guiTimers[timerID].notifierType = TMR_NOTIFY_WIDGET;
    guiTimers[timerID].notifiers.targetWidget = target;
}


//-------------------------------------------------------//
//  Alias for initializing GUI core timer
//  When timer expires, handler function will be called
//-------------------------------------------------------//
void guiCore_InitTimerH(uint8_t timerID, tmrType_t period, uint8_t runOnce, tmrHandler handler)
{
    if (timerID >= emGUI_TIMERS_COUNT)
        return;
    guiTimers[timerID].top = period;
    guiTimers[timerID].counter = 0;
    guiTimers[timerID].runOnce = (runOnce) ? 1 : 0;
    guiTimers[timerID].isEnabled = 0;
    guiTimers[timerID].notifierType = TMR_NOTIFY_HANDLER;
    guiTimers[timerID].notifiers.handler = handler;
}


//-------------------------------------------------------//
//  Starts GUI core timer
//  Timer is identified by timerID which is simply index
//  of element in guiTimers[]
//
//  If doReset is non-zero, timer will be set to 0
//-------------------------------------------------------//
void guiCore_StartTimer(uint8_t timerID, uint8_t doReset)
{
    if (timerID >= emGUI_TIMERS_COUNT)
        return;
    if (doReset)
        guiTimers[timerID].counter = 0;
    guiTimers[timerID].isEnabled = 1;
}


//-------------------------------------------------------//
//  Stops GUI core timer
//  Timer is identified by timerID which is simply index
//  of element in guiTimers[]
//
//  If doReset is non-zero, timer will be set to 0
//-------------------------------------------------------//
void guiCore_StopTimer(uint8_t timerID, uint8_t doReset)
{
    if (timerID >= emGUI_TIMERS_COUNT)
        return;
    if (doReset)
        guiTimers[timerID].counter = 0;
    guiTimers[timerID].isEnabled = 0;
}


//-------------------------------------------------------//
//  Processes GUI core timer
//  Timer is identified by timerID which is simply index
//  of element in guiTimers[]
//
//  Timer's counter is incremented. If counter has reached
//  top, in is reset and timer event is sent to the target widget
//  Additionaly, handler is called (if specified)
//-------------------------------------------------------//
static void guiCoreTimer_Process(uint8_t timerID)
{
    guiEvent_t event = {GUI_EVENT_TIMER};
    if (timerID >= emGUI_TIMERS_COUNT)
        return;
    if (guiTimers[timerID].isEnabled)
    {
        guiTimers[timerID].counter++;
        if (guiTimers[timerID].counter >= guiTimers[timerID].top)
        {
            guiTimers[timerID].counter = 0;
            if (guiTimers[timerID].runOnce)
                guiTimers[timerID].isEnabled = 0;
            if (guiTimers[timerID].notifierType == TMR_NOTIFY_WIDGET)
            {
                if (guiTimers[timerID].notifiers.targetWidget != 0)
                {
                    event.spec = timerID;
                    guiCore_AddMessageToQueue(guiTimers[timerID].notifiers.targetWidget, &event);
                }
            }
            else
            {
                if (guiTimers[timerID].notifiers.handler != 0)
                    guiTimers[timerID].notifiers.handler(timerID);
            }
        }
    }
}


//-------------------------------------------------------//
//  Top function for processing all timers
//
//-------------------------------------------------------//
void guiCore_ProcessAllTimers(void)
{
    uint8_t i;
    for (i=0; i<emGUI_TIMERS_COUNT; i++)
    {
        guiCoreTimer_Process(i);
    }
    guiCore_ProcessMessageQueue();
}

#endif  // emGUI_USE_TIMERS
