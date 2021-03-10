#include "counter.h"
#include "gpio_handler.h"
#include <QDebug>

counter::counter(QObject *parent) : QObject(parent)
{
    m_count = 0;

}

void counter::increment()
{
    this->m_count += 0.5;
}


