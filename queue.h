#ifndef QUEUE_H
#define QUEUE_H

#include "common.h"

class Queue : public Common
{
public:
    Queue() {}
    Queue(Display *parent);
    ~Queue() {}

    void Add(int a);
};

#endif // QUEUE_H
