#ifndef GPIO_HANDLER_H
#define GPIO_HANDLER_H

#include <QObject>
#include<GPIO_pin.h>

class GPIO_handler : public QObject
{
    Q_OBJECT
public:
    explicit GPIO_handler(QObject *parent = nullptr);
    void changePinValue();
    void exportPin(GPIO_pin*);
    ~GPIO_handler();
    GPIO_pin* m_pin1;


signals:
     void signalPinValChange(int pin, int value);   //called from GPIO handler, sent to QML

public slots:
    void PinValueFileRead(); //connected to pin signal
};

#endif // GPIO_HANDLER_H
