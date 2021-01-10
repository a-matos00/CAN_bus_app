#include "recieveFrames.h"
#include <QCanBus>
#include <QCanBusDevice>
#include <QCanBusFrame>
#include "comboboxmodel.h"
#include <QQmlEngine>
#include <qqmlcontext.h>

recieveFrames::recieveFrames(QObject *parent) : QObject(parent)
{
    m_device = QCanBus::instance()->createDevice("socketcan", "vcan0");
    m_device->connectDevice();
    connect(m_device, &QCanBusDevice::framesReceived, this, &recieveFrames::displayFrame);
}

void recieveFrames::displayFrame() {

    frame = m_device->readFrame();
    QString frame_string = frame.toString();
    emit signalFrame(frame_string); // send recieved signal from c++ to QML

   return;
}
