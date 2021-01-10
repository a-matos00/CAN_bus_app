#ifndef CUSTOMDEVICE_H
#define CUSTOMDEVICE_H

#include <QObject>
#include<QCanBus>
#include<QCanBusDevice>

class customDevice : public QObject
{
    Q_OBJECT
public:
    explicit customDevice(QObject *parent = nullptr);

    QCanBusDevice *device;

signals:

public slots:
    void display();
};

#endif // CUSTOMDEVICE_H
