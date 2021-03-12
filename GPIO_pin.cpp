#include "GPIO_pin.h"
#include <QtDebug>
#include<QFileSystemWatcher>
#include "gpio_handler.h"

GPIO_pin::GPIO_pin(int a_pinNumber, QString a_pinType, int a_initVal, QObject *parent) : QObject(parent)
{
    m_FW = new QFileSystemWatcher;

    if( !GPIO_handler::setPinNumber(this, a_pinNumber) )    //1. set pin number to allow file configuration
        return;

    GPIO_handler::configurePinFilePaths(this);  //2. configure all gpio pin system file path's

    if( !GPIO_handler::exportPin(this) )    //3. export pin(exit in faulire)
        return;

    GPIO_handler::setPinDirection(this, a_pinType); //4. set pin type (in/out)
    GPIO_handler::setPinValue(this, a_initVal);    //5. set initial value

    m_FW->setParent(this);  //important for pin value file read GPIO handler slot function
    m_FW->addPath(m_pathValue);  //watch for changes in value file
}

GPIO_pin::~GPIO_pin(){
    delete m_FW;

    if(m_exportStatus == true)
        GPIO_handler::unexportPin(this);
}
