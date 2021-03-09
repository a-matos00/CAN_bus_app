#include "GPIO_pin.h"
#include <QtDebug>
#include<QFileSystemWatcher>
#include "gpio_handler.h"

GPIO_pin::GPIO_pin(int a_pinNumber, QString a_pinType, int a_initVal, QObject *parent) : QObject(parent)
{
    if( !GPIO_handler::setPinNumber(this, a_pinNumber) )
        return;

    GPIO_handler::configurePinFilePaths(this);  //configure all gpio pin system file path's

    if( !GPIO_handler::exportPin(this) )    //export pin(exit in faulire)
        return;

    GPIO_handler::setPinDirection(this, a_pinType); //set pin type (in/out)
    GPIO_handler::setPinValue(this, a_initVal);    //set initial value


    m_FW = new QFileSystemWatcher;
    m_FW->setParent(this);  //important for pin value file read GPIO handler function
    m_FW->addPath("m_pathValue");  //watch for changes in value file
}

GPIO_pin::~GPIO_pin(){
    //delete m_FW;
}
