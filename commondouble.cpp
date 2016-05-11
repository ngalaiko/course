#include "commondouble.h"

CommonDouble::CommonDouble()
{
    first = NULL;
    tail = NULL;
}

CommonDouble::~CommonDouble()
{
    elemdouble *curr = new elemdouble;
    curr = first;
    while(curr->next)
    {
        elemdouble *buff = new elemdouble;
        buff = curr;
        curr = curr->next;
        delete buff;
    }
}

int CommonDouble::Top()
{
    return first->info;
}

int CommonDouble::Tail()
{
    return tail->info;
}

int CommonDouble::Remove(int n)
{
    for (int i = 0; i < n; i++)
    {

    }
    //если очередь пуста, возвращаем 0
    if(!first)
        return 0;
    //возвращаем first и сдвигаем на следующий
    int buff = first->info;
    first = first->next;
    return buff;
}

void CommonDouble::SortSet()
{
    elemdouble *curr_i = new elemdouble;
    elemdouble *curr_j = new elemdouble;

    int i;
    int j;

    curr_i = first;
    i = 0;

    while (curr_i->next)
    {
        curr_j = curr_i->next;
        j = i + 1;
    while (curr_j)
        {
            if(curr_i->info > curr_j->info)
            {
                int buff = curr_i->info;
                curr_i->info = curr_j->info;
                curr_j->info = buff;
            }
            curr_j = curr_j->next;
            j++;
        }
        curr_i = curr_i->next;
        i++;
    }

}

void CommonDouble::SortBubble()
{

}

