#include "stack.h"

Stack::Stack(Display *parent)
{
    this->parent = parent;
}

void Stack::Add(int a)
{
    //создаем новый элемент очереди и записываем в него то, что нужно добавить
    RecDyn *new_RecDyn = new RecDyn;
    new_RecDyn->info = a;
    new_RecDyn->next = NULL;
    //если стэк пуст, то добавляем в first новый элемент
    if (a)
    {
        if(!first)
        {
            first = new_RecDyn;

            PaintAddStackElem(number, new_RecDyn->info);
            number++;
        }
        else
        {
            //иначе, переопределяем first новым элементом, а старый first прикрепляем к нему
            RecDyn *buff = new RecDyn;
            buff = first;
            first = new_RecDyn;
            first->next = buff;

            PaintAddStackElem(number, new_RecDyn->info);
            number++;
        }
    }
    else
    {
        if (number)
            PaintAddStackElem(number, new_RecDyn->info);
    }

    emit setLabel("Добавление закончено.");
}
