#include "gpio_handler.h"
#include "GPIO_pin.h"
#include<QDebug>

#define HIGH 1
#define LOW 0

GPIO_handler::GPIO_handler(QObject *parent) : QObject(parent)
{
     m_pin1 = new GPIO_pin(1, "in", HIGH);  //initialize pin1

     connect(m_pin1, SIGNAL(pinValueChanged()), this, SLOT(PinValueChangedSlot()));
}

void GPIO_handler::PinValueChangedSlot()
{
    GPIO_pin* sender_pin = qobject_cast<GPIO_pin*>(sender());   //gets the pointer to the signal sender PIN
    int pinNum = sender_pin->m_pinNumber;
    int pinValue = sender_pin->m_value;

    emit signal(pinNum, pinValue);
    qDebug()<<"GPIO HANDLER SIGNALING";

}

GPIO_handler::~GPIO_handler(){
    delete m_pin1;
}
