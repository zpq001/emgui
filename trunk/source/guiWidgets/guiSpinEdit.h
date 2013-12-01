
#include <stdint.h>
#include "guiEvents.h"
#include "guiFonts.h"
#include "guiCore.h"

#define SPINEDIT_STRING_LENGTH  12  // long enough to hold INT32_MAX and INT32_MIN + \0

#define SPINEDIT_HAS_FRAME  (1<<4)
#define SPINEDIT_RESTORE_ON_ESC    (1<<7)

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
    uint8_t x_pos;
    uint8_t y_pos;
    uint8_t width;
    uint8_t height;
    uint8_t blinkInterval;

    int32_t value;
    // TODO - maxValue, minValue
    int32_t savedValue;

    uint8_t dotPosition;
    uint8_t activeDigit;
    uint8_t minDigitsToDisplay;
    uint8_t digitsToUse;
    char string[SPINEDIT_STRING_LENGTH];
    guiFont_t *pFont;
} guiSpinEdit_t;




void guiSpinEdit_Initialize(guiSpinEdit_t *pListBox);
void guiSpinEdit_SetValue(guiSpinEdit_t *pSpinEdit, int32_t newValue);
void guiSpinEdit_SetVisible(guiSpinEdit_t* pSpinEdit, uint8_t visibleMode);
void guiSpinBox_SetMaxValue(guiSpinEdit_t *pSpinEdit, int32_t newValue);
void guiSpinBox_SetMinValue(guiSpinEdit_t *pSpinEdit, int32_t newValue);




