#include "queue.h"

Queue::Queue(Display *parent)
{
    this->parent = parent;
}

void Queue::Add(int a)
{
    //создаем новый элемент очереди и записываем в него то, что нужно добавить
    RecDyn *new_RecDyn = new RecDyn;
    new_RecDyn->info = a;
    new_RecDyn->next = NULL;
    if (a)
    {
        //если очередь пуста, то добавляем в first новый элемент
        if (!first)
        {
            first = new_RecDyn;

            emit PaintAddQueueElem(number, new_RecDyn->info);
            number++;
        }
        else
        {
            //иначе, двигаемся в конец очереди и к последнему элементу добавляем new_RecDyn
            RecDyn *curr = new RecDyn;
            curr = first;
            while(curr->next)
            {
                curr = curr->next;
            }
            curr->next = new_RecDyn;

            emit PaintAddQueueElem(number, new_RecDyn->info);
            number++;
        }
    }
    else
    {
        if (number)
            emit PaintAddQueueElem(number, new_RecDyn->info);
    }
}
