#include "customdevice.h"
#include<QDebug>
#include<QCanBusDevice>

customDevice::customDevice(QObject *parent) : QObject(parent)
{
    QObject::connect(this, &QCanBusDevice::framesReceived,
            this, display());
}

void customDevice::display()
{

}
