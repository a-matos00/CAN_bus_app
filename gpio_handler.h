#ifndef GPIO_HANDLER_H
#define GPIO_HANDLER_H

#include <QObject>
#include<GPIO_pin.h>

class GPIO_handler : public QObject
{
    Q_OBJECT
public:
    explicit GPIO_handler(QObject *parent = nullptr);
    ~GPIO_handler();
    GPIO_pin* m_pin1;


signals:
     void signal(int pin, int value);   //called from GPIO handler, sent to QML

public slots:
    void PinValueChangedSlot(); //connected to pin
};

#endif // GPIO_HANDLER_H
