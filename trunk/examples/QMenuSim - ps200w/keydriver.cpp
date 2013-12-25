

#include <QTimer>
#include <QSignalMapper>

#include "keydriver.h"


QSignalMapper *timerSignalMapper;

keyDriver::keyDriver(QObject *parent, int keyCount) :
    QObject(parent)
{
    this->keyCount = keyCount;
    this->timers = new QTimer[keyCount];
    this->key_states = new int[keyCount];

    timerSignalMapper = new QSignalMapper(this);
    for (int i=0; i<keyCount; i++)
    {
        timerSignalMapper->setMapping(&timers[i], i);
        connect(&timers[i], SIGNAL(timeout()), timerSignalMapper, SLOT (map()));
        timers[i].setInterval(300);
        key_states[i] = KEY_RELEASED;
    }
    connect(timerSignalMapper, SIGNAL(mapped(const int &)), this, SLOT(onTimerTimeout(const int &)));
}


void keyDriver::onTimerTimeout(int id)
{

}

void keyDriver::keyPress(int id)
{
    switch(key_states[id])
    {
        case KEY_RELEASED:
            key_states[id] = KEY_PRESSED;
            //timers[id].start();
            emit onActionDown(id);
        break;
        case KEY_PRESSED:
            // forbidden state - do nothing
        break;
    }

}

void keyDriver::keyRelease(int id)
{
    switch(key_states[id])
    {
        case KEY_PRESSED:
            key_states[id] = KEY_RELEASED;
            //timers[id].stop();
            emit onActionUp(id);
        break;
        case KEY_RELEASED:
            // forbidden state - do nothing
        break;
    }
}
