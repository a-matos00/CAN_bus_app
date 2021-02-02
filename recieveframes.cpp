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
    quint32 id = arg_frame.frameId();
     QString id_string = QByteArray::number( id, 16 );    //convert from decimal to hex
    qInfo()<<"ID ======>"<<id_string;
    QByteArray payload = arg_frame.payload();   //extract payload from full message

    if(id_string == "2000"){
        parseRPM(payload);
    }

    if(id_string == "2001"){
        parseKPH(payload);
    }
}

void recieveFrames::parseKPH(QByteArray payload)
{
    QByteArray hex_full = payload.toHex();   //convert payload to hex

    QByteArray temp = hex_full.mid(8,4);    //cutout the kph speed
    QByteArray swap1 = temp.right(2);
    QByteArray swap2 = temp.left(2);
    QByteArray hex_kph;
    float kph_factor = 0.1;

    hex_kph.append(swap1);  //byte swap
    hex_kph.append(swap2);

    bool ok2;
    quint16 kph_raw = static_cast<short>(hex_kph.toUShort(&ok2, 16));   //convert hex to uint16

    float kph = (float)kph_raw * kph_factor;    //get real kph value

     QString display = QString::number(kph);
     emit signalKPH(display); // send recieved signal from c++ to QML

    qInfo()<<" FULL DATA: "<<hex_full<<" KPH HEX "<<hex_kph<<" KPH: "<<kph;
}

void recieveFrames::parseRPM(QByteArray payload)
{
    QByteArray hex_full = payload.toHex();   //convert payload to hex

    QByteArray temp = hex_full.left(4);
    QByteArray swap1 = temp.right(2);
    QByteArray swap2 = temp.left(2);
    QByteArray hex_rpm;

    hex_rpm.append(swap1);
    hex_rpm.append(swap2);

    bool ok2;
    quint16 rpm = static_cast<short>(hex_rpm.toUShort(&ok2, 16));

    QString display = QString::number(rpm);
    emit signalRPM(display); // send recieved signal from c++ to QML

    qInfo()<<" FULL DATA: "<<hex_full<<" rpm HEX "<<hex_rpm<<" RPM: "<<rpm;
}
