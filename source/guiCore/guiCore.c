/**********************************************************
    Module guiCore




**********************************************************/

#include <stdint.h>
//#include "guiFonts.h"
#include "guiGraphPrimitives.h"
#include "guiGraphWidgets.h"
#include "guiEvents.h"
#include "guiWidgets.h"
#include "guiForm.h"
#include "guiCore.h"




const guiEvent_t guiEvent_DRAW = {GUI_EVENT_DRAW, 0};
const guiEvent_t guiEvent_UPDATE = {GUI_EVENT_UPDATE, 0};

const guiEvent_t guiEvent_HIDE = {GUI_EVENT_HIDE, 0};
const guiEvent_t guiEvent_SHOW = {GUI_EVENT_SHOW, 0};

const guiEvent_t guiEvent_UNFOCUS = {GUI_EVENT_UNFOCUS, 0};
const guiEvent_t guiEvent_FOCUS = {GUI_EVENT_FOCUS, 0};



guiMsgQueue_t guiMsgQueue;



guiGenericWidget_t *rootWidget;
guiGenericWidget_t *focusedWidget;


//=======================================================//


uint8_t guiCore_AddMessageToQueue(const guiGenericWidget_t *target, const guiEvent_t *event)
{
    if (guiMsgQueue.count < GUI_CORE_QUEUE_SIZE)
    {
        guiMsgQueue.queue[guiMsgQueue.tail].event = *event;
        guiMsgQueue.queue[guiMsgQueue.tail].target = (guiGenericWidget_t *)target;
        guiMsgQueue.count++;
        guiMsgQueue.tail++;
        if (guiMsgQueue.tail == GUI_CORE_QUEUE_SIZE)
            guiMsgQueue.tail = 0;
        return 1;
     }
    return 0;
}

uint8_t guiCore_GetMessageFromQueue(guiGenericWidget_t **target, guiEvent_t *event)
{
    if (guiMsgQueue.count > 0)
    {
        *target = guiMsgQueue.queue[guiMsgQueue.head].target;
        *event = guiMsgQueue.queue[guiMsgQueue.head].event;
        guiMsgQueue.count--;
        guiMsgQueue.head++;
        if (guiMsgQueue.head == GUI_CORE_QUEUE_SIZE)
            guiMsgQueue.head = 0;
        return 1;
    }
    return 0;
}





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



//=======================================================//




//-------------------------------------------------------//
//  Top function for GUI core initializing
//  All components must be already initialized
//-------------------------------------------------------//
void guiCore_Init(guiGenericWidget_t *rootObject)
{
    guiMsgQueue.count = 0;
    guiMsgQueue.head = 0;
    guiMsgQueue.tail = 0;

    rootWidget = rootObject;
    focusedWidget = rootObject;
    // Redraw flags ?

    guiCore_PostEventToFocused(guiEvent_FOCUS);
    guiCore_ProcessMessageQueue();
}



void guiCore_RedrawAll(void)
{
    guiGenericWidget_t *widget;
    guiGenericWidget_t *nextWidget;
    uint8_t index;

    // Update root widget. Root widget can further call
    // update for any other widget.
    guiCore_AddMessageToQueue(rootWidget, &guiEvent_UPDATE);
    guiCore_ProcessMessageQueue();

    // Start widget tree traverse from root widget
    widget = rootWidget;
    guiGraph_SetBaseXY(widget->x, widget->y);

    while(1)
    {
        // Process widget
        if (widget->redrawRequired)
        {
            // The redrawRequired flag is reset by widget after processing DRAW event
            widget->processEvent(widget, guiEvent_DRAW);
        }
        // Check if widget has children
        if (widget->isContainer)
        {
            // If container has unprocessed children
            if ( ((guiGenericContainer_t *)widget)->widgets.traverseIndex <
                 ((guiGenericContainer_t *)widget)->widgets.count )
            {
                // switch to next one if possible
                index = ((guiGenericContainer_t *)widget)->widgets.traverseIndex++;
                nextWidget = ((guiGenericContainer_t *)widget)->widgets.elements[index];
                // check if widget actually exists and is visible
                if (nextWidget == 0)
                    continue;
                if (nextWidget->isVisible == 0)
                    continue;
                // Check if widget must be redrawn forcibly
                if (widget->redrawForced)
                {
                    nextWidget->redrawForced = 1;
                    nextWidget->redrawRequired = 1;
                }
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
}




void guiCore_ProcessTouchEvent(int16_t x, int16_t y, uint8_t touchState)
{
    guiEvent_t event;
    event.type = GUI_EVENT_TOUCH;
    event.spec = touchState;
    event.lparam = (uint16_t)x;
    event.hparam = (uint16_t)y;
    guiCore_AddMessageToQueue(focusedWidget, &event);
    guiCore_ProcessMessageQueue();
}

void guiCore_ProcessButtonEvent(uint16_t code, uint8_t spec)
{
    guiEvent_t event;
    event.type = GUI_EVENT_KEY;
    event.spec = spec;
    event.lparam = code;
    guiCore_AddMessageToQueue(focusedWidget, &event);
    guiCore_ProcessMessageQueue();
}

void guiCore_ProcessEncoderEvent(int16_t increment)
{
    guiEvent_t event;
    event.type = GUI_EVENT_ENCODER;
    event.spec = 0;
    event.lparam = (uint16_t)increment;
    guiCore_AddMessageToQueue(focusedWidget, &event);
    guiCore_ProcessMessageQueue();
}








// CHECKME
void guiCore_PostEventToFocused(guiEvent_t event)
{
    if (focusedWidget == 0)
        return;                 // Should not normally happen ?
    guiCore_AddMessageToQueue(focusedWidget, &event);
}


void guiCore_ConvertToAbsoluteXY(guiGenericWidget_t *widget, int16_t *x, int16_t *y)
{
    while(widget->parent != 0)
    {
        // Convert XY into parent's coordinates
        *x += widget->x;
        *y += widget->y;

        // Move up the tree
        widget = widget->parent;
    }
}

void guiCore_ConvertToRelativeXY(guiGenericWidget_t *widget, int16_t *x, int16_t *y)
{
    while(widget->parent != 0)
    {
        // Convert XY into parent's coordinates
        *x -= widget->x;
        *y -= widget->y;

        // Move up the tree
        widget = widget->parent;
    }
}

/*
uint8_t guiCore_CheckWidgetXY(guiGenericWidget_t *widget, int16_t x, int16_t y)
{
    if (x < 0)
        return 0;
    if (x >= widget->width)
        return 0;
    if (y < 0)
        return 0;
    if (y >= widget->height)
        return 0;

    return 1;
}
*/



// Returns widget that has point (x;y) - either one of child widgets or widget itself.
// If widget is not visible, or not enabled, it is skipped.
// If no widget is found, 0 is returned
// X and Y parameters must be relative to container
guiGenericWidget_t *guiCore_GetWidgetAtXY(guiGenericWidget_t *widget, int16_t x, int16_t y)
{
    guiGenericWidget_t *w;
    uint8_t i;
    // First check if point lies inside container
    if ((x < 0) || (x >= widget->width))
        return 0;
    if ((y < 0) || (y >= widget->height))
        return 0;

    if (widget->isContainer)
    {
        // Point is inside container or one of it's widgets. Find out which one.
        for (i=0; i<((guiGenericContainer_t *)widget)->widgets.count; i++)
        {
            w = ((guiGenericContainer_t *)widget)->widgets.elements[i];
            if (w == 0)
                continue;
            if ((w->acceptTouch) && (w->isVisible))   // TODO - add isEnabled, etc
            {
                if ((x >= w->x) && (x < w->x + w->width) &&
                    (y >= w->y) && (y < w->y + w->height))
                {
                    return w;  // Found
                }
            }
        }
    }
    // Not found - return container itself
    return (guiGenericWidget_t *)widget;
}




//-------------------------------------------------------//
//  GUI core function for processing message queue
//
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


// Returns index of a widget in parent's collection
uint8_t guiCore_GetWidgetIndex(guiGenericWidget_t *widget)
{
    uint8_t i;
    if (widget == 0) return 0;
    if (widget->parent == 0) return 0;
    for (i = 0; i < ((guiGenericContainer_t *)widget->parent)->widgets.count; i++)
    {
        if (((guiGenericContainer_t *)widget->parent)->widgets.elements[i] == widget)
            return i;
    }
    return 0;   // error - widget is not present in parent's collection
}


void guiCore_RequestFocusChange(guiGenericWidget_t *newFocusedWidget)
{
    if (newFocusedWidget == focusedWidget)
        return;

    // First tell currently focused widget to loose focus
//    if (focusedWidget != 0)
//    {
//        guiCore_AddMessageToQueue(focusedWidget, guiEvent_UNFOCUS);
//    }
    // Tell new widget to get focus
    if (newFocusedWidget != 0)
    {
        guiCore_AddMessageToQueue(newFocusedWidget, &guiEvent_FOCUS);
    }
}


void guiCore_AcceptFocus(guiGenericWidget_t *widget)
{
    uint8_t index;
    // First tell currently focused widget to loose focus
    if (focusedWidget != 0)
    {
        guiCore_AddMessageToQueue(focusedWidget, &guiEvent_UNFOCUS);
    }
    focusedWidget = widget;
    index = guiCore_GetWidgetIndex(focusedWidget);
    if ((guiGenericContainer_t *)widget->parent != 0)
        ((guiGenericContainer_t *)widget->parent)->widgets.focusedIndex = index;
}


// Checks widget's tabindex in parent's collection.
// If current widget is the last in the collection that can be focused,
//      TABINDEX_IS_MAX is returned.
// If current widget is the first in the collection that can be focused,
//      TABINDEX_IS_MIN is returned.
// Else TABINDEX_IS_NORM is returned.
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
        if ((w->acceptFocusByTab == 0) || (w->isVisible == 0)) continue;
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








//-------------------------------------------------------//
//  Pass focus to next widget in collection
//
//-------------------------------------------------------//
void guiCore_RequestFocusNextWidget(guiGenericContainer_t *container, int8_t tabDir)
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
        //container->widgets.focusedIndex = minWidgetIndex;
        guiCore_RequestFocusChange(widget);
    }
}


//-------------------------------------------------------//
//  Gets next widget in collection to focus on
//
//-------------------------------------------------------//
guiGenericWidget_t *guiCore_GetNextFocusWidget(guiGenericContainer_t *container, int8_t tabDir)
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
        //container->widgets.focusedIndex = minWidgetIndex;
        return widget;
    }
    return 0;
}




// CHECKME - const modifiers
uint8_t guiCore_CallEventHandler(guiGenericWidget_t *widget, guiEvent_t *event)
{
    uint8_t i;
    uint8_t handlerResult = GUI_EVENT_DECLINE;
    for(i=0; i<widget->handlers.count; i++)
    {
        if (widget->handlers.elements[i].eventType == event->type)
        {
            handlerResult = widget->handlers.elements[i].handler(widget, event);
        }
    }
    return handlerResult;
}



void guiCore_SetVisibleByTag(guiWidgetCollection_t *collection, uint8_t minTag, uint8_t maxTag, uint8_t mode)
{
    uint8_t i;
    uint8_t tagInRange;
    guiGenericWidget_t *widget;
    for(i=0; i<collection->count; i++)
    {
        widget = (guiGenericWidget_t *)collection->elements[i];
        if (widget == 0)
            continue;
        tagInRange = ((widget->tag >= minTag) && (widget->tag <= maxTag)) ? mode & 0x3 : mode & 0xC;
        if ((tagInRange == ITEMS_IN_RANGE_ARE_VISIBLE) || (tagInRange == ITEMS_OUT_OF_RANGE_ARE_VISIBLE))
        {
            if (widget->isVisible == 0)
                //widget->processEvent(widget, guiEvent_SHOW);
                guiCore_AddMessageToQueue(widget, &guiEvent_SHOW);
        }
        else if ((tagInRange == ITEMS_IN_RANGE_ARE_INVISIBLE) || (tagInRange == ITEMS_OUT_OF_RANGE_ARE_INVISIBLE))
        {
            if (widget->isVisible)
                //widget->processEvent(widget, guiEvent_HIDE);
                guiCore_AddMessageToQueue(widget, &guiEvent_HIDE);
        }
    }
}





//=======================================================//
//=======================================================//
//                                                       //
//              Generic widget API fucntions             //
//                                                       //
//=======================================================//



void guiCore_SetVisible(guiGenericWidget_t *widget, uint8_t newVisibleState)
{
    guiEvent_t event;
    if (widget == 0) return;
    if (newVisibleState)
    {
        // Show widget
        if (widget->isVisible) return;
        widget->isVisible = 1;
        widget->redrawForced = 1;
    }
    else
    {
        // Hide widget
        if (widget->isVisible == 0) return;
        widget->isVisible = 0;
        guiCore_InvalidateRect(widget, widget->x, widget->y,
              widget->x + widget->width - 1, widget->y + widget->height - 1);
    }
    // Visible state changed - call handler
    if (widget->handlers.count != 0)
    {
        event.type = GUI_ON_VISIBLE_CHANGED;
        guiCore_CallEventHandler(widget, &event);
    }
}



void guiCore_DecodeWidgetTouchEvent(guiGenericWidget_t *widget, guiEvent_t *touchEvent, widgetTouchState_t *decodedTouchState)
{
    // Convert coordinates to widget's relative
    decodedTouchState->x = (int16_t)touchEvent->lparam;
    decodedTouchState->y = (int16_t)touchEvent->hparam;
    guiCore_ConvertToRelativeXY(widget,&decodedTouchState->x, &decodedTouchState->y);
    decodedTouchState->state = touchEvent->spec;
    // Determine if touch point lies inside the widget
    decodedTouchState->isInsideWidget = (guiCore_GetWidgetAtXY(widget,decodedTouchState->x, decodedTouchState->y)) ? 1 : 0;
}


void guiCore_DecodeContainerTouchEvent(guiGenericWidget_t *widget, guiEvent_t *touchEvent, containerTouchState_t *decodedTouchState)
{
    // Convert coordinates to widget's relative
    decodedTouchState->x = (int16_t)touchEvent->lparam;
    decodedTouchState->y = (int16_t)touchEvent->hparam;
    guiCore_ConvertToRelativeXY(widget,&decodedTouchState->x, &decodedTouchState->y);
    decodedTouchState->state = touchEvent->spec;
    // Determine if touch point lies inside the widget
    decodedTouchState->widgetAtXY = guiCore_GetWidgetAtXY(widget,decodedTouchState->x, decodedTouchState->y);
}







