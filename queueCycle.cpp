#include "queueCycle.h"

QueueCycle::QueueCycle(Display *parent)
{
    this->parent = parent;
}

int QueueCycle::Remove(int n) {
    RecDyn *tek, *pred, *t;
    int result = 0;
    tek = first->next;
    pred = first;

    emit PaintQueueCyclePointerUp(1, "tek");
    emit PaintQueueCyclePointerUp(this->number, "pred");
    wait(parent, SIGNAL(onAll()));

    while (first && first->info == n) {
        if (first->next == first) {
            free(first); first = NULL;
        } else {
            t = first;
            do
                t = t->next;
            while (t->next != first);
            t->next = pred->next;
            free(first);
            result = first->info;
            first = t;
            pred = t;
        }
    }
    if (first != NULL) {
        do
            if (tek->info == n) {
                result = tek->info;
                pred->next = tek->next;
                free(tek);
                tek = pred->next;
            } else {
                pred = tek,tek = tek->next;
            }
        while (tek != first);
    }
    return n;
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
