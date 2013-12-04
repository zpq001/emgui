
#include "guiGraphHAL.h"
#include "guiGraphPrimitives.h"
#include "guiFonts.h"


// temporary
void guiGraph_drawButton(uint16_t x, uint16_t y)
{
    uint16_t bWidth = 50;
    uint16_t bHeight = 20;
    rect_t rect;

    /*
    rect1.x1 = 300;
    rect1.y1 = 200;
    rect1.x2 = 350;
    rect1.y2 = 260;
    guiGraph_fillRect(&rect1, CL_RED); */

    penColor = colorFromRgb(100,100,100);
    fillColor = colorFromRgb(200,200,200);

    // Fill
    rect.x1 = x + 1;
    rect.y1 = y + 1;
    rect.x2 = rect.x1 + bWidth - 2;
    rect.y2 = rect.y1 + bHeight - 2;
    guiGraph_fillRect(&rect);

    // Draw frame
/*    rect.x1 = x;
    rect.y1 = y;
    rect.x2 = rect.x1 + bWidth - 1;
    rect.y2 = rect.y1 + bHeight - 1;
    guiGraph_drawRect(&rect); */

    // Dark
    penColor = colorFromRgb(100,100,100);
    guiGraph_drawHorLine(x,y + bHeight - 1,bWidth);
    guiGraph_drawVertLine(x + bWidth - 1,y,bHeight);

    penColor = colorFromRgb(150,150,150);
    guiGraph_drawHorLine(x+1,y + bHeight - 2,bWidth-2);
    guiGraph_drawVertLine(x + bWidth - 2,y+1,bHeight-2);

    // Light
    penColor = colorFromRgb(230,230,230);
    guiGraph_drawHorLine(x,y,bWidth-1);
    guiGraph_drawVertLine(x,y,bHeight-1);

    penColor = colorFromRgb(195,195,195);
    guiGraph_drawHorLine(x + 1,y + 1,bWidth-3);
    guiGraph_drawVertLine(x + 1,y + 1,bHeight-3);




}
