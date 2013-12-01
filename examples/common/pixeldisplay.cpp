#include <qpainter.h>
#include "pixeldisplay.h"

// Constructor
// We can tell Qt that a widget has static content (so it will only repaint newly revealed rectangles) using the WStaticContents flag:
PixelDisplay::PixelDisplay(QWidget *parent) :
    //QWidget(parent, Qt::WA_StaticContents)
    QFrame(parent)
{
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setLineWidth(1);
    scale = 1.0;
    activePixelColor = qRgb(0, 0, 0);
    backgroundColor = qRgb(180, 230, 150);
    image = QImage(128,128,QImage::Format_RGB32);
    image.fill(backgroundColor);
    setMinimumSize(QSize(image.width() + lineWidth()*2,image.height() + lineWidth()*2));
}



// Returns optimal size for widget
QSize PixelDisplay::sizeHint(void) const
{
    QSize size = QSize(image.width()*scale+lineWidth()*2,image.height()*scale+lineWidth()*2);
    return size;
}


// Sets new color for active pixels
void PixelDisplay::setActivePixelColor(const QColor &newColor)
{
    activePixelColor = newColor.Rgb;
    update();
}

// Sets new color for background pixels
void PixelDisplay::setBackgroundColor(const QColor &newColor)
{
    backgroundColor = newColor.Rgb;
    update();
}

void PixelDisplay::setImageSize(int width, int height)
{
 //   image.~QImage();
    image = QImage(width,height,QImage::Format_RGB32);
    image.fill(backgroundColor);
    setMinimumSize(QSize(image.width() + lineWidth()*2,image.height() + lineWidth()*2));
    updateGeometry();
}

void PixelDisplay::setScale(float newScale)
{
    scale = newScale;
    updateGeometry();
}


void PixelDisplay::updateImage(uint16_t *lcd_buffer)
{
    unsigned int bitMask, bufferOffset, bufferIndex;
    int bitmap_x, bitmap_y;

    for (bitmap_y = 0; bitmap_y < image.height(); bitmap_y++)
    {
        bufferOffset = (bitmap_y / 8) * image.width();
        bufferIndex = 0;
        bitMask = 1<<(bitmap_y % 8);

        for (bitmap_x = 0; bitmap_x < image.width(); bitmap_x++)
        {
            if (lcd_buffer[bufferOffset + bufferIndex] & bitMask)
                image.setPixel(bitmap_x,bitmap_y,activePixelColor);
            else
                image.setPixel(bitmap_x,bitmap_y,backgroundColor);
            bufferIndex++;
        }
    }

    this->update();
}


void PixelDisplay::paintEvent(QPaintEvent *e)
{
    QFrame::paintEvent(e);

    QPainter painter(this);
   // int i,j;

//    painter.setPen(Qt::black);
   // painter.drawRect(0,0,width()-1,height()-1);
    painter.drawImage(lineWidth(),lineWidth(),image.scaled(width()-2*lineWidth(),height()-2*lineWidth()));
 //   painter.drawImage(0,0,image);
    /*
    for (i=0;i<image.width();i++)
        for (j=0;j<image.height();j++)
            drawImagePixel(&painter,i,j);
*/
}


void PixelDisplay::drawImagePixel(QPainter *painter, int i, int j)
{
/*  QColor color;
  QRgb rgb = image.pixel(i, j);


  color.setRgb(rgb);

  if (zoom >= 3) {
    painter->fillRect(zoom * i + 1, zoom * j + 1,
                      zoom - 1, zoom - 1, color);
  } else {
    painter->fillRect(zoom * i, zoom * j,
                      zoom, zoom, color);
  } */
}
