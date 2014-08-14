/**********************************************************
    emGUI configuration file

    Project - specific

**********************************************************/

#ifndef __GUI_CONFIG_H_
#define __GUI_CONFIG_H_


// Setup core queue size
#define emGUI_CORE_QUEUE_SIZE 20

// Heap settings
#define emGUI_HEAP_SIZE             2000        // bytes
#define emGUI_BYTE_ALIGNMENT        4           // bytes
#define emGUI_POINTER_SIZE_TYPE     uint32_t

// Enable this macro if your design requires timer API
#define emGUI_USE_TIMERS
// Setup number of timers used
#define emGUI_TIMERS_COUNT          1
// Enumerate your timers to allow access by name, not only index
enum emGUI_Timers { TMR_TIME_UPDATE };

// Enable or disable touch support
#define emGUI_USE_TOUCH_SUPPORT
// Touch processing option
//#define emGUI_ALWAYS_PASS_TOUCH_TO_FOCUSED

// Enable or disable widgets update stuff
#define emGUI_USE_UPDATE

// Enable or disable using of Z-order for redrawing
#define emGUI_USE_Z_ORDER_REDRAW



//---------- Graphic library configuration ----------//

// Screen size definitions in pixels
#define LCD_XSIZE 320
#define LCD_YSIZE 240




#endif  // __GUI_CONFIG_H_
