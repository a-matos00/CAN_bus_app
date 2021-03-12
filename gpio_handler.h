#ifndef GPIO_HANDLER_H
#define GPIO_HANDLER_H

#include <QObject>
#include "GPIO_pin.h"
#include "counter.h"

class GPIO_handler : public QObject
{
    Q_OBJECT
public:
    explicit GPIO_handler(QObject *parent = nullptr);
    static bool setPinValue(GPIO_pin*, int);
    static void setPinDirection(GPIO_pin*, QString);
    static bool exportPin(GPIO_pin*);
    static void unexportPin(GPIO_pin*);
    static void configurePinFilePaths(GPIO_pin*);
    static bool setPinNumber(GPIO_pin*, int);
    static void resetFileWatcher(GPIO_pin*);
    ~GPIO_handler();

    //---PIN INITIALIZATION--- (Initialize pointers to all gpio pins that will be used)
    GPIO_pin* m_pin1;
    counter m_pressCounter; //FOR TESTING

signals:
    void signalPinValChange(int pin, int value, float x);   //called from GPIO handler, sent to QML

public slots:
    void PinValueFileRead(); //connected to pin signal
};

#endif // GPIO_HANDLER_H
