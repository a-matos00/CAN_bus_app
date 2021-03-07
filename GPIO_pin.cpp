#include "GPIO_pin.h"
#include <QtDebug>
#include <QFile>
#include<QFileSystemWatcher>
#include <fcntl.h>  //za file descriptor open funkciju

#define HIGH 1
#define LOW 0

GPIO_pin::GPIO_pin(int a_pinNumber, QString a_pinType, int a_initVal, QObject *parent) : QObject(parent)
{
    m_pinNumber = a_pinNumber;
    m_value = a_initVal;    //set initial value

    if(a_pinType == "in" || a_pinType == "out"){
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

    m_FW = new QFileSystemWatcher;
    m_FW->addPath("/home/andrija/datoteka.txt");  //watch for changes in value file

    /*m_FD = open("/home/andrija/datoteka.txt", O_RDONLY|O_NONBLOCK);
       if (m_FD ==  -1) {
           perror("Unable to open /home/andrija/datoteka.txt");
           exit(1);
       }
    */
    qDebug()<<"Pin "<<m_pinNumber<<"Type: "<<m_pinType<<" Default value: "<<m_value<<" PATH: "<<m_pathGPIO;

    //connect signal to slot
    connect(m_FW, SIGNAL(fileChanged(QString)), this, SLOT(valueChange()));
}

void GPIO_pin::valueChange()
{
    if (QFile::exists("/home/andrija/datoteka.txt")) {  //IMPORTANT!
        m_FW->addPath("/home/andrija/datoteka.txt");
    }

    emit pinValueChanged();

    qDebug()<<"Value FILE update!";
}

GPIO_pin::~GPIO_pin(){

}
