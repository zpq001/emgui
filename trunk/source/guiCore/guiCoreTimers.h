#ifndef __GUI_CORE_TIMERS_H_
#define __GUI_CORE_TIMERS_H_

#include <stdint.h>
#include "guiConfig.h"
#include "guiWidgets.h"

// The tmrType_t type should be defined in configuration file
#ifndef tmrType_t
#define tmrType_t   uint16_t
#endif

typedef void (*tmrHandler)(uint8_t id);

typedef struct {
    tmrType_t top;
    tmrType_t counter;
    uint8_t runOnce : 1;
    uint8_t isEnabled : 1;
    uint8_t notifierType : 1;
    union {
        guiGenericWidget_t *targetWidget;
        tmrHandler handler;
    } notifiers;
} guiTimer_t;

// Timer init arguments
#define TMR_RUN_CONSTANTLY  0
#define TMR_RUN_ONCE        1
#define TMR_TARGET_VOID     0
#define TMR_HANDLER_VOID    0

// Timer start arguments
#define TMR_DO_RESET        1
#define TMR_NO_RESET        0


void guiCore_DisableAllTimers(void);
void guiCore_InitTimer(uint8_t timerID, tmrType_t period, uint8_t runOnce, guiGenericWidget_t *target);
void guiCore_InitTimerH(uint8_t timerID, tmrType_t period, uint8_t runOnce, tmrHandler handler);
void guiCore_StartTimer(uint8_t timerID, uint8_t doReset);
void guiCore_StopTimer(uint8_t timerID, uint8_t doReset);
void guiCore_ProcessAllTimers(void);

#endif
