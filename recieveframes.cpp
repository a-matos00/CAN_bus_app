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

QString recieveFrames::funkcija() {
    qDebug() << "[Frame received] !";
    frame = m_device->readFrame();
    QString text = frame.toString();
    qInfo() << text;
    emit signalData(text); // Signal from GAPI to QML

    return "aaaa";
}
