#include "gpio_handler.h"
#include "GPIO_pin.h"
#include<QDebug>
#include<unistd.h>
#include<fcntl.h>

#define HIGH 1
#define LOW 0

GPIO_handler::GPIO_handler(QObject *parent) : QObject(parent)
{
    //---PIN DECLARATION--- (create pin objects)
    m_pin1 = new GPIO_pin(1, "in", HIGH);  //initialize pin1

     connect(m_pin1->m_FW, SIGNAL(fileChanged(QString)), this, SLOT(PinValueFileRead()));   //connect pin value file wathcher
}

void GPIO_handler::PinValueFileRead()   //slot
{
    GPIO_pin* sender_pin = qobject_cast<GPIO_pin*>(sender()->parent());   //gets the pointer to the signal sender PIN

    const char* path = qPrintable(sender_pin->m_pathValue);   //convert QString to const char*
    int fd = open(path, O_RDONLY);
    char c;
    read(fd, &c, 1);
    close(fd);
    int read_val = c - '0'; // c - '0' converts digit to int(ascii)

    if( read_val != sender_pin->m_value)    //if the pin value changed
        setPinValue(sender_pin, read_val);

    if (QFile::exists(path)) {  //reset the file watcher(important!)
       sender_pin->m_FW->addPath(path);
    }

    emit  signalPinValChange(sender_pin->m_pinNumber, sender_pin->m_value); //signal for QML
}

 void GPIO_handler::setPinDirection(GPIO_pin* pin, QString direction)   //static function
 {
     const char* path = qPrintable(pin->m_pathDirection);   //convert QString to const char*
     int fd = open(path, O_WRONLY);
     if(fd == -1){
         qDebug()<<"Error opening file: "<<path;
         return;
     }

     const char* direction_str = qPrintable(direction);

     write(fd, direction_str, strlen(direction_str));  //write to value file
     close(fd);

    pin->m_pinType = direction;

 }

void GPIO_handler::exportPin(GPIO_pin* pin)
{
    const char* path = qPrintable(pin->m_pathExport);   //convert QString to const char*
    int fd = open(path, O_WRONLY);
    if(fd == -1){
        qDebug()<<"Error opening file: "<<path;
        return;
    }

    QString temp = QString::number(pin->m_pinNumber);   //convert pin number to string
    const char* pinNumberStr = qPrintable(temp);

    write(fd, pinNumberStr, strlen(pinNumberStr));  //write to export file
    close(fd);
}

void GPIO_handler::unexportPin(GPIO_pin* pin)
{
    const char* path = qPrintable(pin->m_pathUnexport);   //convert QString to const char*
    int fd = open(path, O_WRONLY);
    if(fd == -1){
        qDebug()<<"Error opening file: "<<path;
        return;
    }

    QString temp = QString::number(pin->m_pinNumber);   //convert pin number to string
    const char* pinNumberStr = qPrintable(temp);

    write(fd, pinNumberStr, strlen(pinNumberStr));  //write to unexport file
    close(fd);
}


void GPIO_handler::setPinValue(GPIO_pin* pin, int new_value)
{
    const char* path = qPrintable(pin->m_pathValue);   //convert QString to const char*
    int fd = open(path, O_WRONLY);
    if( fd == -1){
        qDebug()<<"Unable to open file: "<<pin->m_pathValue;
        return;
    }

    QString temp = QString::number(new_value);   //convert pin number to string
    const char* value_str = qPrintable(temp);

    write(fd, value_str, strlen(value_str));  //write to value file
    close(fd);

    pin->m_value = new_value;   //record change in virtual pin
}

GPIO_handler::~GPIO_handler(){
    delete m_pin1;
}
