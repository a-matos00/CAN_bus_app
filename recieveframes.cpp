#include "recieveFrames.h"
#include <QCanBus>
#include <QCanBusDevice>
#include <QCanBusFrame>
#include "comboboxmodel.h"
#include <QDebug>

recieveFrames::recieveFrames(QObject *parent) : QObject(parent)
{
    device_list = QCanBus::instance()->availableDevices("socketcan");   //update node list

    if(device_list.isEmpty())return;

    //assign node for listening to the network
    device = QCanBus::instance()->createDevice(QStringLiteral("socketcan"),
                                               device_list[0].name());
    device->connectDevice();
    //connect signal to slot
    connect(device, &QCanBusDevice::framesReceived, this, &recieveFrames::displayFrame);
}

//slot for framesRecieved() signal
void recieveFrames::displayFrame() {

    frame = device->readFrame();
    QString frame_string = frame.toString();
    emit signalFrame(frame_string); // send recieved signal from c++ to QML
    parseMessage(frame);
}

void recieveFrames::parseMessage(QCanBusFrame arg_frame)
{
    QByteArray payload = arg_frame.payload();
    quint32 id = arg_frame.frameId();
    qInfo()<<"frame id: "<<id<<" DATA: "<<payload;  //FRAME ID CONVERSION MISSING
}
