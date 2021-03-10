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
    int m_pinNumber;    //gpio number
    int m_value;    //current pin value
    bool m_exportStatus;    //true if the pin is exported
    QString m_pinType;  //input/output
    QString m_pathGPIO; //path to GPIO pin files folder
    QString m_pathValue;
    QString m_pathDirection;
    QString m_pathExport;
    QString m_pathUnexport;
    QFileSystemWatcher* m_FW;  //watches for changes in the pin value file

signals:

public slots:
};


#endif // GPIO_PIN_H
