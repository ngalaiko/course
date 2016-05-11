#ifndef COMMONDOUBLE_H
#define COMMONDOUBLE_H

#include "commonall.h"

class CommonDouble : public CommonAll
{
protected:
    elemdouble *first;
    elemdouble *tail;

public:
    CommonDouble();
    ~CommonDouble();

    int Top();
    int Tail();
    void virtual Add(int a) = 0;
    int Remove(int n);
    void SortBubble();
    void SortSet();
    void Reset() { first = NULL; tail = NULL; number = 0;}
    void Insert() {}
    void Reverse() {}
};

#endif // COMMONDOUBLE_H
