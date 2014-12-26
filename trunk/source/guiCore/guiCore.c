/**********************************************************
    Module guiCore

Widget's event processing function calls:

Direct:
    guiCore_ProcessMessageQueue
    guiCore_AcceptVisibleStateByTag
    guiCore_BroadcastEvent
    guiCore_RedrawAll
    guiCore_UpdateAll (using guiCore_BroadcastEvent)
    guiCore_AcceptFocusedStatesedState

Through message queue:
    guiCore_PostEventToFocused
    guiCore_TimerProcess
    guiCore_Init
    guiCore_ProcessTouchEvent
    guiCore_ProcessKeyEvent
    guiCore_ProcessEncoderEvent
    guiCore_ProcessTimers (using guiCore_TimerProcess)
    guiCore_RequestFocusChange
    guiCore_SetFocusOnNextWidget (using guiCore_RequestFocusChange)


**********************************************************/

#include <stdint.h>
#include "guiConfig.h"
#include "guiGraphWidgets.h"
#include "guiEvents.h"
#include "guiWidgets.h"
#include "guiCore.h"
#include "guiCoreMemory.h"
#include "guiCoreTimers.h"


// Frequently used events - saves stack a bit
const guiEvent_t guiEvent_HIDE = {GUI_EVENT_HIDE};
const guiEvent_t guiEvent_SHOW = {GUI_EVENT_SHOW};
const guiEvent_t guiEvent_UNFOCUS = {GUI_EVENT_UNFOCUS};
const guiEvent_t guiEvent_FOCUS = {GUI_EVENT_FOCUS};


static guiMsgQueue_t guiMsgQueue;
static guiGenericWidget_t *rootWidget;         // Root widget must be present
static guiGenericWidget_t *focusedWidget;      // Focused widget gets events from keys/encoder/touch





//===================================================================//
//===================================================================//
//                                                                   //
//                 GUI core message queue functions                  //
//                                                                   //
//===================================================================//


//-------------------------------------------------------//
//  Adds a message to GUI core message queue
//
//  Returns 0 if there is no space left
//  Returns non-zero if message has been put
//-------------------------------------------------------//
uint8_t guiCore_AddMessageToQueue(const guiGenericWidget_t *target, const guiEvent_t *event)
{
    if (guiMsgQueue.count < emGUI_CORE_QUEUE_SIZE)
    {
        guiMsgQueue.queue[guiMsgQueue.tail].event = *event;
        guiMsgQueue.queue[guiMsgQueue.tail].target = (guiGenericWidget_t *)target;
        guiMsgQueue.count++;
        guiMsgQueue.tail++;
        if (guiMsgQueue.tail == emGUI_CORE_QUEUE_SIZE)
            guiMsgQueue.tail = 0;
        return 1;
     }
    return 0;
}


//-------------------------------------------------------//
//  Reads a message from GUI core message queue
//
//  Returns 0 if queue is empty
//  Returns non-zero if message has been read
//-------------------------------------------------------//
uint8_t guiCore_GetMessageFromQueue(guiGenericWidget_t **target, guiEvent_t *event)
{
    if (guiMsgQueue.count > 0)
    {
        *target = guiMsgQueue.queue[guiMsgQueue.head].target;
        *event = guiMsgQueue.queue[guiMsgQueue.head].event;
        guiMsgQueue.count--;
        guiMsgQueue.head++;
        if (guiMsgQueue.head == emGUI_CORE_QUEUE_SIZE)
            guiMsgQueue.head = 0;
        return 1;
    }
    return 0;
}


//-------------------------------------------------------//
//  GUI core function for processing message queue
//
// Generally, if message target widget cannot process
// event, message is sent to it's parent and so on
// until it is accepted or root widget is sent the message
// If root cannot process this message, it is lost.
//-------------------------------------------------------//
void guiCore_ProcessMessageQueue(void)
{
    guiGenericWidget_t *target;
    guiEvent_t targetEvent;
    uint8_t processResult;

    while(guiCore_GetMessageFromQueue(&target,&targetEvent))
    {
        while(1)
        {
            if (target == 0)
                break;
            processResult = target->processEvent(target, targetEvent);
            if (processResult == GUI_EVENT_ACCEPTED)
                break;
            // Focused widget cannot process event - pass event to parent
            if (target->parent != 0)
            {
                target = target->parent;
            }
            else
            {
                // No widget can process this event - skip it.
                break;
            }
        }
    }
}


//-------------------------------------------------------//
//  Adds message for focused widget to message queue
//
//-------------------------------------------------------//
void guiCore_PostEventToFocused(guiEvent_t event)                   // CHECKME - rename
{
    if (focusedWidget == 0)
        return;                 // Should not normally happen ?
    guiCore_AddMessageToQueue(focusedWidget, &event);
}







//===================================================================//
//===================================================================//
//                                                                   //
//                      Top GUI core functions                       //
//                                                                   //
//===================================================================//




//-------------------------------------------------------//
//  Top function for GUI core initializing
//  All components must be already initialized
//-------------------------------------------------------//
void guiCore_Init(guiGenericWidget_t *guiRootWidget)
{
    const guiEvent_t event = {GUI_EVENT_INIT};

    // Init queue
    guiMsgQueue.count = 0;
    guiMsgQueue.head = 0;
    guiMsgQueue.tail = 0;

#ifdef emGUI_USE_TIMERS
    guiCore_DisableAllTimers();
#endif

    // Set root and focused widget and send initialize event
    // Root widget must set focus in itself or other widget
    // depending on design. If focus is not set, no keyboard
    // and encoder events will get processed. ~~~
    rootWidget = guiRootWidget;
    focusedWidget = 0;
    guiCore_AddMessageToQueue(rootWidget, &event);
    guiCore_ProcessMessageQueue();
}


/*
//-------------------------------------------------------//
//  Top function for GUI redrawing
//
//-------------------------------------------------------//
void guiCore_RedrawAll(void)
{
    guiGenericWidget_t *widget;
    guiGenericWidget_t *nextWidget;
    uint8_t index;
    const guiEvent_t drawEvent = {GUI_EVENT_DRAW};
    guiGenericWidget_t *w;
    uint8_t i;
    rect16_t inv_rect;

    // Start widget tree traverse from root widget
    widget = rootWidget;
    guiGraph_SetBaseXY(widget->x, widget->y);

    while(1)
    {
        // Process widget
        if (widget->redrawRequired)
        {
            // The redrawRequired flag is reset by widget after processing DRAW event
            widget->processEvent(widget, drawEvent);
        }
        // Check if widget has children
        if (widget->isContainer)
        {
            if (((guiGenericContainer_t *)widget)->widgets.traverseIndex == 0)
            {
                // The first time visit
                // TODO - set graph clipping
            }

            // If container has unprocessed children
            if ( ((guiGenericContainer_t *)widget)->widgets.traverseIndex <
                 ((guiGenericContainer_t *)widget)->widgets.count )
            {
                // switch to next one if possible
                index = ((guiGenericContainer_t *)widget)->widgets.traverseIndex++;
                nextWidget = ((guiGenericContainer_t *)widget)->widgets.elements[index];
                // check if widget actually exists and is visible
                if ((nextWidget == 0) || (nextWidget->isVisible == 0))
                    continue;
                // Check if widget must be redrawn forcibly
                if (widget->redrawForced)
                {
                    nextWidget->redrawForced = 1;
                    nextWidget->redrawRequired = 1;
                }
                ///////////////////////////
#ifdef emGUI_USE_Z_ORDER_REDRAW
                if ((widget->redrawForced == 0) &&(nextWidget->redrawRequired))
                {
                    // Widget will be redrawn - make overlapping widgets with higher Z index redraw too
                    inv_rect.x1 = nextWidget->x;
                    inv_rect.y1 = nextWidget->y;
                    inv_rect.x2 = nextWidget->x + nextWidget->width - 1;
                    inv_rect.y2 = nextWidget->y + nextWidget->height - 1;
                    for (i = index+1; i < ((guiGenericContainer_t *)widget)->widgets.count; i++)
                    {
                        w = ((guiGenericContainer_t *)widget)->widgets.elements[i];
                        if ((w != 0) && (w->isVisible))
                        {
                            if (guiCore_CheckWidgetOvelap(w, &inv_rect))
                            {
                                w->redrawForced = 1;
                                w->redrawRequired = 1;
                            }
                        }
                    }
                }
#endif
                ///////////////////////////
                if ((nextWidget->redrawRequired) || (nextWidget->isContainer))
                {
                    widget = nextWidget;
                    guiGraph_OffsetBaseXY(widget->x, widget->y);
                }
            }
            else
            {
                // All container child items are processed. Reset counter of processed items and move up.
                ((guiGenericContainer_t *)widget)->widgets.traverseIndex = 0;
                widget->redrawForced = 0;
                if (widget->parent == 0)    // root widget has no parent
                    break;
                else
                {
                    guiGraph_OffsetBaseXY(-widget->x, -widget->y);
                    widget = widget->parent;
                }
            }
        }
        else
        {
            // Widget has no children. Move up.
            widget->redrawForced = 0;
            guiGraph_OffsetBaseXY(-widget->x, -widget->y);
            widget = widget->parent;
        }
    }
    // Process messages
    guiCore_ProcessMessageQueue();
} */


//-------------------------------------------------------//
//  Top function for GUI redrawing
//
//-------------------------------------------------------//
void guiCore_RedrawAll(void)
{
    guiGenericWidget_t *widget;
    guiGenericWidget_t *nextWidget;
    guiGenericWidget_t *processedWidget;
    const guiEvent_t drawEvent = {GUI_EVENT_DRAW};
    uint8_t index;
    uint8_t containerRequiredRedraw;
    uint8_t trectEmpty;
    guiGenericWidget_t *w;
    uint8_t i;
    rect16_t wrect;

    // Start widget tree traverse from root widget
    widget = rootWidget;
    guiGraph_SetBaseXY(widget->x, widget->y);

    while(1)
    {
        // Process widget
        containerRequiredRedraw = widget->redrawRequired;
        if (widget->redrawRequired)
        {
            // The redrawRequired flag is reset by widget after processing DRAW event
            widget->processEvent(widget, drawEvent);
        }
        // Check if widget has children (is a container)
        if (widget->isContainer)
        {
            if (((guiGenericContainer_t *)widget)->widgets.traverseIndex == 0)
            {
                // The first time visit
                // TODO - set graph clipping
                if (containerRequiredRedraw)
                {
                    // If container needed to be redawn itself, set trect to it's size
                    ((guiGenericContainer_t *)widget)->trect.x1 = 0;
                    ((guiGenericContainer_t *)widget)->trect.y1 = 0;
                    ((guiGenericContainer_t *)widget)->trect.x2 = widget->width - 1;
                    ((guiGenericContainer_t *)widget)->trect.y2 = widget->height - 1;
                }
                else
                {
                    // Set trect to be empty - it may be expanded by child widgets
                    ((guiGenericContainer_t *)widget)->trect.x1 = 0;
                    ((guiGenericContainer_t *)widget)->trect.y1 = 0;
                    ((guiGenericContainer_t *)widget)->trect.x2 = -1;
                    ((guiGenericContainer_t *)widget)->trect.y2 = -1;
                }
            }

            // If container has unprocessed children
            if ( ((guiGenericContainer_t *)widget)->widgets.traverseIndex <
                 ((guiGenericContainer_t *)widget)->widgets.count )
            {
                // switch to next one if possible
                index = ((guiGenericContainer_t *)widget)->widgets.traverseIndex++;
                nextWidget = ((guiGenericContainer_t *)widget)->widgets.elements[index];
                // check if widget actually exists and is visible
                if ((nextWidget) && (nextWidget->isVisible))
                {
                    // Check if widget must be redrawn forcibly
                    // <------------ analyze if nextWidget and parent's trect overlap
                    if (widget->redrawForced)
                    {
                        nextWidget->redrawForced = 1;
                        nextWidget->redrawRequired = 1;
                    }
                    // Switch to next widget if required
                    if ((nextWidget->redrawRequired) || (nextWidget->isContainer))
                    {
                        widget = nextWidget;
                        guiGraph_OffsetBaseXY(widget->x, widget->y);
                    }
                }
                // Either skip current widget which does not require redraw,
                // or redraw new widget that was selected
                continue;
            }
            else
            {
                // All container child items are processed. Reset counter of processed items.
                ((guiGenericContainer_t *)widget)->widgets.traverseIndex = 0;
                widget->redrawForced = 0;
                if (widget->parent == 0)    // root widget has no parent
                    break;                  // done
            }
        }
        else
        {
            // Widget is not a container
            widget->redrawForced = 0;
        }

        //-------------------------//
        // A widget has been processed.
        // Move up the tree
        guiGraph_OffsetBaseXY(-widget->x, -widget->y);
        processedWidget = widget;
        widget = widget->parent;


        // Invalidate widget's rectangle for it's neighbours with higher Z
        // We get here if widget was not container but required redraw,
        // or widget was a container (possibly not required redraw).

        // trect has coordinates of it's container.

        if (processedWidget->isContainer)
        {
            wrect.x1 = ((guiGenericContainer_t *)processedWidget)->trect.x1;
            wrect.y1 = ((guiGenericContainer_t *)processedWidget)->trect.y1;
            wrect.x2 = ((guiGenericContainer_t *)processedWidget)->trect.x2;
            wrect.y2 = ((guiGenericContainer_t *)processedWidget)->trect.y2;

            // Offset to parent's coordinates
            wrect.x1 += processedWidget->x;
            wrect.y1 += processedWidget->y;
            wrect.x2 += processedWidget->x;
            wrect.y2 += processedWidget->y;
        }
        else
        {
            wrect.x1 = processedWidget->x;
            wrect.y1 = processedWidget->y;
            wrect.x2 = processedWidget->x + processedWidget->width - 1;
            wrect.y2 = processedWidget->y + processedWidget->height - 1;
        }

        // Expand parent's invalidating rectangle
        trectEmpty = ( ((guiGenericContainer_t *)widget)->trect.x1 > ((guiGenericContainer_t *)widget)->trect.x2 ) ? 1 : 0;
        if (wrect.x1 < wrect.x2)
        {
            if ((trectEmpty) || (wrect.x1 < ((guiGenericContainer_t *)widget)->trect.x1))
                ((guiGenericContainer_t *)widget)->trect.x1 = wrect.x1;
            if ((trectEmpty) || (wrect.y1 < ((guiGenericContainer_t *)widget)->trect.y1))
                ((guiGenericContainer_t *)widget)->trect.y1 = wrect.y1;
            if ((trectEmpty) || (wrect.x2  > ((guiGenericContainer_t *)widget)->trect.x2))
                ((guiGenericContainer_t *)widget)->trect.x2 = wrect.x2;
            if ((trectEmpty) || (wrect.y2  > ((guiGenericContainer_t *)widget)->trect.y2))
                ((guiGenericContainer_t *)widget)->trect.y2 = wrect.y2;
        }

        /////////////////////////
#ifdef emGUI_USE_Z_ORDER_REDRAW
        // Analyze parent's flag
        if (widget->redrawForced == 0)
        {
            // Widget has been redrawn - make overlapping widgets in the same container
            //  with higher Z index redraw too
            for (i = ((guiGenericContainer_t *)widget)->widgets.traverseIndex;
                 i < ((guiGenericContainer_t *)widget)->widgets.count; i++)
            {
                w = ((guiGenericContainer_t *)widget)->widgets.elements[i];
                if ((w != 0) && (w->isVisible))
                {
                    if (guiCore_CheckWidgetOvelap(w, &wrect))
                    {
                        w->redrawForced = 1;
                        w->redrawRequired = 1;
                    }
                }
            }
        }
#endif
        /////////////////////////


    }
    // Process messages
    guiCore_ProcessMessageQueue();
}






//-------------------------------------------------------//
//  Top function for touchscreen processing
//  x and y are absolute coordinates
//  touchState values are defined in guiCore.h
//-------------------------------------------------------//
void guiCore_ProcessTouchEvent(int16_t x, int16_t y, uint8_t touchState)
{
    guiEvent_t event;
    event.type = GUI_EVENT_TOUCH;
    event.spec = touchState;
    event.payload.params.lparam = (uint16_t)x;
    event.payload.params.hparam = (uint16_t)y;
#ifdef emGUI_ALWAYS_PASS_TOUCH_TO_FOCUSED
    guiCore_AddMessageToQueue(focusedWidget, &event);
#else
    if ((focusedWidget != 0) && (focusedWidget->keepTouch))
        guiCore_AddMessageToQueue(focusedWidget, &event);
    else
        guiCore_AddMessageToQueue(rootWidget, &event);
#endif
    guiCore_ProcessMessageQueue();
}

//-------------------------------------------------------//
//  Top function for processing keys
//  default keys and specificators are defined in guiCore.h
//-------------------------------------------------------//
void guiCore_ProcessKeyEvent(uint16_t code, uint8_t spec)
{
    guiEvent_t event;
    event.type = GUI_EVENT_KEY;     // CHECKME - use one of union types
    event.spec = spec;
    event.payload.params.lparam = code;
    guiCore_AddMessageToQueue(focusedWidget, &event);
    guiCore_ProcessMessageQueue();
}

//-------------------------------------------------------//
//  Top function for processing encoder
//  Obsolete
//-------------------------------------------------------//
void guiCore_ProcessEncoderEvent(int16_t increment)
{
    guiEvent_t event;
    event.type = GUI_EVENT_KEY;
    event.spec = GUI_ENCODER_EVENT;
    event.payload.params.lparam = (uint16_t)increment;
    guiCore_AddMessageToQueue(focusedWidget, &event);
    guiCore_ProcessMessageQueue();
}





//-------------------------------------------------------//
//  Sends event to all GUI elements for which validator
//  returns non-zero
//
//  guiCore_ProcessMessageQueue() should be called after
//  this function.
//  GUI message queue should be long enough - depending
//  on particular case
//-------------------------------------------------------//
void guiCore_BroadcastEvent(guiEvent_t event, uint8_t(*validator)(guiGenericWidget_t *widget))
{
    guiGenericWidget_t *widget;
    guiGenericWidget_t *nextWidget;
    uint8_t index;

    // Start widget tree traverse from root widget
    widget = rootWidget;

    while(1)
    {
        // Check if widget has children
        if (widget->isContainer)
        {
            if (((guiGenericContainer_t *)widget)->widgets.traverseIndex == 0)
            {
                // The first time visit
                if (validator(widget))
                {
                    widget->processEvent(widget, event);
                }
            }

            // If container has unprocessed children
            if ( ((guiGenericContainer_t *)widget)->widgets.traverseIndex <
                 ((guiGenericContainer_t *)widget)->widgets.count )
            {
                // switch to next one if possible
                index = ((guiGenericContainer_t *)widget)->widgets.traverseIndex++;
                nextWidget = ((guiGenericContainer_t *)widget)->widgets.elements[index];
                // check if widget actually exists
                if ((nextWidget == 0))
                    continue;
                widget = nextWidget;
            }
            else
            {
                // All container child items are processed. Reset counter of processed items and move up.
                ((guiGenericContainer_t *)widget)->widgets.traverseIndex = 0;
                if (widget->parent == 0)    // root widget has no parent
                    break;
                else
                    widget = widget->parent;
            }
        }
        else
        {
            // Widget has no children. Move up.
            if (validator(widget))
            {
                // The redrawRequired flag is reset by widget after processing DRAW event
                widget->processEvent(widget, event);
            }
            widget = widget->parent;
        }
    }
}

#ifdef emGUI_USE_UPDATE
//-------------------------------------------------------//
//  Top function for GUI elements update
//
//-------------------------------------------------------//
void guiCore_UpdateAll(void)
{
    const guiEvent_t event = {GUI_EVENT_UPDATE};
    guiCore_BroadcastEvent(event, guiCore_UpdateValidator);
    guiCore_ProcessMessageQueue();
}


//-------------------------------------------------------//
//  Returns true if widget requires update
//
//-------------------------------------------------------//
uint8_t guiCore_UpdateValidator(guiGenericWidget_t *widget)
{
    if ((widget == 0) || (widget->updateRequired == 0))
        return 0;
    else
        return 1;
}
#endif


//-------------------------------------------------------//
// GUI error handler
// One may trace call stack and thus find source of the error
//-------------------------------------------------------//
void guiCore_Error(uint8_t errCode)
{
    while(1);
}





//===================================================================//
//===================================================================//
//                                                                   //
//                    Drawing and touch support                      //
//                       geometry functions                          //
//                                                                   //
//===================================================================//


//-------------------------------------------------------//
// Makes specified rectangle invalid - it must be redrawn
// Rectangle coordinates are relative to widget's.
// When calling this function, widget should set it's
// redraw flags itself.
//-------------------------------------------------------//
void guiCore_InvalidateRect(guiGenericWidget_t *widget, int16_t x1, int16_t y1, uint16_t x2, uint16_t y2)
{
    /*
        Approach 1:
            Add this rectangle to the list of invalidated rectangles of thew form.
            Redrawing will be split into two stages:
                a.  Traverse whole widget tree and find for each container if it intercepts with any of the rectangles.
                    If there is some interseption, mark the container to fully redraw it and it's content if rectangle is
                    not an exact widget.
                    For each widget in the container also check interseption with the rectangles and mark those
                    who has interception.
                b.  Add marked widgets and containers to redraw list. Sort list by Z-index and redraw every widget.
        Approach 2:
            Check if the rectangle lies on the parent widget completely. If so, mark parent to be redrawn and exit.
            If rectangle spands over the parent's borders, check the same for parent's parent and so on, until
            root widget is reached - i.e. propagate up the tree.

        If using Z-order, possibly put all form widgets into single array?
    */


    while (1)
    {
        if (widget->parent == 0)    // root widget has no parent
            break;

        // Convert rectangle into parent's coordinates
        x1 += widget->x;
        x2 += widget->x;
        y1 += widget->y;
        y2 += widget->y;

        // Move up the tree
        widget = widget->parent;

        // Make parent widget redraw
        widget->redrawRequired = 1;
        widget->redrawForced = 1;

        // Check if rectangle lies inside parent
        if ( (x1 >= 0) &&
             (y1 >= 0) &&
             (x2 < widget->width) &&
             (y2 < widget->height) )
        {
            break;
        }
    }
}


//-------------------------------------------------------//
//  Verifies if widget and rectangle are overlapped
//
//  Returns true if interseption is not null.
//-------------------------------------------------------//
uint8_t guiCore_CheckWidgetOvelap(guiGenericWidget_t *widget, rect16_t *rect)
{
    if ((rect->x2 - rect->x1 <= 0) || (rect->y2 - rect->y1 <= 0))
        return 0;
    if ( (rect->x2 < widget->x) ||
         (rect->y2 < widget->y) ||
         (rect->x1 > widget->x + widget->width - 1) ||
         (rect->y1 > widget->y + widget->height - 1) )
        return 0;
    else
        return 1;
}


//-------------------------------------------------------//
//  Converts relative (x,y) for a specified widget to
//    absolute values (absolute means relative to screen's (0,0))
//
//-------------------------------------------------------//
void guiCore_ConvertToAbsoluteXY(guiGenericWidget_t *widget, int16_t *x, int16_t *y)
{
    while(widget != 0)
    {
        // Convert XY into parent's coordinates
        *x += widget->x;
        *y += widget->y;

        // Move up the tree
        widget = widget->parent;
    }
}


//-------------------------------------------------------//
//  Converts absolute (x,y) to relative for a specified widget
//     values (absolute means relative to screen's (0,0))
//
//-------------------------------------------------------//
void guiCore_ConvertToRelativeXY(guiGenericWidget_t *widget, int16_t *x, int16_t *y)
{
    while(widget != 0)
    {
        // Convert XY into parent's coordinates
        *x -= widget->x;
        *y -= widget->y;

        // Move up the tree
        widget = widget->parent;
    }
}


//-------------------------------------------------------//
// Returns widget that has point (x;y) and can be touched -
//  either one of child widgets or widget itself.
// If widget is not visible, or not enabled, it is skipped.
// If no widget is found, 0 is returned
// X and Y parameters must be relative to container
//-------------------------------------------------------//
guiGenericWidget_t *guiCore_GetTouchedWidgetAtXY(guiGenericWidget_t *widget, int16_t x, int16_t y)
{
    guiGenericWidget_t *w;
    uint8_t i;

    // First check if point lies inside widget
    if ((x < 0) || (x >= widget->width))
        return 0;
    if ((y < 0) || (y >= widget->height))
        return 0;

    if (widget->isContainer)
    {
        if ( (((guiGenericContainer_t *)widget)->widgets.count == 0) ||
             (((guiGenericContainer_t *)widget)->widgets.elements == 0) )
            return widget;

        // Point is inside container or one of it's widgets. Find out which one.
        i = ((guiGenericContainer_t *)widget)->widgets.count - 1;
        do
        {
            w = ((guiGenericContainer_t *)widget)->widgets.elements[i];
            if (w == 0)
                continue;
            if ((w->acceptTouch) && (w->isVisible))   // TODO - add isEnabled, etc
            {
                if ((x >= w->x) && (x < w->x + w->width) &&
                    (y >= w->y) && (y < w->y + w->height))
                {
                    return w;
                }
            }
        } while(i--);
    }
    // Not found - return widget itself
    return widget;
}


//-------------------------------------------------------//
//  Checks if widget is visible
//  Returns non-zero if widget is visible itself and
//      all his parents are visible too.
//  Note - function does not check if widget is covered by other widget or panel
//-------------------------------------------------------//
uint8_t guiCore_IsWidgetVisible(guiGenericWidget_t *widget)
{
    // Root widget has no parent
    while(widget != 0)
    {
        // Check visibility
        if (widget->isVisible == 0)
            return 0;
        // Move up the tree
        widget = widget->parent;
    }
    return 1;
}


void guiCore_DecodeWidgetTouchEvent(guiGenericWidget_t *widget, guiEvent_t *touchEvent, widgetTouchState_t *decodedTouchState)
{
    // Convert coordinates to widget's relative
    decodedTouchState->x = (int16_t)touchEvent->payload.params.lparam;
    decodedTouchState->y = (int16_t)touchEvent->payload.params.hparam;
    guiCore_ConvertToRelativeXY(widget,&decodedTouchState->x, &decodedTouchState->y);
    decodedTouchState->state = touchEvent->spec;
    // Determine if touch point lies inside the widget
    decodedTouchState->isInsideWidget = (guiCore_GetTouchedWidgetAtXY(widget,decodedTouchState->x, decodedTouchState->y)) ? 1 : 0;
}


void guiCore_DecodeContainerTouchEvent(guiGenericWidget_t *widget, guiEvent_t *touchEvent, containerTouchState_t *decodedTouchState)
{
    // Convert coordinates to widget's relative
    decodedTouchState->x = (int16_t)touchEvent->payload.params.lparam;
    decodedTouchState->y = (int16_t)touchEvent->payload.params.hparam;
    guiCore_ConvertToRelativeXY(widget,&decodedTouchState->x, &decodedTouchState->y);
    decodedTouchState->state = touchEvent->spec;
    // Determine if touch point lies inside the widget
    decodedTouchState->widgetAtXY = guiCore_GetTouchedWidgetAtXY(widget,decodedTouchState->x, decodedTouchState->y);
}




//===================================================================//
//===================================================================//
//                                                                   //
//                   Widget collections management                   //
//                                                                   //
//===================================================================//


//-------------------------------------------------------//
// Allocates memory for a widget collection
//
//-------------------------------------------------------//
void guiCore_AllocateWidgetCollection(guiGenericContainer_t *container, uint16_t count)
{
    if (container != 0)
    {
        container->widgets.count = count;
        container->widgets.elements = guiCore_calloc(count * sizeof(void *));
    }
    else
    {
        guiCore_Error(emGUI_ERROR_NULL_REF);
    }
}


//-------------------------------------------------------//
// Adds a widget to collection
// The widget being added gets specified container widget as parent
// Not used items in a collection must be zero
// If success, function returns non-zero
//-------------------------------------------------------//
uint8_t guiCore_AddWidgetToCollection(guiGenericWidget_t *widget, guiGenericContainer_t *container)
{
    uint8_t i;
    if ((widget != 0) && (container != 0))
    {
        for (i = 0; i < container->widgets.count; i++)
        {
            if (container->widgets.elements[i] == 0)
            {
                // Found free item slot
                container->widgets.elements[i] = widget;
                widget->parent = (guiGenericWidget_t *)container;
                return 1;
            }
        }
    }
    else
    {
        guiCore_Error(emGUI_ERROR_NULL_REF);
        return 0;
    }
    guiCore_Error(emGUI_ERROR_OUT_OF_PREALLOCATED_MEMORY);
    return 0;
}


//-------------------------------------------------------//
//  Pass focus to next widget in collection
//
//-------------------------------------------------------//
void guiCore_SetFocusOnNextWidget(guiGenericContainer_t *container, int8_t tabDir, uint8_t invokeType)
{
    uint8_t currentTabIndex;
    uint8_t i;
    int16_t minTabIndex = 0x200;   // maximum x2
    int16_t tmp;
    uint8_t minWidgetIndex = container->widgets.count;
    guiGenericWidget_t *widget;

    currentTabIndex = 0;

    // Check if current widget belongs to specified container's collection
    if (focusedWidget)
    {
        if (focusedWidget->parent == (guiGenericWidget_t *)container)
            currentTabIndex = focusedWidget->tabIndex;
    }


    // Find widget with next tabIndex
    for (i = 0; i < container->widgets.count; i++)
    {
        widget = (guiGenericWidget_t *)container->widgets.elements[i];
        if (widget == 0)
            continue;
        if ((widget->acceptFocusByTab) && (widget->isVisible))
        {
            if (tabDir >= 0)
                tmp = (widget->tabIndex <= currentTabIndex) ? widget->tabIndex + 256 : widget->tabIndex;
            else
                tmp = (widget->tabIndex >= currentTabIndex) ? -(widget->tabIndex - 256) : -widget->tabIndex;

            if (tmp < minTabIndex)
            {
                minTabIndex = tmp;
                minWidgetIndex = i;
            }
        }
    }

    if (minWidgetIndex < container->widgets.count)
    {
        widget = container->widgets.elements[minWidgetIndex];
        guiCore_SetFocusOn(widget, invokeType);
    }
}


//-------------------------------------------------------//
// Returns index of a widget in parent's collection
//
//-------------------------------------------------------//
uint8_t guiCore_GetWidgetIndex(guiGenericWidget_t *widget)
{
    uint8_t i;
    if ((widget == 0) || (widget->parent == 0))
        return 0;
    for (i = 0; i < ((guiGenericContainer_t *)widget->parent)->widgets.count; i++)
    {
        if (((guiGenericContainer_t *)widget->parent)->widgets.elements[i] == widget)
            return i;
    }
    return 0;   // error - widget is not present in parent's collection
}


//-------------------------------------------------------//
// Checks widget's tabindex in parent's collection.
// If current widget is the last in the collection that can be focused,
//      TABINDEX_IS_MAX is returned.
// If current widget is the first in the collection that can be focused,
//      TABINDEX_IS_MIN is returned.
// Else TABINDEX_IS_NORM is returned.
//-------------------------------------------------------//
uint8_t guiCore_CheckWidgetTabIndex(guiGenericWidget_t *widget)
{
    // TODO - add canBeFocused() function
    uint8_t i;
    uint8_t currTabIndex;
    uint8_t maxTabIndex;
    uint8_t minTabIndex;
    guiGenericWidget_t *w;
    if (widget == 0) return 0;

    currTabIndex = widget->tabIndex;
    maxTabIndex = currTabIndex;
    minTabIndex = currTabIndex;

    for (i = 0; i < ((guiGenericContainer_t *)widget->parent)->widgets.count; i++)
    {
        w = ((guiGenericContainer_t *)widget->parent)->widgets.elements[i];
        if (w == 0) continue;
        if ((w->acceptFocusByTab == 0) || (w->isVisible == 0)) continue;    // TODO - add isEnabled
        if (w->tabIndex > widget->tabIndex)
            maxTabIndex = w->tabIndex;
        else if (w->tabIndex < widget->tabIndex)
            minTabIndex = w->tabIndex;
    }

    if (currTabIndex == maxTabIndex)
        return TABINDEX_IS_MAX;
    if (currTabIndex == minTabIndex)
        return TABINDEX_IS_MIN;

    return TABINDEX_IS_NORM;
}











//===================================================================//
//===================================================================//
//                                                                   //
//                   General widget API fucntions                    //
//                                                                   //
//===================================================================//


//-------------------------------------------------------//
// Allocates memory for widget's handlers
//
//-------------------------------------------------------//
void guiCore_AllocateHandlers(void *widget, uint16_t count)
{
    guiGenericWidget_t *w = (guiGenericWidget_t *)widget;
    if (w != 0)
    {
        w->handlers.count = count;
        w->handlers.elements = guiCore_calloc(count * sizeof(guiWidgetHandler_t));
    }
    else
    {
        guiCore_Error(emGUI_ERROR_NULL_REF);
    }
}


//-------------------------------------------------------//
// Adds a handler to widget's handlers list
//
// Not used items in a collection must be zero
// If success, function returns non-zero
//-------------------------------------------------------//
uint8_t guiCore_AddHandler(void *widget, uint8_t handlerType, eventHandler_t handler)
{
    uint8_t i;
    guiGenericWidget_t *w = (guiGenericWidget_t *)widget;
    if ((w == 0) || (handler == 0))
    {
        guiCore_Error(emGUI_ERROR_NULL_REF);
        return 0;
    }
    for (i = 0; i < w->handlers.count; i++)
    {
        if (w->handlers.elements[i].handler == 0)
        {
            // Found free item slot
            w->handlers.elements[i].type = handlerType;
            w->handlers.elements[i].handler = handler;
            return 1;
        }
    }
    // No free space
    guiCore_Error(emGUI_ERROR_OUT_OF_PREALLOCATED_MEMORY);
    return 0;
}


//-------------------------------------------------------//
//  Call widget's handler for an event
//  This function should be called by widget as response for
//      some received or internal event
//
//  Function searches through the widget's handler table
//  and call handlers for matching event type
//-------------------------------------------------------//
uint8_t guiCore_CallHandler(void *widget, uint8_t handlerType, guiEvent_t *event)
{
    uint8_t i;
    uint8_t handlerResult = GUI_EVENT_DECLINE;
    guiGenericWidget_t *w = (guiGenericWidget_t *)widget;
    for(i=0; i<w->handlers.count; i++)
    {
        if (w->handlers.elements[i].type == handlerType)
        {
            handlerResult = w->handlers.elements[i].handler(w, event);
        }
    }
    return handlerResult;
}


//-------------------------------------------------------//
//  Change visible state and call handlers
//  This function should be called by widget as response for
//      received SHOW or HIDE event
//
// This function does not perform any widget state checks
//      except visible state.
// Returns 1 if new state was applied. Otherwise returns 0.
//-------------------------------------------------------//
uint8_t guiCore_AcceptVisibleState(void *widget, uint8_t newVisibleState)
{
    guiEvent_t event;
    guiGenericWidget_t *w = (guiGenericWidget_t *)widget;
    if (newVisibleState)
    {
        // Show widget
        if (w->isVisible) return 0;
        w->isVisible = 1;
        w->redrawRequired = 1;
        w->redrawForced = 1;
    }
    else
    {
        // Hide widget
        if (w->isVisible == 0) return 0;
        w->isVisible = 0;
        guiCore_InvalidateRect(w, w->x, w->y,
              w->x + w->width - 1, w->y + w->height - 1);
    }
    // Visible state changed - call handler
    if (w->handlers.count != 0)
    {
        guiCore_CallHandler(w, WIDGET_ON_VISIBLE_CHANGED, &event);
    }
    return 1;
}


//-------------------------------------------------------//
//  Change focused state and call handlers
//  This function should be called by widget as response for
//      received FOCUS or UNFOCUS message
//
// This function does not perform any widget state checks
//      except focused state.
// Returns 1 if new state was applied. Otherwise returns 0.
//-------------------------------------------------------//
uint8_t guiCore_AcceptFocusedState(void *widget, uint8_t newFocusedState)
{
    guiEvent_t event;
    uint8_t index;
    guiGenericWidget_t *w = (guiGenericWidget_t *)widget;
    if (newFocusedState)
    {
        // Check if widget is already focused
        if (w->isFocused) return 0;
        // First tell currently focused widget to loose focus
        if (focusedWidget != 0)
            focusedWidget->processEvent(focusedWidget, guiEvent_UNFOCUS);
        w->isFocused = 1;
        focusedWidget = w;
        if ((guiGenericContainer_t *)w->parent != 0)
        {
            // Update index of focused child for parent container
            index = guiCore_GetWidgetIndex(focusedWidget);
            ((guiGenericContainer_t *)w->parent)->widgets.focusedIndex = index;
        }
    }
    else
    {
        // Focus was removed
        if (w->isFocused == 0) return 0;
        w->isFocused = 0;
    }
    // Focused state changed - set drawing flags
    w->redrawFocus = 1;
    w->redrawRequired = 1;
    // Call handler
    if (w->handlers.count != 0)
    {
        guiCore_CallHandler(w, WIDGET_ON_FOCUS_CHANGED, &event);
    }
    return 1;
}








//-------------------------------------------------------//
//  Shows or hides a widget
//
// Widget is sent show or hide events ether directly, bypassing message queue, or through queue.
// If widget cannot accept the event, nothing is done. Widgets should always accept show or hide events.
//-------------------------------------------------------//
void guiCore_SetVisible(void *widget, uint8_t newVisibleState, uint8_t invokeType)
{
    guiGenericWidget_t *w = (guiGenericWidget_t *)widget;
    const guiEvent_t *event;
    if (w != 0)
    {
        event = (newVisibleState) ? &guiEvent_SHOW : &guiEvent_HIDE;
        if (invokeType == INVOKE_DIRECT)
            w->processEvent(w, *event);
        else
            guiCore_AddMessageToQueue(w, event);
    }
}


//-------------------------------------------------------//
//  Shows or hides widgets in a collection
//
// Widget is sent show or hide events ether directly, bypassing message queue, or through queue.
// If widget cannot accept the event, nothing is done. Widgets should always accept show or hide events.
//
//  Widgets are affected using mode parameter:
//      SHOW_IN_RANGE
//      HIDE_IN_RANGE
//      SHOW_OUT_OF_RANGE
//      HIDE_OUT_OF_RANGE
//  mode can be any combination of these constants
//-------------------------------------------------------//
void guiCore_SetVisibleByTag(guiWidgetCollection_t *collection, uint8_t minTag, uint8_t maxTag, uint8_t mode, uint8_t invokeType)
{
    uint8_t i;
    uint8_t tagInRange;
    guiGenericWidget_t *widget;
    const guiEvent_t *event;
    if (collection != 0)
    {
        for(i=0; i<collection->count; i++)
        {
            widget = (guiGenericWidget_t *)collection->elements[i];
            if (widget == 0)
                continue;
            tagInRange = ((widget->tag >= minTag) && (widget->tag <= maxTag)) ? mode & 0x3 : mode & 0xC;
            event = 0;
            if ((tagInRange == SHOW_IN_RANGE) || (tagInRange == SHOW_OUT_OF_RANGE))
            {
                if (widget->isVisible == 0)
                    event = &guiEvent_SHOW;
            }
            else if ((tagInRange == HIDE_IN_RANGE) || (tagInRange == HIDE_OUT_OF_RANGE))
            {
                if (widget->isVisible)
                    event = &guiEvent_HIDE;
            }
            if (event)
            {
                if (invokeType == INVOKE_DIRECT)
                    widget->processEvent(widget, *event);
                else
                    guiCore_AddMessageToQueue(widget, event);
            }
        }
    }
}


//-------------------------------------------------------//
//  Shows a widget in a collection while hiding others
//
// Widget is sent show or hide events ether directly, bypassing message queue, or through queue.
// If widget cannot accept the event, nothing is done. Widgets should always accept show or hide events.
//-------------------------------------------------------//
void guiCore_SetVisibleExclusively(void *widget, uint8_t invokeType)
{
    uint8_t i;
    guiGenericWidget_t *this_widget = (guiGenericWidget_t *)widget;
    guiGenericWidget_t *some_other_widget;
    if (this_widget != 0)
    {
        guiGenericContainer_t *parent = (guiGenericContainer_t *)this_widget->parent;
        if (parent != 0)
        {
            for (i=0; i<parent->widgets.count; i++)
            {
                some_other_widget = parent->widgets.elements[i];
                if ((some_other_widget == 0) || (some_other_widget == this_widget))
                    continue;
                if (invokeType == INVOKE_DIRECT)
                    some_other_widget->processEvent(some_other_widget, guiEvent_SHOW);
                else
                    guiCore_AddMessageToQueue(some_other_widget, &guiEvent_HIDE);
            }
        }
        if (this_widget->isVisible == 0)
        {
            if (invokeType == INVOKE_DIRECT)
                this_widget->processEvent(some_other_widget, guiEvent_SHOW);
            else
                guiCore_AddMessageToQueue(this_widget, &guiEvent_SHOW);
        }
    }
}


//-------------------------------------------------------//
// Sets focus on widget
//
// Widget is sent focus event ether directly, bypassing message queue, or through queue.
// If widget cannot accept the event, focus event is sent to widgets's parent by queue
//-------------------------------------------------------//
void guiCore_SetFocusOn(void *newFocusedWidget, uint8_t invokeType)
{
    guiGenericWidget_t *widget = (guiGenericWidget_t *)newFocusedWidget;
    if (widget != 0)
    {
        if (invokeType == INVOKE_DIRECT)
        {
            if (widget->processEvent(widget, guiEvent_FOCUS) == GUI_EVENT_DECLINE)
            {
                // Widget cannot take focus.
                // Post focus event to the parent (as would message queue processor do)
                if (widget->parent)
                    guiCore_AddMessageToQueue(widget->parent, &guiEvent_FOCUS);
            }
        }
        else
        {
            // Post focus event to the widget
            guiCore_AddMessageToQueue(widget, &guiEvent_FOCUS);
        }
    }
}







