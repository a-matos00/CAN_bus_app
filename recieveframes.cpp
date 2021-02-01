#include "recieveFrames.h"
#include <QCanBus>
#include <QCanBusDevice>
#include <QCanBusFrame>
#include "comboboxmodel.h"
#include <QDebug>
#include <QtEndian>

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
    QByteArray hex_full = payload.toHex();   //convert payload to byte array to hex
    QByteArray temp = hex_full.left(4);
    QByteArray swap1 = temp.right(2);
    QByteArray swap2 = temp.left(2);
    QByteArray hex_kph;

    hex_kph.append(swap1);
    hex_kph.append(swap2);

    bool ok2;
    quint16 value = static_cast<short>(hex_kph.toUShort(&ok2, 16));

    quint32 id = arg_frame.frameId();
    QString id_string = QByteArray::number( id, 16 );    //convert from decimal to hex
    qInfo()<<"frame id: "<<id_string<<" FULL DATA: "<<hex_full<<" KPH HEX "<<hex_kph<<" SPEED: "<<value;  //FRAME ID CONVERSION MISSING
}
