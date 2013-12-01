#ifndef PIXELDISPLAY_H
#define PIXELDISPLAY_H

#include <QWidget>
#include <QFrame>
#include <qimage.h>
#include <qwidget.h>

class PixelDisplay : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(QColor activePixelColor READ getActivePixelColor WRITE setActivePixelColor)
public:
    explicit PixelDisplay(QWidget *parent = 0);
    void setActivePixelColor(const QColor &newColor);
    void setBackgroundColor(const QColor &newColor);
    void updateImage(uint16_t *lcd_buffer);
    QColor getActivePixelColor(void) {return activePixelColor;}
    QColor getBackgroundPixelColor(void) {return backgroundColor;}
    void setImageSize(int width, int height);
    void setScale(float newScale);
signals:

public slots:


protected:
    void paintEvent(QPaintEvent *event);
    QSize sizeHint(void) const;
private:
    void drawImagePixel(QPainter *painter, int i, int j);
    QRgb activePixelColor;
    QRgb backgroundColor;
    QImage image;
    float scale;
};

#endif // PIXELDISPLAY_H
