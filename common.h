#ifndef COMMON_H
#define COMMON_H

#include "commonall.h"

class Common : public CommonAll
{
protected:
    RecDyn *first;

public:
    Common();
    ~Common();

    int Top();
    void virtual Add(int a) = 0;
    void Insert();
    int virtual Remove(int n);
    void SortBubble();
    void SortSet();
    void Reverse();
    void Reset() { first = NULL; number = 0;}

    RecDyn *Reverse_helper(RecDyn *lst, int pos);
    void PaintList();

};

#endif // COMMON_H
