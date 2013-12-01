
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

#define LOG_FROM_TOP      10
#define LOG_FROM_BOTTOM   11

// Size definitions in points
#define LCD_XSIZE 96
#define LCD_YSIZE 68

// Size definitions in bytes
#define LCD_BUFFER_SIZE 864 //96*9

extern uint16_t lcd0_buffer[];
extern uint16_t lcd1_buffer[];

typedef void (*cbFuncPtr)(int type, char *string);
typedef void (*cbLcdUpdatePtr)(int display, uint16_t *buffer);

void registerLogCallback(cbFuncPtr fptr);
void registerLcdUpdateCallback(cbLcdUpdatePtr fptr);

void guiInitialize(void);
void guiDrawAll(void);
void guiDrawIsCompleteCallback(void);
void guiButtonClicked(uint32_t buttonCode);
void guiEncoderRotated(int32_t delta);

#ifdef __cplusplus
}
#endif
