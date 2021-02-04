#ifndef RECIEVEFRAMES_H
#define RECIEVEFRAMES_H

#include <QObject>
#include<QCanBusDevice>
#include<QCanBusFrame>

class recieveFrames : public QObject
{
    Q_OBJECT
public:
    explicit recieveFrames(QObject *parent = nullptr);
    void parseMessage(QCanBusFrame);
    void parseRPM(QByteArray);
    void parseKPH(QByteArray);
    QCanBusDevice *m_device;
    QCanBusFrame m_frame;
    QList<QCanBusDeviceInfo>m_device_list;   //will contain available CAN devices
signals:
    void signalFrame(QString data); //signal for qml
    void signalRPM(QString data); //signal for qml
    void signalKPH(QString data); //signal for qml

public slots:
    void displayFrame();
};

#endif // RECIEVEFRAMES_H
