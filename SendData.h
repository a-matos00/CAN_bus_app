#ifndef SENDATA_H
#define SENDATA_H

#include <QObject>

class SendData : public QObject
{
Q_OBJECT
public:
explicit SendData(QObject *parent = 0); //constructor
Q_INVOKABLE void sendMessage(QString arg_id, QByteArray arg_data);

signals:

public slots:

};

#endif // SENDATA_H
