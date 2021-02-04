#include "SendData.h"
#include <QCanBus>
#include <QCanBusDeviceInfo>
#include <QList>
#include <QByteArray>

SendData::SendData(QObject *parent) :
QObject(parent)
{
    device_list = QCanBus::instance()->availableDevices("socketcan");   //update node list
}

void SendData::sendMessage(QString arg_id, QByteArray arg_data)
{
    bool ok = true;
    ID = arg_id.toInt(&ok, 16);
    arg_data.replace(" ","");    //removes spaces from the user input

    m_frame.setFrameId(ID);   //argument is of type int
    m_payload = QByteArray::fromHex(arg_data);
    m_frame.setPayload(m_payload);

    for (const QCanBusDeviceInfo &info : qAsConst(device_list)) //iterate through device info list
    {
        m_device = QCanBus::instance()->createDevice(QStringLiteral("socketcan"), info.name());
        m_device->connectDevice();
        m_device->writeFrame(m_frame);
    }
}
