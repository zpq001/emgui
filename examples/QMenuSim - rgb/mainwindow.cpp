#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSignalMapper.h>
#include <QTimer.h>
#include <QWheelEvent>
#include <QLabel>
#include <QTime>

#include "pixeldisplay.h"

#include "guiTop.h"



// Internal button codes
enum buttons {
    BTN_ESC,
    BTN_LEFT,
    BTN_RIGHT,
    BTN_UP,
    BTN_DOWN,
    BTN_OK
};


QSignalMapper *viewSignalMapper;
QSignalMapper *btnPressSignalMapper;
QSignalMapper *btnReleaseSignalMapper;

MainWindow* pt2Myself;        // Global variable which points to this.
                              // Used for C callbacks.
QTimer updateTimer;
QTimer secondsTimer;
QTime t;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->PixelDisplay1->setSize(DISPLAY_XSIZE,DISPLAY_YSIZE);
    ui->PixelDisplay1->setScale(2.0);
    //ui->PixelDisplay1->setDataEncoding(PixelDisplay::MONOCHROME_3310_8bit);
    ui->PixelDisplay1->setDataEncoding(PixelDisplay::RGB_888_32bit);


    // View
    viewSignalMapper = new QSignalMapper(this);
    viewSignalMapper->setMapping(ui->actionX1, 1);
    viewSignalMapper->setMapping(ui->actionX2, 2);
    viewSignalMapper->setMapping(ui->actionX3, 3);
    viewSignalMapper->setMapping(ui->actionX4, 4);
    viewSignalMapper->setMapping(ui->actionX5, 5);
    connect(ui->actionX1, SIGNAL(triggered()), viewSignalMapper, SLOT (map()));
    connect(ui->actionX2, SIGNAL(triggered()), viewSignalMapper, SLOT (map()));
    connect(ui->actionX3, SIGNAL(triggered()), viewSignalMapper, SLOT (map()));
    connect(ui->actionX4, SIGNAL(triggered()), viewSignalMapper, SLOT (map()));
    connect(ui->actionX5, SIGNAL(triggered()), viewSignalMapper, SLOT (map()));
    connect(viewSignalMapper, SIGNAL(mapped(const int &)), this, SLOT(on_viewScale_changed(const int &)));

    // Control buttons press
    btnPressSignalMapper = new QSignalMapper(this);
    btnPressSignalMapper->setMapping(ui->pushButton_esc, BTN_ESC);
    btnPressSignalMapper->setMapping(ui->pushButton_left, BTN_LEFT);
    btnPressSignalMapper->setMapping(ui->pushButton_right, BTN_RIGHT);
    btnPressSignalMapper->setMapping(ui->pushButton_ok, BTN_OK);
    connect(ui->pushButton_esc, SIGNAL(pressed()), btnPressSignalMapper, SLOT(map()));
    connect(ui->pushButton_left, SIGNAL(pressed()), btnPressSignalMapper, SLOT(map()));
    connect(ui->pushButton_right, SIGNAL(pressed()), btnPressSignalMapper, SLOT(map()));
    connect(ui->pushButton_ok, SIGNAL(pressed()), btnPressSignalMapper, SLOT(map()));
    connect(btnPressSignalMapper, SIGNAL(mapped(const int &)), this, SLOT(on_ControlButtonPress(const int &)));

    // Control buttons release
    btnReleaseSignalMapper = new QSignalMapper(this);
    btnReleaseSignalMapper->setMapping(ui->pushButton_esc, BTN_ESC);
    btnReleaseSignalMapper->setMapping(ui->pushButton_left, BTN_LEFT);
    btnReleaseSignalMapper->setMapping(ui->pushButton_right, BTN_RIGHT);
    btnReleaseSignalMapper->setMapping(ui->pushButton_ok, BTN_OK);
    connect(ui->pushButton_esc, SIGNAL(pressed()), btnReleaseSignalMapper, SLOT(map()));
    connect(ui->pushButton_left, SIGNAL(pressed()), btnReleaseSignalMapper, SLOT(map()));
    connect(ui->pushButton_right, SIGNAL(pressed()), btnReleaseSignalMapper, SLOT(map()));
    connect(ui->pushButton_ok, SIGNAL(pressed()), btnReleaseSignalMapper, SLOT(map()));
    connect(btnReleaseSignalMapper, SIGNAL(mapped(const int &)), this, SLOT(on_ControlButtonRelease(const int &)));






    connect(ui->updateButton,SIGNAL(clicked()),this,  SLOT(on_LCD_update()));
    connect(&updateTimer,SIGNAL(timeout()),this,SLOT(on_LCD_update()));
    connect(&secondsTimer,SIGNAL(timeout()),this,SLOT(on_secondsTimer()));

    connect(ui->PixelDisplay1, SIGNAL(touchMove()), this, SLOT(on_touchMove()) );
    connect(ui->PixelDisplay1, SIGNAL(touchPress()), this, SLOT(on_touchPress()) );
    connect(ui->PixelDisplay1, SIGNAL(touchRelease()), this, SLOT(on_touchRelease()) );


    qApp->installEventFilter( this );


    // This does shrinking of a form when inner widgets are resized
    //layout()->setSizeConstraint(QLayout::SetFixedSize);

    pt2Myself = this;
    registerLogCallback((cbLogPtr)&MainWindow::addLogWrapper);
    registerLcdUpdateCallback((cbLcdUpdatePtr)&MainWindow::updateDisplayWrapper);
    guiInitialize();

    // Start seconds timer
    secondsTimer.start(1000);

    // Start update timer
    if (ui->updateCheckBox->checkState())
    {
        updateTimer.start(ui->updateSpinBox->value());
    }
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
    if (ui->checkBox_logEnable->checkState())
    {
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
void MainWindow::updateDisplayWrapper(uint16_t *buffer)
{
    pt2Myself->ui->PixelDisplay1->updateDisplay(buffer);
}


void MainWindow::on_LCD_update()
{
    guiDrawAll();
}

void MainWindow::on_viewScale_changed(const int scale)
{
    ui->PixelDisplay1->setScale(scale);
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

void MainWindow::updateStatusBar(void)
{
    QString touchPressStatus = (ui->PixelDisplay1->touchState.isPressed) ? "Pressed" : "Released";
    QString touchStatus = QString("Touch panel x = %1; y = %2; state = %3")
        .arg(ui->PixelDisplay1->touchState.x).arg(ui->PixelDisplay1->touchState.y).arg(touchPressStatus);
    ui->statusBar->showMessage(touchStatus);
}


//-----------------------------------//
// Touch panel events

void MainWindow::on_touchMove(void)
{
    updateStatusBar();
    if (ui->PixelDisplay1->touchState.isPressed)
    {
        guiTouchMoved(ui->PixelDisplay1->touchState.x, ui->PixelDisplay1->touchState.y);
        if (ui->checkBox_updMode->checkState())
            on_LCD_update();
    }
}

void MainWindow::on_touchPress(void)
{
    updateStatusBar();
    guiTouchPressed(ui->PixelDisplay1->touchState.x, ui->PixelDisplay1->touchState.y);
    if (ui->checkBox_updMode->checkState())
        on_LCD_update();
}

void MainWindow::on_touchRelease(void)
{
    updateStatusBar();
    guiTouchReleased(ui->PixelDisplay1->touchState.x, ui->PixelDisplay1->touchState.y);
    if (ui->checkBox_updMode->checkState())
        on_LCD_update();
}



//-----------------------------------//
// Button and encoder events

void MainWindow::on_ControlButtonPress(int btn)
{
    switch(btn)
    {
        case BTN_ESC:
            guiButtonPressed(KEY_ESC);
            break;
        case BTN_LEFT:
            guiButtonPressed(KEY_LEFT);
            break;
        case BTN_RIGHT:
            guiButtonPressed(KEY_RIGHT);
            break;
        case BTN_OK:
            guiButtonPressed(KEY_OK);
            break;
    }
    if (ui->checkBox_updMode->checkState())
        on_LCD_update();
}

void MainWindow::on_ControlButtonRelease(int btn)
{
    switch(btn)
    {
        case BTN_ESC:
            guiButtonReleased(KEY_ESC);
            break;
        case BTN_LEFT:
            guiButtonReleased(KEY_LEFT);
            break;
        case BTN_RIGHT:
            guiButtonReleased(KEY_RIGHT);
            break;
        case BTN_OK:
            guiButtonReleased(KEY_OK);
            break;
    }
    if (ui->checkBox_updMode->checkState())
        on_LCD_update();
}





// Filter should be set on qApp
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>( event );
        if (on_keyPress(keyEvent))
            return true;
    }
    if (event->type() == QEvent::KeyRelease)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>( event );
        if (on_keyRelease(keyEvent))
            return true;
    }
    if ( (event->type() == QEvent::Wheel) && (obj != ui->textEdit))     // FIXME - obj
    {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent*>( event );
        on_wheelEvent(wheelEvent);
        return true;
    }
    return QMainWindow::eventFilter( obj, event );
}


bool MainWindow::on_keyPress(QKeyEvent *event)
{
    bool eventIsHandled = true;
    switch(event->key())
    {
        case Qt::Key_Escape:
        case Qt::Key_Backspace:
            on_ControlButtonPress(BTN_ESC);
            break;
        case Qt::Key_Left:
            on_ControlButtonPress(BTN_LEFT);
            break;
        case Qt::Key_Right:
            on_ControlButtonPress(BTN_RIGHT);
            break;
        case Qt::Key_Return:
        case Qt::Key_Space:
            on_ControlButtonPress(BTN_OK);
            break;
        default:
            eventIsHandled = false;
    }
    return eventIsHandled;
}

bool MainWindow::on_keyRelease(QKeyEvent *event)
{
    bool eventIsHandled = true;
    // ....

    eventIsHandled = false;
    return eventIsHandled;
}


void MainWindow::on_wheelEvent(QWheelEvent * event)
{
    guiEncoderRotated(event->delta()/120 );
    if (ui->checkBox_updMode->checkState())
        on_LCD_update();
}



void MainWindow::on_secondsTimer(void)
{
    t.start();
    guiUpdateTime(t.hour(),t.minute(),t.second());
    if (ui->checkBox_updMode->checkState())
        on_LCD_update();
}
