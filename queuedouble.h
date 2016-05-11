#ifndef QUEUEDOUBLE_H
#define QUEUEDOUBLE_H

#include "commondouble.h"

class QueueDouble : public CommonDouble
{
public:
    QueueDouble() {}
    QueueDouble(Display *parent);
    ~QueueDouble() {}

    void Add(int a);
};

#endif // QUEUEDOUBLE_H
