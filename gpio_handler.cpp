#include "gpio_handler.h"
#include "GPIO_pin.h"
#include<QDebug>
#include<unistd.h>
#include<fcntl.h>
#include<QtGlobal>

#define HIGH 1
#define LOW 0

GPIO_handler::GPIO_handler(QObject *parent) : QObject(parent)
{
    //---PIN DECLARATION--- (create pin objects)
    m_pin1 = new GPIO_pin(16, "in", HIGH);  //initialize pin16

    //BUTTON PRESS COUNTER TESTING
    connect(this, SIGNAL(signalPinValChange(int,int, float)), &m_pressCounter, SLOT(increment()));

    if(m_pin1->m_exportStatus == true)
        connect(m_pin1->m_FW, SIGNAL(fileChanged(QString)), this, SLOT(PinValueFileRead()));   //connect pin value file wathcher
}

GPIO_handler::~GPIO_handler(){
    delete m_pin1;
}

void GPIO_handler::PinValueFileRead()   //slot
{
    GPIO_pin* sender_pin = qobject_cast<GPIO_pin*>(sender()->parent());   //gets the pointer to the signal sender PIN

    const char* path = qUtf8Printable(sender_pin->m_pathValue);   //convert QString to const char*
    int fd = open(path, O_RDONLY);
    if(fd == -1){
        qDebug()<<"Error opening file: "<<sender_pin->m_pathValue;
        return;
    }

    char c;
    read(fd, &c, 1);
    close(fd);
    int read_val = c - '0'; // c - '0' converts digit to int(ascii)

    if( setPinValue(sender_pin, read_val) == true)  ////FOR TESTING(only modifiy for real test, do not remove)
         emit  signalPinValChange(sender_pin->m_pinNumber, sender_pin->m_value, this->m_pressCounter.m_count + 0.5); //signal for QML
}

bool GPIO_handler::setPinValue(GPIO_pin* pin, int new_value)
{
    if( new_value != LOW && new_value != HIGH){
        qDebug()<<"Invalid value "<<new_value<<" for pin number: "<<pin->m_pinNumber;
        GPIO_handler::resetFileWatcher(pin);
        return false;
    }
    if( new_value == pin->m_value){
        qDebug()<<"No change in pin value!";
       GPIO_handler::resetFileWatcher(pin);
        return false;
    }

    const char* path = qUtf8Printable(pin->m_pathValue);   //convert QString to const char*
    int fd = open(path, O_WRONLY);
    if( fd == -1){
        qDebug()<<"Unable to open file: "<<pin->m_pathValue;
        return false;
    }

    QString temp = QString::number(new_value);   //convert pin number to string
    const char* value_str = qUtf8Printable(temp);

    write(fd, value_str, strlen(value_str));  //write to value file
    close(fd);

    pin->m_value = new_value;   //record change in virtual pin

    GPIO_handler::resetFileWatcher(pin);    //it is important to re-configure the file watcher after a file change report

    return true;
}

void GPIO_handler::resetFileWatcher(GPIO_pin* pin)
{
    if (QFile::exists(pin->m_pathValue)) {
      pin->m_FW->addPath(pin->m_pathValue);
    }
    else
        qDebug()<<"File "<<pin->m_pathValue<<" not found(not available for file watch)";
}

bool GPIO_handler::setPinNumber(GPIO_pin* pin, int a_number)
{
    if( a_number >= 0 && a_number <= 27)
        pin->m_pinNumber = a_number;  //set pin number
    else{
       qDebug()<<"Invalid pin number: "<<a_number<<" Aborting pin initialization";
       return false;
    }

    return true;
}

 void GPIO_handler::setPinDirection(GPIO_pin* pin, QString direction)   //static function
 {
     if(direction != "in" && direction != "out"){
        qDebug()<<"Invalid direction set for pin: "<<pin->m_pinNumber;
        return;
     }
     const char* path = qUtf8Printable(pin->m_pathDirection);   //convert QString to const char*
     int fd = open(path, O_WRONLY);
     if(fd == -1){
         qDebug()<<"Error opening file: "<<pin->m_pathDirection;
         return;
     }

     const char* direction_str = qUtf8Printable(direction);

     write(fd, direction_str, strlen(direction_str));  //write to value file
     close(fd);

     pin->m_pinType = direction;
 }

bool GPIO_handler::exportPin(GPIO_pin* pin)
{
    const char* path = qUtf8Printable(pin->m_pathExport);   //convert QString to const char*
    int fd = open(path, O_WRONLY);
    if(fd == -1){
        qDebug()<<"Error opening file: "<<path<<" Aborting pin "<<pin->m_pinNumber<<" initialization...";
        return false;
    }

    QString temp = QString::number(pin->m_pinNumber);   //convert pin number to string
    const char* pinNumberStr = qUtf8Printable(temp);

    write(fd, pinNumberStr, strlen(pinNumberStr));  //write to export file
    close(fd);

    pin->m_exportStatus = true;

    return true;
}

void GPIO_handler::unexportPin(GPIO_pin* pin)
{
    const char* path = qUtf8Printable(pin->m_pathUnexport);   //convert QString to const char*
    int fd = open(path, O_WRONLY);
    if(fd == -1){
        qDebug()<<"Error opening file: "<<path;
        return;
    }

    QString temp = QString::number(pin->m_pinNumber);   //convert pin number to string
    const char* pinNumberStr = qUtf8Printable(temp);

    write(fd, pinNumberStr, strlen(pinNumberStr));  //write to unexport file
    close(fd);

    pin->m_exportStatus = false;
}

 void GPIO_handler::configurePinFilePaths(GPIO_pin* pin)
 {  /*
     pin->m_pathGPIO  = "/sys/class/gpio/gpio" + QString::number(pin->m_pinNumber) + "/";
     pin->m_pathDirection = pin->m_pathGPIO + pin->m_pathDirection;
     pin->m_pathValue  = pin->m_pathGPIO + pin->m_pathValue;
     pin->m_pathExport  =pin->m_pathGPIO + pin->m_pathExport;
     pin->m_pathUnexport  = pin->m_pathGPIO + pin->m_pathUnexport;
    */
     //TEST
     pin->m_pathDirection = "/home/andrija/GPIO_test/direction.txt";
     pin->m_pathValue  = "/home/andrija/GPIO_test/value.txt";
     pin->m_pathExport  ="/home/andrija/GPIO_test/export.txt";
     pin->m_pathUnexport  = "/home/andrija/GPIO_test/unexport.txt";

 }


