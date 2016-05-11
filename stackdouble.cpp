#include "stackdouble.h"

StackDouble::StackDouble(Display *parent)
{
    this->parent = parent;
}

void StackDouble::Add(int a)
{
    //создаем новый элемент очереди и записываем в него то, что нужно добавить
    elemdouble *new_elemdouble = new elemdouble;
    new_elemdouble->info = a;
    new_elemdouble->next = NULL;
    //если стэк пуст, то добавляем в first новый элемент
    if (a)
    {
        if(!first)
        {
            first = new_elemdouble;

            emit PaintAddDoubleStackElem(number, new_elemdouble->info);
            number++;
        }
        else
        {
            //иначе, переопределяем first новым элементом, а старый first прикрепляем к нему
            first->prev = new_elemdouble;
            new_elemdouble->next = first;
            first = first->prev;

            PaintAddDoubleStackElem(number, new_elemdouble->info);
            number++;
        }
    }
    else
    {
        if (number)
            PaintAddDoubleStackElem(number, new_elemdouble->info);
    }

    emit setLabel("Добавление закончено.");
}
