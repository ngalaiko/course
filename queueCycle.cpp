#include "queueCycle.h"

QueueCycle::QueueCycle(Display *parent)
{
    this->parent = parent;
}

void QueueCycle::Add(int a)
{
    //создаем новый элемент очереди и записываем в него то, что нужно добавить
    RecDyn *new_RecDyn = new RecDyn;
    new_RecDyn->info = a;
    new_RecDyn->next = NULL;
    if (a)
    {
        if (!first)
        {
            new_RecDyn->next = new_RecDyn;
            first = new_RecDyn;

            emit PaintAddCycleQueueAdd(number, new_RecDyn->info);
            number++;
        }
        else
        {
            //иначе, двигаемся в конец очереди и к последнему элементу добавляем new_RecDyn
            new_RecDyn->next = first->next;
            first->next = new_RecDyn;

            emit PaintAddCycleQueueAdd(number, new_RecDyn->info);
            number++;
        }
        first = new_RecDyn;
    }
    else
    {
        if (number)
            emit PaintAddCycleQueueAdd(number, new_RecDyn->info);
    }
}
