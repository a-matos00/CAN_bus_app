#ifndef GPIO_H
#define GPIO_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QFile>

class GPIO : public QObject
{
    Q_OBJECT
public:
    explicit GPIO(int a_pinNumber, QString a_pinType, int a_initVal, QObject *parent = nullptr);
    ~GPIO();
    int m_pinNumber;
    QString m_pinType;  //input/output
    QString m_pathGPIO; //path to GPIO pin files folder
    QString m_pathValue;
    QString m_pathDirection;
    int m_value;    //current pin value
    int m_FD;
    QFileSystemWatcher* m_FW;  //watches for changes in the pin value file

signals:

public slots:
    void funkcija();
};


#endif // GPIO_H
