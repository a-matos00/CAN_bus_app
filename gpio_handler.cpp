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

void GPIO_handler::PinValueChangedSlot(){
    emit signal();
    qDebug()<<"GPIO HANDLER SIGNALING";

}
GPIO_handler::~GPIO_handler(){
    delete m_pin1;
}
