
#include <stdint.h>


// putPixel() draw mode
#define PIXEL_ON       0x00
#define PIXEL_OFF      0x01
#define PIXEL_XOR      0x02

// DrawImage() draw mode
#define PIXEL_MODE_REWRITE   0x00
#define PIXEL_MODE_OR        0x02
#define PIXEL_MODE_AND       0x06
#define PIXEL_MODE_XOR       0x0E

#define IMAGE_MODE_NORM      0x00
#define IMAGE_MODE_INVERSE   0x01

// Aliases for fill rect
#define FILL_WITH_BLACK      0x00
#define FILL_WITH_WHITE      0x01

#define guiGraph_FillRect(x_pos, y_pos, width, height, mode) \
    guiGraph_DrawImage(0, x_pos, y_pos, width, height, mode)
/*#define guiGraph_FillRectBlack(x_pos, y_pos, width, ut8_t height) \
    guiGraph_DrawImage(0, x_pos, y_pos, width, height, FILL_WITH_BLACK)
#define guiGraph_FillRectWhite(x_pos, y_pos, width, height) \
    guiGraph_DrawImage(0, x_pos, y_pos, width, height, FILL_WITH_WHITE) */


void guiGraph_FillBuffer(uint8_t value);
void guiGraph_PutPixel (uint8_t x_pos, uint8_t y_pos, uint8_t mode);
void guiGraph_PutHorLine(uint8_t x_pos, uint8_t y_pos, uint8_t length, uint8_t mode);
void guiGraph_PutVertLine(uint8_t x_pos, uint8_t y_pos, uint8_t length, uint8_t mode);

void guiGraph_DrawImage(uint8_t* img, uint8_t x_pos, uint8_t y_pos, uint8_t width, uint8_t height, uint8_t mode);


