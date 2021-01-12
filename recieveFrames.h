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
    QCanBusDevice *device;
    QCanBusFrame frame;
    QList<QCanBusDeviceInfo>device_list;   //will contain available CAN devices
signals:
    void signalFrame(QString data); //signal for qml

public slots:
    void displayFrame();

};

#endif // RECIEVEFRAMES_H
