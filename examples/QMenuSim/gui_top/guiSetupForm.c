#include <stdio.h>      // due to printf

#include "guiConfig.h"
#include "guiCore.h"
#include "guiForm.h"
#include "guiTextLabel.h"
#include "guiListBox.h"
#include "guiSpinEdit.h"
#include "guiWidgetCommon.h"
#include "guiGraphUtils.h"


// Other forms - in order to switch between them
#include "guiMainForm.h"
#include "guiSetupForm.h"

extern void guiLogEvent(char *string);
static uint8_t guiSetupForm_ProcessEvents(guiEvent_t event);
static void guiSetupForm_drawStatic(void);
static void guiSetupForm_On_ListBox1_indexChanged(void *sender);

//--------- Form elements ---------//
static guiTextLabel_t TextLabel1;

static guiTextLabel_t TextLabel_10;
static guiTextLabel_t TextLabel_11;

static guiListBox_t ListBox1;
static char *ListBox1Strings[8];
static guiWidgetHandler_t listBox1Handlers[1];

static guiSpinEdit_t SpinEdit1;
static guiSpinEdit_t SpinEdit2;

//----------- GUI Form  -----------//
guiForm_t     guiSetupForm;
static void *guiSetupFormElements[6];



void guiSetupForm_Initialize(void)
{
    // Initialize gui elements
    guiForm_Initialize(&guiSetupForm);
    guiSetupForm.processEvent = guiSetupForm_ProcessEvents;
    guiSetupForm.widgets.count = 6;
    guiSetupForm.widgets.elements = guiSetupFormElements;
    guiSetupForm.widgets.elements[0] = &TextLabel1;
    guiSetupForm.widgets.elements[1] = &ListBox1;
    guiSetupForm.widgets.elements[2] = &SpinEdit1;
    guiSetupForm.widgets.elements[3] = &SpinEdit2;
    guiSetupForm.widgets.elements[4] = &TextLabel_10;
    guiSetupForm.widgets.elements[5] = &TextLabel_11;

    guiTextLabel_Initialize(&TextLabel1);
    TextLabel1.pfont = &font_8x12;
    TextLabel1.string = "Settings";
    TextLabel1.x_pos = 15;
    TextLabel1.y_pos = 1;    
    TextLabel1.tabIndex = 0;    // not tab-selectable
    TextLabel1.properties = WP_IS_VISIBLE;

    guiListBox_Initialize(&ListBox1);
    ListBox1.items.strings = ListBox1Strings;
    ListBox1.items.count = 8;
    ListBox1.items.strings[0] = "Voltage lim";
    ListBox1.items.strings[1] = "Current lim";
    ListBox1.items.strings[2] = "Item 3";
    ListBox1.items.strings[3] = "Item 4";
    ListBox1.items.strings[4] = "Item 5";
    ListBox1.items.strings[5] = "Item 6";
    ListBox1.items.strings[6] = "Item 7";
    ListBox1.items.strings[7] = "";
    ListBox1.x_pos = 2;
    ListBox1.y_pos = 15;
    ListBox1.width = 92;
    ListBox1.tabIndex = 0;
    ListBox1.pFont = &font_8x12;
    ListBox1.properties = /*LISTBOX_RESTORE_INDEX_ON_ESC |*/ LISTBOX_CAN_WRAP /*| LISTBOX_HAS_FRAME*/ | WP_IS_VISIBLE | WP_SELECT_IS_ACTIVATE;
    ListBox1.handlers.count = 1;
    ListBox1.handlers.elements = listBox1Handlers;

    ListBox1.handlers.elements[0].eventType = WEVENT_SELECTED_INDEX_CHANGED;
    ListBox1.handlers.elements[0].handler = guiSetupForm_On_ListBox1_indexChanged;


    guiTextLabel_Initialize(&TextLabel_10);
    TextLabel_10.pfont = &font_8x12;
    TextLabel_10.string = "High [V]";
    TextLabel_10.x_pos = 96 + 4;
    TextLabel_10.y_pos = 4;
    TextLabel_10.tabIndex = 0;    // not tab-selectable
    TextLabel_10.tag = 12;

    guiTextLabel_Initialize(&TextLabel_11);
    TextLabel_11.pfont = &font_8x12;
    TextLabel_11.string = "Low [V]";
    TextLabel_11.x_pos = 96 + 4;
    TextLabel_11.y_pos = 35;
    TextLabel_11.tabIndex = 0;    // not tab-selectable
    TextLabel_11.tag = 13;

    guiSpinEdit_Initialize(&SpinEdit1);
    SpinEdit1.x_pos = 100;
    SpinEdit1.y_pos = 18;
    SpinEdit1.width = 80;
    SpinEdit1.dotPosition = 2;
    SpinEdit1.properties = 0/*WP_SELECT_IS_ACTIVATE*/ /*| SPINEDIT_HAS_FRAME*/ /*| WP_IS_VISIBLE*/ | SPINEDIT_RESTORE_ON_ESC;
    SpinEdit1.activeDigit = 2;
    SpinEdit1.minDigitsToDisplay = 3;
    SpinEdit1.pFont = &font_8x12;
    SpinEdit1.tabIndex = 1;
    SpinEdit1.tag = 10;
    guiSpinEdit_SetValue(&SpinEdit1, -7);

    guiSpinEdit_Initialize(&SpinEdit2);
    SpinEdit2.x_pos = 100;
    SpinEdit2.y_pos = 50;
    SpinEdit2.width = 80;
    SpinEdit2.dotPosition = 2;
    SpinEdit2.properties = 0 /*WP_SELECT_IS_ACTIVATE*/ /*| SPINEDIT_HAS_FRAME*/ /*| WP_IS_VISIBLE*/ | SPINEDIT_RESTORE_ON_ESC;
    SpinEdit2.activeDigit = 1;
    SpinEdit2.minDigitsToDisplay = 2;
    SpinEdit2.pFont = &font_8x12;
    SpinEdit2.tabIndex = 2;
    SpinEdit2.tag = 11;
    guiSpinEdit_SetValue(&SpinEdit2, 851520);

    guiCore_SetVisibleByTag(&guiSetupForm.widgets,10,20,ITEMS_IN_RANGE_ARE_VISIBLE);
}


static uint8_t guiSetupForm_ProcessEvents(guiEvent_t event)
{
    uint8_t temp;
    // Process GUI messages - select, draw, etc
    switch(event.type)
    {
        case GUI_EVENT_DRAW:
            guiForm_Draw(&guiSetupForm);
            if (guiSetupForm.redrawFlags & WF_REDRAW)
                guiSetupForm_drawStatic();
            guiSetupForm.redrawFlags = 0;
            break;
        case GUI_EVENT_SELECT:
            guiCore_SelectWidget(&guiSetupForm.widgets, (guiGenericWidget_t *)&ListBox1);
            guiListBox_SelectItem(&ListBox1,0);
            //guiCore_SelectNextWidget(&guiSetupForm.widgets, 1);
            guiCore_RequestFullRedraw();
            break;
        case GUI_EVENT_DESELECT:
            //guiCore_SelectWidget(&guiSetupForm.widgets, 0);
            break;
        default:

            // Pass event to the widgets
            if (guiSetupForm.widgets.pSelected)
            {
                temp = ((guiGenericWidget_t *)guiSetupForm.widgets.pSelected)->processEvent(guiSetupForm.widgets.pSelected, event);
            }
            else
            {
                temp = EVENT_FLAG_NOT_USED;
            }

            if (temp == EVENT_FLAG_NOT_USED)
            {
                // Process form logic
                if (guiSetupForm.widgets.pSelected == &ListBox1)
                {
                    if (((guiEventArgButtons_t *)event.args)->buttonCode & GUI_BTN_ESC)
                        guiCore_RequestSwitchForm(&guiMainForm);
                    else if (((guiEventArgButtons_t *)event.args)->buttonCode & GUI_BTN_OK)
                        guiCore_SelectNextWidget(&guiSetupForm.widgets, 1);
                }
                else
                {
                    if (((guiEventArgButtons_t *)event.args)->buttonCode & (GUI_BTN_ESC | GUI_BTN_OK))
                        guiCore_SelectWidget(&guiSetupForm.widgets, (guiGenericWidget_t *)&ListBox1);
                    else if (((guiEventArgButtons_t *)event.args)->buttonCode & GUI_BTN_LEFT)
                        guiCore_SelectNextWidget(&guiSetupForm.widgets, -1);
                    else if (((guiEventArgButtons_t *)event.args)->buttonCode & GUI_BTN_RIGHT)
                        guiCore_SelectNextWidget(&guiSetupForm.widgets, 1);
                }

            }
    }
    guiCore_CallEventHandler((guiGenericWidget_t *)&guiSetupForm,event.type);
    return 0;
}


static void guiSetupForm_drawStatic(void)
{
    guiGraph_PutHorLine(2,13,92,PIXEL_ON);
  //  guiGraph_PutHorLine(2,15,92,PIXEL_ON);
}


static void guiSetupForm_On_ListBox1_indexChanged(void *sender)
{
    guiListBox_t *pListBox = (guiListBox_t *)sender;

    guiCore_SetVisibleByTag(&guiSetupForm.widgets,10,100,ITEMS_IN_RANGE_ARE_INVISIBLE);

    switch (pListBox->items.selectedIndex)
    {
        case 0:
            guiCore_SetVisibleByTag(&guiSetupForm.widgets,10,20,ITEMS_IN_RANGE_ARE_VISIBLE);
            break;
        case 1:
            guiCore_SetVisibleByTag(&guiSetupForm.widgets,20,30,ITEMS_IN_RANGE_ARE_VISIBLE);
            break;
    }
}




