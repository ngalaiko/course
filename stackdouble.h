#ifndef STACKDOUBLE_H
#define STACKDOUBLE_H

#include "commondouble.h"

class StackDouble : public CommonDouble
{
public:
    StackDouble() {}
    StackDouble(Display *parent);
    ~StackDouble() {}

    void Add(int a);
};

#endif // STACKDOUBLE_H
