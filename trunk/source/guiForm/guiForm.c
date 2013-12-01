
#include "guiConfig.h"
#include "guiForm.h"
#include "guiWidgetCommon.h"
#include "guiGraphUtils.h"
#include "guiCore.h"


void guiForm_Initialize(guiForm_t *pForm)
{
    pForm->type = WT_FORM;
    pForm->properties = 0;
    pForm->redrawFlags = 0;
    pForm->state = 0;
    pForm->tabIndex = 0;
    pForm->widgets.count = 0;
    pForm->widgets.elements = 0;
    pForm->widgets.pSelected = 0;
    pForm->processEvent = 0;
    pForm->handlers.count = 0;
    pForm->handlers.elements = 0;
    pForm->tag = 0;
}



void guiForm_Draw(guiForm_t *pForm)
{
    // redrawFlags are reset by widget itself after calling handler.
    guiEvent_t drawEvent;
    uint8_t i;
    guiGenericWidget_t * pWidget;

    for (i=0; i<pForm->widgets.count; i++)
    {
        pWidget = (guiGenericWidget_t *)pForm->widgets.elements[i];
        pWidget->processEvent(pWidget, guiEvent_UPDATE);
    }

    if (pForm->redrawFlags & WF_REDRAW)
    {
        guiGraph_FillBuffer(0x00);              // Erase screen
        drawEvent = guiEvent_DRAW_ALL;          // Redraw all childs
    }
    else
    {
        drawEvent = guiEvent_DRAW;              // Redraw only childs that require drawing
    }

    for (i=0; i<pForm->widgets.count; i++)
    {
        pWidget = (guiGenericWidget_t *)pForm->widgets.elements[i];
        pWidget->processEvent(pWidget, drawEvent);
    }

}







