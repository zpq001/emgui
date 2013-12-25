#ifndef KEYDRIVER_H
#define KEYDRIVER_H

#include <QObject>
#include <QTimer>


typedef enum {KEY_PRESSED, KEY_RELEASED} keyState_t;
//typedef struct {
//} keyDescriptor_t;


class keyDriver : public QObject
{
    Q_OBJECT
    QTimer *timers;
    int *key_states;
    int keyCount;
    void onTimerTimeout(int id);

public:
    explicit keyDriver(QObject *parent = 0, int keyCount = 0);

signals:
    
    void onActionDown(int id);
    void onActionUp(int id);
    void onActionUpShort(int id);
    void onActionUpLong(int id);
    void onActionHold(int id);

public slots:

    void keyPress(int id);
    void keyRelease(int id);
    
};

#endif // KEYDRIVER_H
