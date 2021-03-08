#include "GPIO_pin.h"
#include <QtDebug>
#include <QFile>
#include<QFileSystemWatcher>

#define HIGH 1
#define LOW 0

GPIO_pin::GPIO_pin(int a_pinNumber, QString a_pinType, int a_initVal, QObject *parent) : QObject(parent)
{
    m_pinNumber = a_pinNumber;  //set pin number
    m_value = a_initVal;    //set initial value

    if(a_pinType == "in" || a_pinType == "out"){    //set pin type (in/out)
        m_pinType = a_pinType;
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
    m_FW->setParent(this);  //important for pin value read GPIO handler function
    m_FW->addPath("/home/andrija/datoteka.txt");  //watch for changes in value file
    //m_FW->addPath("m_pathValue");  //watch for changes in value file
}


GPIO_pin::~GPIO_pin(){
    delete m_FW;
}
