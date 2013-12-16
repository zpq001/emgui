/**********************************************************
    Module guiForm




**********************************************************/

#include <stdint.h>
#include "guiFonts.h"
#include "guiGraphPrimitives.h"
#include "guiEvents.h"
#include "guiWidgets.h"
#include "guiForm.h"





static uint8_t guiForm_ProcessEvent(guiGenericWidget_t *pWidget, guiEvent_t event)
{
    return 0;
}


void guiForm_Initialize(guiForm_t *form)
{
    form->parent = 0;
    form->acceptFocus = 1;
    form->acceptFocusByTab = 0;
    form->isFocused = 0;
    form->isVisible = 0;
    form->redrawForced = 0;
    form->redrawRequired = 0;
    form->isContainer = 1;
    form->tag = 0;
    form->tabIndex = 0;
    form->processEvent = guiForm_ProcessEvent;
    form->handlers.count = 0;
    form->acceptTouch = 1;
    form->focusFallsThrough = 0;
    form->keepTouch = 0;

    form->widgets.count = 0;
    form->widgets.focusedIndex = 0;
    form->widgets.traverseIndex = 0;
    form->redrawFlags = 0;
    form->hasFrame = 0;
}



