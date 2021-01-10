#include "recieveFrames.h"
#include <QCanBus>
#include <QCanBusDevice>
#include <QCanBusFrame>

recieveFrames::recieveFrames(QObject *parent) : QObject(parent)
{
    m_device = QCanBus::instance()->createDevice("socketcan", "vcan0");
    m_device->connectDevice();
    connect(m_device, &QCanBusDevice::framesReceived, this, &recieveFrames::funkcija);
}

void recieveFrames::funkcija() {
    qDebug() << "[Frame received] !";
    frame = m_device->readFrame();
    QString text = frame.toString();
    qInfo() << text;
    emit signalFrame(text); // send signal from c++ to qml

}
