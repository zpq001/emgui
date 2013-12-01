#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSignalMapper.h>
#include <QTimer.h>
#include <QWheelEvent>

#include "pixeldisplay.h"

#include "menu_top.h"
#include "guiGraphCommon.h"     // LCD size definitions


QSignalMapper *signalMapper;
MainWindow* pt2Myself;        // Global variable which points to this.
                              // Used for C callbacks.
QTimer updateTimer;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->PixelDisplay1->setImageSize(LCD_XSIZE,LCD_YSIZE);
    ui->PixelDisplay2->setImageSize(LCD_XSIZE,LCD_YSIZE);

    ui->PixelDisplay1->setScale(2.0);
    ui->PixelDisplay2->setScale(2.0);

    if (ui->updateCheckBox->checkState())
    {
        updateTimer.start(ui->updateSpinBox->value());
    }

    // Signals and slots mapping
    signalMapper = new QSignalMapper(this);
    signalMapper->setMapping(ui->actionX1, 1);
    signalMapper->setMapping(ui->actionX2, 2);
    signalMapper->setMapping(ui->actionX3, 3);
    signalMapper->setMapping(ui->actionX4, 4);
    signalMapper->setMapping(ui->actionX5, 5);

    connect(ui->actionX1, SIGNAL(triggered()), signalMapper, SLOT (map()));
    connect(ui->actionX2, SIGNAL(triggered()), signalMapper, SLOT (map()));
    connect(ui->actionX3, SIGNAL(triggered()), signalMapper, SLOT (map()));
    connect(ui->actionX4, SIGNAL(triggered()), signalMapper, SLOT (map()));
    connect(ui->actionX5, SIGNAL(triggered()), signalMapper, SLOT (map()));

    connect(signalMapper, SIGNAL(mapped(const int &)),
            this, SLOT(on_viewScale_changed(const int &)));

    connect(ui->updateButton,SIGNAL(clicked()),this,  SLOT(on_LCD_update()));
    connect(&updateTimer,SIGNAL(timeout()),this,SLOT(on_LCD_update()));

//    connect()

    // This does shrinking of a form when inner widgets are resized
    //layout()->setSizeConstraint(QLayout::SetFixedSize);

    pt2Myself = this;
    registerLogCallback((cbFuncPtr)&MainWindow::addLogWrapper);
    registerLcdUpdateCallback((cbLcdUpdatePtr)&MainWindow::updateDisplayWrapper);
    guiInitialize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//-----------------------------------//
//  Logging
// http://en.wikipedia.org/wiki/Template%3AUnicode_chart_Arrows

void MainWindow::addLogMessage(int type, char *string)
{
    QString msg;
    switch(type)
    {
        case LOG_FROM_TOP:
            ui->textEdit->setTextColor( QColor( "blue" ) );
            msg = QString::fromUtf8("\u21D3");
            //msg = "v";
            break;
        case LOG_FROM_BOTTOM:
            ui->textEdit->setTextColor( QColor( "red" ) );
            msg = QString::fromUtf8("\u21D1");
            //msg = "^";
            break;
        default:
            ui->textEdit->setTextColor( QColor( "black" ) );
            msg = "?";
            break;
    }
    msg += " ";
    msg += string;
    ui->textEdit->append(msg);
}



//-----------------------------------//
// C-functions callbacks
// Since such methods must be declared as static,
// we use pointer to object (this) to access non-static members

// Callback function for log message add
void MainWindow::addLogWrapper(int type, char *string)
{
    pt2Myself->addLogMessage(type, string);
}

// Callback function for LCD update
void MainWindow::updateDisplayWrapper(int display, uint16_t *buffer)
{
    if (display == 0)
        pt2Myself->ui->PixelDisplay1->updateImage(buffer);
    else
        pt2Myself->ui->PixelDisplay2->updateImage(buffer);
}



void MainWindow::on_LCD_update()
{
    guiDrawAll();
}

void MainWindow::on_viewScale_changed(const int scale)
{
    ui->PixelDisplay1->setScale(scale);
    ui->PixelDisplay2->setScale(scale);
    QTimer::singleShot(5, this, SLOT(shrink()));
}

void MainWindow::shrink()
{
   resize(0, 0);
}

void MainWindow::on_updateCheckBox_clicked()
{
    if (ui->updateCheckBox->checkState())
        updateTimer.start(ui->updateSpinBox->value());
    else
        updateTimer.stop();
}

void MainWindow::on_pushButton_esc_clicked()
{
    guiButtonClicked((1<<8));
    if (ui->checkBox_updMode->checkState())
        on_LCD_update();

}
void MainWindow::on_pushButton_left_clicked()
{
    guiButtonClicked((1<<9));
    if (ui->checkBox_updMode->checkState())
        on_LCD_update();
}

void MainWindow::on_pushButton_right_clicked()
{
    guiButtonClicked((1<<10));
    if (ui->checkBox_updMode->checkState())
        on_LCD_update();
}

void MainWindow::on_pushButton_ok_clicked()
{
    guiButtonClicked((1<<11));
    if (ui->checkBox_updMode->checkState())
        on_LCD_update();
}


void MainWindow::wheelEvent ( QWheelEvent * event )
{
    guiEncoderRotated(event->delta()/120 );
    if (ui->checkBox_updMode->checkState())
        on_LCD_update();
}
