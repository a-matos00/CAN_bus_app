#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>

class counter : public QObject
{
    Q_OBJECT
public:
    explicit counter(QObject *parent = nullptr);
    float m_count = 0;
signals:

public slots:
    void increment();
};

#endif // COUNTER_H
