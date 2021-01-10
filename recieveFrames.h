#ifndef RECIEVEFRAMES_H
#define RECIEVEFRAMES_H

#include <QObject>
#include <QCanBus>
#include<QCanBusDevice>
#include<QDebug>
#include<QCanBusFrame>

class recieveFrames : public QObject
{
    Q_OBJECT
public:
    explicit recieveFrames(QObject *parent = nullptr);
    QCanBusDevice *m_device;
    QCanBusFrame frame;
signals:
    void signalData(QString data);

public slots:
    QString funkcija();

};

#endif // RECIEVEFRAMES_H
