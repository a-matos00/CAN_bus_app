#include "gpio_handler.h"
#include "GPIO_pin.h"
#include<QDebug>
#include<unistd.h>
#include<fcntl.h>

#define HIGH 1
#define LOW 0

GPIO_handler::GPIO_handler(QObject *parent) : QObject(parent)
{
     m_pin1 = new GPIO_pin(1, "in", HIGH);  //initialize pin1

     connect(m_pin1->m_FW, SIGNAL(fileChanged(QString)), this, SLOT(PinValueFileRead()));
}

void GPIO_handler::PinValueFileRead()
{
    GPIO_pin* sender_pin = qobject_cast<GPIO_pin*>(sender()->parent());   //gets the pointer to the signal sender PIN

    //LOW LEVEL C file read(radi na linuxu)
    int fd = open("/home/andrija/datoteka.txt", O_RDONLY);
    char c;
    read(fd, &c, 1);
    close(fd);

    //fali uvjet ako je promjena
    if( c == '0')
       sender_pin->m_value = 0;
    else if(c == '1')
        sender_pin->m_value = 1;

    if (QFile::exists("/home/andrija/datoteka.txt")) {  //IMPORTANT!
       sender_pin->m_FW->addPath("/home/andrija/datoteka.txt");
    }

    emit  signalPinValChange(sender_pin->m_pinNumber, sender_pin->m_value);
    qDebug()<<"GPIO HANDLER FILE READ";

}

void GPIO_handler::exportPin(GPIO_pin* pin)
{
}


void GPIO_handler::changePinValue()
{

}

GPIO_handler::~GPIO_handler(){
    delete m_pin1;
}
