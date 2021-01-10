#ifndef RECIEVEFRAMES_H
#define RECIEVEFRAMES_H

#include <QObject>
#include <QCanBus>
#include<QCanBusDevice>
#include<QDebug>
#include<QCanBusFrame>
#include "comboboxmodel.h"

class recieveFrames : public QObject
{
    Q_OBJECT
public:
    explicit recieveFrames(QObject *parent = nullptr);
    QCanBusDevice *m_device;
    QCanBusFrame frame;
signals:
    void signalFrame(QString data);

public slots:
    void displayFrame();

};

#endif // RECIEVEFRAMES_H
