#include "common.h"

Common::Common()
{
    first = NULL;
}

Common::~Common()
{
    RecDyn *curr = new RecDyn;
    curr = first;
    while(curr->next)
    {
        RecDyn *buff = new RecDyn;
        buff = curr;
        curr = curr->next;
        delete buff;
    }
}

int Common::Top()
{
    return first->info;
}

void Common::Reverse()
{
    first = Reverse_helper(first, 0);

    emit setLabel("Реверс списка завершен.");
    emit setLabelFlag(" ");
    emit markReverse(13);

    PaintList();
}

RecDyn* Common::Reverse_helper(RecDyn *lst, int pos)
{
   RecDyn *tail, *NewHead;
   if (!lst || !lst->next)
      return lst;
   else
   {
      tail = lst->next;

      emit setLabel("Сдвигаем указатели. Глубина: " + QString::number(pos));
      emit markReverse(8);

      emit PaintQueuePredCurr(number, pos, pos + 1, "lst " + QString::number(pos), "tail " + QString::number(pos));
      emit PaintStackPredCurr(number, pos, pos + 1, "lst " + QString::number(pos), "tail " + QString::number(pos));
      wait(parent, SIGNAL(onAll()));

      NewHead = Reverse_helper(tail, pos + 1);

      lst->next = NULL;
      tail->next = lst;

      emit PaintReverseQueue(number, pos, lst->info, tail->info);
      emit PaintReverseStack(number, pos, lst->info, tail->info);
      wait(parent, SIGNAL(onAll()));

      return NewHead;
    }
}

void Common::PaintList()
{
    //рисуем список
    if (first->next)
    {
        emit PaintStackElem(number, 0, first->info, true, false);
        emit PaintQueueElem(number, 0, first->info, true, false);

        RecDyn *temp = first->next;
        int j;
        for (j = 1; temp->next; j++)
        {
            emit PaintStackElem(number, j, temp->info, false, false);
            emit PaintQueueElem(number, j, temp->info, false, false);
            temp = temp->next;
        }
        emit PaintStackElem(number, j, temp->info, false, true);
        emit PaintQueueElem(number, j, temp->info, false, true);
    }
    else
    {
        emit PaintStackElem(number, 0, first->info, true, true);
        emit PaintQueueElem(number, 0, first->info, true, true);
    }
}

void Common::Insert()
{
    RecDyn *curr, *prev, *r100, *r1000, *max, *predmax;
    curr = prev = max = predmax = first;
    int icurr = 0;
    int ipred = 0;
    int imax = 0;
    int ipredmax = 0;
    bool isLast = false;
    bool isFirst = false;

    emit setLabel("Устанавливаем все указатели на первый элемент.");
    emit markInsert(4);

    emit PaintQueuePredCurr(number, 0, 0, "prev", "curr", 0, 0);
    emit PaintStackPredCurr(number, 0, 0, "prev", "curr", 0, 0);
    wait(parent, SIGNAL(onAll()));


    while (curr)
    {
        emit setLabel("Сравниваем с максимумом.");
        emit markInsert(7);
        emit PaintQueuePredCurr(number, ipred, icurr, "prev", "curr", ipredmax, imax);
        emit PaintStackPredCurr(number, ipred, icurr, "prev", "curr", ipredmax, imax);
        wait(parent, SIGNAL(onAll()));

        if (curr->info > max->info)
        {
            max = curr;
            predmax = prev;
            imax = icurr;
            ipredmax = ipred;

            emit setLabel("Запоминаем новый максимум.");
            emit markInsert(9);
            if (ipredmax < 0)
                ipredmax = 0;
            //указатели
            emit PaintQueuePredCurr(number, ipred, icurr, "prev", "curr", ipredmax, imax);
            emit PaintStackPredCurr(number, ipred, icurr, "prev", "curr", ipredmax, imax);
            wait(parent, SIGNAL(onAll()));
        }
        prev = curr;
        curr = curr->next;
        icurr++;
        ipred = icurr - 1;

        emit setLabel("Переходим к следующему элементу.");
        emit markInsert(11);

        //указатели
        emit PaintQueuePredCurr(number, ipred, icurr, "prev", "curr", ipredmax, imax);
        emit PaintStackPredCurr(number, ipred, icurr, "prev", "curr", ipredmax, imax);
        wait(parent, SIGNAL(onAll()));
    }
    emit setLabel("Максимум найден.");
    emit markInsert(12);
    //указатели
    emit PaintQueuePredCurr(number, 100, 100, "prev", "curr", ipredmax, imax);
    emit PaintStackPredCurr(number, number + 1, number + 1, "prev", "curr", ipredmax, imax);
    wait(parent, SIGNAL(onAll()));

    r100 = new RecDyn;
    r1000 = new RecDyn;

    r100->info = 100;
    r1000->info = 1000;

    r1000->next = max->next;
    max->next = r1000;

    if (max == first)
    {
        r100->next = first;
        first = r100;
    }
    else
    {
        r100->next = max;
        predmax->next = r100;
    }

    number += 2;

    emit PaintList();

    if (imax == 0)
        isFirst = true;
    if (!r1000->next)
        isLast = true;

    emit PaintInsertAtQueue(number, imax + 1, isFirst, isLast);
    emit PaintInsertAtStack(number, imax + 1, isFirst, isLast);
}

int Common::Remove(int n)
{
    //если очередь пуста, возвращаем NULL
    if(!first)
    {
        return 0;
    }

    RecDyn *curr, *pred;
    int i = 0;
    int result = 0;

    pred = first;
    curr = first;

    if (n)
    {
        emit setLabel("Устанавливаем curr и pred на первый элемент.");
        emit markRemove(4);

        emit PaintQueuePredCurr(number, 0, 0, "pred", "curr");
        emit PaintStackPredCurr(number, 0, 0, "pred", "curr");
        wait(parent, SIGNAL(onAll()));
    }

    while(curr)
    {
        if (curr->info == n)
        {
            if (curr == first)
            {
                result = curr->info;

                curr = curr->next;
                first = curr;
                pred = first;

                if (number == 1)
                {
                    number = 0;
                }
                else
                    number--;

                emit PaintRemoveStackElem(number);
                emit PaintRemoveQueueElem(number);
                wait(parent, SIGNAL(onAll()));

                //рисуем список заново сдвинутым
                if (first) //чтобы не вылетало
                {
                    if(first->next)
                    {
                        emit PaintQueueElem(number, 0, first->info, true, false);

                        RecDyn *temp = first->next;
                        int j;
                        for (j = 1; temp->next; j++)
                        {
                            emit PaintQueueElem(number, j, temp->info, false, false);
                            temp = temp->next;
                        }
                        emit PaintQueueElem(number, j, temp->info, false, true);
                    }
                    else
                    {
                        emit PaintQueueElem(number, 0, first->info, true, true);
                    }
                }
            }
            else
            {
                result = curr->info;

                pred->next = curr->next;
                curr = pred->next;

                if (number == 1)
                {
                    number = 0;
                }
                else
                    number--;

                if (curr)
                {
                    emit PaintRemoveAtStack(number, i, result);
                    emit PaintRemoveAtQueue(number, i, result);
                    wait(parent, SIGNAL(onAll()));
                }
                else
                {
                    emit PaintRemoveLastQueue(number, i);
                    emit PaintRemoveLastStack(number, i);
                    wait(parent, SIGNAL(onAll()));
                }

                //рисуем список заново сдвинутым
                PaintList();
            }
        }
        else
        {
            pred = curr;

            emit setLabel("Переставляем pred на curr.");
            emit markRemove(20);
            emit PaintQueuePredCurr(number, i, i, "pred", "curr");
            emit PaintStackPredCurr(number, i, i, "pred", "curr");
            wait(parent, SIGNAL(onAll()));

            curr = curr->next;
            i++;

            emit setLabel("Переставляем curr дальше.");
            emit markRemove(21);
            emit PaintQueuePredCurr(number, i - 1, i, "pred", "curr");
            emit PaintStackPredCurr(number, i - 1, i, "pred", "curr");
            wait(parent, SIGNAL(onAll()));
        }
    }

    emit setLabel("Все элементы, равные " + QString::number(n) + ", удалены.");
    emit markRemove(23);

    return result;
}

void Common::SortSet()
{
    RecDyn *curr_i = new RecDyn;
    RecDyn *curr_j = new RecDyn;

    int i;
    int j;

    curr_i = first;
    i = 0;
    j = -100;

    emit markSortSet(5);
    emit setLabel("Устанавливаем указатель Reci на первый элемент.");

    emit PaintQueuePredCurr(number, i, j, "Reci", "Recj");
    emit PaintStackPredCurr(number, i, j, "Reci", "Recj");
    wait(parent, SIGNAL(onAll()));


    while (curr_i->next)
    {
        curr_j = curr_i->next;
        j = i + 1;

        emit markSortSet(8);
        emit setLabel("Устанавливаем указатель Recj на элемент, следеющий после Reci.");

        emit PaintQueuePredCurr(number, i, j, "Reci", "Recj");
        emit PaintStackPredCurr(number, i, j, "Reci", "Recj");
        wait(parent, SIGNAL(onAll()));

        while (curr_j)
        {
            emit markSortSet(11);
            emit setLabel("Сравнивниваем Reci и Recj элементы, если Reci^.info больше Recj^.info, меняем их местами.");

            emit PaintQueuePredCurr(number, i, j, "Reci", "Recj");
            emit PaintStackPredCurr(number, i, j, "Reci", "Recj");
            wait(parent, SIGNAL(onAll()));

            if(curr_i->info > curr_j->info)
            {
                emit markSortSet(12);
                emit setLabel("Начинаем менять местами Reci^.info и Recj^.info.");

                emit Paint_Queue_Swap(i, j, curr_i->info, curr_j->info, "Reci", "Recj");
                emit Paint_Stack_Swap(number, i, j, curr_i->info, curr_j->info, "Reci", "Recj");
                wait(parent, SIGNAL(onAll()));

                int buff = curr_i->info;
                curr_i->info = curr_j->info;
                curr_j->info = buff;

                emit markSortSet(16);
                emit setLabel("Поменяли Reci^.info и Recj^.info.");

                emit PaintQueuePredCurr(number, i, j, "Reci", "Recj");
                emit PaintStackPredCurr(number, i, j, "Reci", "Recj");
                wait(parent, SIGNAL(onAll()));
            }
            curr_j = curr_j->next;
            j++;

            emit markSortSet(17);
            emit setLabel("Переставляем указатель Recj на следующий элемент.");

            emit PaintQueuePredCurr(number, i, j, "Reci", "Recj");
            emit PaintStackPredCurr(number, i, j, "Reci", "Recj");
            wait(parent, SIGNAL(onAll()));
        }
        curr_i = curr_i->next;
        i++;

        emit markSortSet(19);
        emit setLabel("Переставляем указатель Reci на следующий элемент.");

        emit PaintQueuePredCurr(number, i, j, "Reci", "Recj");
        emit PaintStackPredCurr(number, i, j, "Reci", "Recj");
        wait(parent, SIGNAL(onAll()));
    }
    emit markSortSet(20);
    emit setLabel("Сортировка завершена.");
}

void Common::SortBubble()
{
    RecDyn *curr = new RecDyn;
    RecDyn *next = new RecDyn;
    bool flag;
    QString s_flag;

    int i = -100;
    int j = -100;

    do
    {
        curr = first;
        i = 0;

        emit markSortBubble(6);
        emit setLabel("Устанавливаем указатель curr на первый элемент.");

        emit Paint_Queue_i_j(i, j, "curr", "next");
        emit Paint_Stack_i_j(number, i, j, "curr", "next");
        wait(parent, SIGNAL(onAll()));

        flag = true;
        s_flag = "flag = <font color=green>true</font>";

        emit markSortBubble(7);
        emit setLabel("Поднимаем флаг.");

        emit setLabelFlag(s_flag);
        emit Paint_Queue_i_j(i, j, "curr", "next");
        emit Paint_Stack_i_j(number, i, j, "curr", "next");
        wait(parent, SIGNAL(onAll()));

        while (curr->next)
        {
            next = curr->next;
            j = i+1;

            emit markSortBubble(9);
            emit setLabel("Устанавливаем next на элемент, следующий после curr.");
            emit setLabelFlag(s_flag);

            emit Paint_Queue_i_j(i, j, "curr", "next");
            emit Paint_Stack_i_j(number, i, j, "curr", "next");
            wait(parent, SIGNAL(onAll()));

            emit markSortBubble(10);
            emit setLabel("Сравнивниваем curr и next элементы, если curr^.info меньше next^.info, меняем их местами.");
            emit setLabelFlag(s_flag);

            emit Paint_Queue_i_j(i, j, "curr", "next");
            emit Paint_Stack_i_j(number, i, j, "curr", "next");
            wait(parent, SIGNAL(onAll()));

            if (curr->info < next->info)
            {
                emit markSortBubble(12);
                emit setLabel("Меняем местами curr.info и  next.info.");

                emit setLabelFlag(s_flag);
                emit Paint_Queue_Swap(i, j, curr->info, next->info, "curr", "next");
                emit Paint_Stack_Swap(number, i, j, curr->info, next->info, "curr", "next");
                wait(parent, SIGNAL(onAll()));

                int c = curr->info;
                curr->info = next->info;
                next->info = c;

                flag = false;
                s_flag = "flag = <font color=red>false</font>";

                emit markSortBubble(13);
                emit setLabel("Опускаем флаг.");
                emit setLabelFlag(s_flag);

                emit Paint_Queue_i_j(i, j, "curr", "next");
                emit Paint_Stack_i_j(number, i, j, "curr", "next");
                wait(parent, SIGNAL(onAll()));
            }
            curr = next;
            i = j;

            emit markSortBubble(15);
            emit setLabel("Устанавливаем curr на next (следующий элемент).");
            emit setLabelFlag(s_flag);

            emit Paint_Queue_i_j(i, j, "curr", "next");
            emit Paint_Stack_i_j(number, i, j, "curr", "next");
            wait(parent, SIGNAL(onAll()));
        }
    }
    while (!flag);

    emit markSortBubble(18);
    emit setLabel("Сортировка закончена.");
    emit setLabelFlag(" ");
}
