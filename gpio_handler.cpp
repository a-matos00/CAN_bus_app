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

void GPIO_handler::PinValueFileRead()
{
    GPIO_pin* sender_pin = qobject_cast<GPIO_pin*>(sender()->parent());   //gets the pointer to the signal sender PIN

    //LOW LEVEL C file read(radi na linuxu)

    const char* path = qPrintable(sender_pin->m_pathValue);   //convert QString to const char*
    //int fd = open(path, O_RDONLY);
    int fd = open("/home/andrija/datoteka.txt", O_RDONLY);  //test
    char c;
    read(fd, &c, 1);
    close(fd);

    //fali uvjet ako je promjena
    if( c == '0')
       sender_pin->m_value = 0;
    else if(c == '1')
        sender_pin->m_value = 1;

    if (QFile::exists("/home/andrija/datoteka.txt")) {  //reset the file watcher(important!)
       sender_pin->m_FW->addPath("/home/andrija/datoteka.txt");
    }

    emit  signalPinValChange(sender_pin->m_pinNumber, sender_pin->m_value); //signal for QML
    qDebug()<<"GPIO HANDLER FILE READ";

}

void GPIO_handler::exportPin(GPIO_pin* pin)
{
    const char* path = qPrintable(pin->m_pathExport);   //convert QString to const char*
    int fd = open(path, O_WRONLY);
    //ERROR STATEMENT MISSING!!!

    QString temp = QString::number(pin->m_pinNumber);   //convert pin number to string
    const char* pinNumberStr = qPrintable(temp);

    write(fd, pinNumberStr, strlen(pinNumberStr));  //write to export file
    close(fd);
}

void GPIO_handler::unexportPin(GPIO_pin* pin)
{
    const char* path = qPrintable(pin->m_pathUnexport);   //convert QString to const char*
    int fd = open(path, O_WRONLY);
    //ERROR STATEMENT MISSING!!!

    QString temp = QString::number(pin->m_pinNumber);   //convert pin number to string
    const char* pinNumberStr = qPrintable(temp);

    write(fd, pinNumberStr, strlen(pinNumberStr));  //write to export file
    close(fd);
}


void GPIO_handler::setPinValue(GPIO_pin* pin, int new_value)
{
    const char* path = qPrintable(pin->m_pathValue);   //convert QString to const char*
    int fd = open(path, O_WRONLY);
    //ERROR STATEMENT MISSING!!!

    QString temp = QString::number(new_value);   //convert pin number to string
    const char* value_str = qPrintable(temp);

    write(fd, value_str, strlen(value_str));  //write to export file
    close(fd);
}

GPIO_handler::~GPIO_handler(){
    delete m_pin1;
}
