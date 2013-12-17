
#include <stdint.h>
#include "guiGraphHAL.h"


#ifdef __cplusplus
extern "C" {
#endif


#define DISPLAY_XSIZE   LCD_XSIZE
#define DISPLAY_YSIZE   LCD_YSIZE


//-----------------------------------//
// Keyboard support

// Button codes
#define KEY_ESC     (1<<0)
#define KEY_LEFT    (1<<1)
#define KEY_RIGHT   (1<<2)
#define KEY_OK      (1<<3)



//-----------------------------------//
// Button and encoder event structures
/*
typedef struct {
    uint8_t action_down;		// Bit is set once when button is pressed
    uint8_t action_repeat;      // Bit is set once when button is pressed. Bit is set continuously after some delay until button is released
    uint8_t action_up_short;	// Bit is set once when button is released before some time mark
    uint8_t action_hold;		// Bit is set once when button is pressed longer than some time mark
} guiButtonArgs_t;


typedef struct {
    uint8_t encoder_up;
    uint8_t encoder_down;
    int16_t encoder_delta;
} guiEncoderArgs_t;

*/





//-----------------------------------//
// Callbacks
#define LOG_FROM_TOP      10
#define LOG_FROM_BOTTOM   11

typedef void (*cbLogPtr)(int type, char *string);
//typedef void (*cbLcdUpdatePtr)(int display, uint16_t *buffer);
typedef void (*cbLcdUpdatePtr)(uint32_t *buffer);

void registerLogCallback(cbLogPtr fptr);
void registerLcdUpdateCallback(cbLcdUpdatePtr fptr);
//-----------------------------------//





// Functions for top-level
void guiUpdateTime(uint8_t hours, uint8_t minutes, uint8_t seconds);
void guiInitialize(void);
void guiDrawAll(void);
void guiButtonPressed(uint16_t buttonCode);
void guiButtonReleased(uint16_t buttonCode);
void guiEncoderRotated(int32_t delta);

void guiTouchMoved(int x, int y);
void guiTouchPressed(int x, int y);
void guiTouchReleased(int x, int y);


// Functions for calling from GUI
void guiLogEvent(char *string);
void guiDrawIsComplete(void);



#ifdef __cplusplus
}
#endif
