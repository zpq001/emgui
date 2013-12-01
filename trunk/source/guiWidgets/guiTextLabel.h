
#include <stdint.h>
#include "guiEvents.h"
#include "guiFonts.h"
#include "guiCore.h"


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
	uint8_t x_pos;
	uint8_t y_pos;
	guiFont_t *pfont;
    char *string;
} guiTextLabel_t;


//void guiTextLabel_Draw(guiTextLabel_t* pLabel);
//void guiTextLabel_Select(guiTextLabel_t* pTextLabel, uint8_t mode);


void guiTextLabel_Initialize(guiTextLabel_t *pTextLabel);





