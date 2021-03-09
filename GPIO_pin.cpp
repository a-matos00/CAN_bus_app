#include "GPIO_pin.h"
#include <QtDebug>
#include<QFileSystemWatcher>
#include "gpio_handler.h"

#define HIGH 1
#define LOW 0

GPIO_pin::GPIO_pin(int a_pinNumber, QString a_pinType, int a_initVal, QObject *parent) : QObject(parent)
{
    if(a_pinNumber >= 0 && a_pinNumber <= 27)
        m_pinNumber = a_pinNumber;  //set pin number
    else{
       qDebug()<<"Invalid pin number: "<<a_pinNumber;
       return;
    }


    if( a_initVal == LOW || a_initVal == HIGH)
        m_value = a_initVal;    //set initial value
    else{
         qDebug()<<"Invalid value "<<a_initVal<<" for pin number: "<<a_pinNumber;
         return;
    }

    if(a_pinType == "in" || a_pinType == "out"){    //set pin type (in/out)
        GPIO_handler::setPinDirection(this, a_pinType);
    }
    else{
        qDebug()<<"Undefined pin type used for pin: "<< m_pinNumber;
        return;
    }

    //EXAMPLE GPIO PIN files folder PATH: "/sys/class/gpio/gpio2/"
    m_pathGPIO  = "/sys/class/gpio/gpio" + QString::number(a_pinNumber) + "/";
    m_pathDirection = m_pathGPIO + "direction";
    m_pathValue  = m_pathGPIO + "value";
    m_pathExport  ="/sys/class/gpio/export";
    m_pathUnexport  = "/sys/class/gpio/unexport";

    m_FW = new QFileSystemWatcher;
    m_FW->setParent(this);  //important for pin value file read GPIO handler function
    m_FW->addPath("m_pathValue");  //watch for changes in value file
}

GPIO_pin::~GPIO_pin(){
    delete m_FW;
}
