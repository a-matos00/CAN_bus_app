#ifndef GPIO_PIN_H
#define GPIO_PIN_H

#include <QObject>

class GPIO_pin : public QObject
{
    Q_OBJECT
public:
    explicit GPIO_pin(QObject *parent = nullptr);

signals:

};

#endif // GPIO_PIN_H
