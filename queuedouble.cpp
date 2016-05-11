#include "queuedouble.h"

QueueDouble::QueueDouble(Display *parent)
{
    this->parent = parent;
}

void QueueDouble::Add(int a)
{
    //создаем новый элемент очереди и записываем в него то, что нужно добавить
    elemdouble *new_elemdouble = new elemdouble;
    new_elemdouble->info = a;
    new_elemdouble->next = NULL;
    new_elemdouble->prev = NULL;
    //если очередь пуста, то добавляем в first новый элемент
    if(!first)
    {
        first = new_elemdouble;
        tail = new_elemdouble;

        emit PaintAddDoubleQueueElem(number, new_elemdouble->info);
        number++;
    }
    else
    {
        //иначе, двигаемся в конец очереди и к последнему элементу добавляем new_elemdouble
        tail->next = new_elemdouble;
        new_elemdouble->prev = tail;
        tail = tail->next;
    }
}
