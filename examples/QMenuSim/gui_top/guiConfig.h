//-------------------------------------------------------//
//
//          GUI library configuration file
//
//  Display settings depend on your LCD
//-------------------------------------------------------//

#include <stdint.h>

// These definitions are used by GUI graphical functions
#define DISPLAY_XSIZE (96 * 2)      // 2x LCD width (pixels)
#define DISPLAY_YSIZE 68            // LCD height (pixels)


// There should be allocated a buffer of specified size (bytes)
#define DISPLAY_BUFFER_SIZE		(96 * 9 * 2)

extern uint8_t display_buffer[DISPLAY_BUFFER_SIZE];


// Events - TODO: move to some special file
#define GUI_BTN_ESC     (1<<8)
#define GUI_BTN_LEFT    (1<<9)
#define GUI_BTN_RIGHT   (1<<10)
#define GUI_BTN_OK      (1<<11)


// Result of processEvents()
#define GUI_NO_ACTION               0
#define GUI_SWITCH_TO_OTHER_FORM    1








