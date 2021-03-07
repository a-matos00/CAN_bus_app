#ifndef GPIO_PIN_H
#define GPIO_PIN_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QFile>

class GPIO_pin : public QObject
{
    Q_OBJECT
public:
    explicit GPIO_pin(int a_pinNumber, QString a_pinType, int a_initVal, QObject *parent = nullptr);
    ~GPIO_pin();
    int m_pinNumber;
    QString m_pinType;  //input/output
    QString m_pathGPIO; //path to GPIO pin files folder
    QString m_pathValue;
    QString m_pathDirection;
    int m_value;    //current pin value
    int m_FD;
    QFileSystemWatcher* m_FW;  //watches for changes in the pin value file

signals:
    void pinValueChanged(); //signal for qml

public slots:
    void valueChange();
};


#endif // GPIO_PIN_H
