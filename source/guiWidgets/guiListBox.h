
#include <stdint.h>
#include "guiEvents.h"
#include "guiFonts.h"
#include "guiCore.h"



#define LISTBOX_CAN_WRAP    (1<<4)
#define LISTBOX_HAS_FRAME   (1<<5)
#define LISTBOX_RESTORE_INDEX_ON_ESC    (1<<7)



typedef struct {
    uint8_t count;
    uint8_t selectedIndex;
    uint8_t savedIndex;
    uint8_t firstIndexToDisplay;
    char **strings;
} guiStringCollection_t;



typedef struct {
    //----------------------//
    // Fields, common for all widgets
    uint8_t type;
    uint8_t redrawFlags;
    uint8_t tabIndex;
    uint8_t state;
    uint8_t tag;
    uint8_t (*processEvent)(struct guiGenericWidget_t *pWidget, guiEvent_t event);
    guiHandlerTable_t handlers;
    uint8_t properties;
    //----------------------//
    // Widget - specific
    guiStringCollection_t items;
    uint8_t x_pos;
    uint8_t y_pos;
    uint8_t width;
    uint8_t height;
    uint8_t visibleItemsCount;
    guiFont_t *pFont;

} guiListBox_t;




void guiListBox_Initialize(guiListBox_t *pListBox);
void guiListBox_SelectItem(guiListBox_t* pListBox, uint8_t index);

