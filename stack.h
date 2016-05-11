#ifndef STACK_H
#define STACK_H

#include "common.h"

class Stack : public Common
{
public:
    Stack() {}
    Stack(Display *parent);
    ~Stack() {}

    void Add(int a);
};

#endif // STACK_H
