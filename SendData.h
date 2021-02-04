#ifndef SENDATA_H
#define SENDATA_H

#include <QObject>
#include <QCanBusDeviceInfo>
#include <QCanBusFrame>
#include <QCanBusDevice>

class SendData : public QObject
{
Q_OBJECT
public:
    explicit SendData(QObject *parent = 0); //constructor
    QList<QCanBusDeviceInfo>device_list;   //will contain available CAN devices
    int ID;
    QCanBusFrame m_frame;
    QByteArray m_payload;
    QCanBusDevice *m_device;
    Q_INVOKABLE void sendMessage(QString arg_id, QByteArray arg_data);

signals:

public slots:

};

#endif // SENDATA_H
