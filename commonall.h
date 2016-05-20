#ifndef COMMONALL_H
#define COMMONALL_H

#include <QObject>
#include <cstddef>
#include <QEventLoop>

#include "display.h"

struct RecDyn
{
    int info;
    RecDyn *next;
};

struct elemdouble
{
    int info;
    elemdouble *next;
    elemdouble *prev;
};

class CommonAll : public QObject
{
    Q_OBJECT
public:
    CommonAll() {}
    ~CommonAll() {}

    int virtual Top() = 0;
    void virtual Add(int a) = 0;
    void virtual Insert() = 0;
    int virtual Remove(int n) = 0;
    void virtual SortBubble() = 0;
    void virtual SortSet() = 0;
    void virtual Reverse() = 0;
    void virtual Reset() = 0;
protected:
    Display *parent;

    //количество элементов
    int number = 0;

signals:
    //добавление
    void PaintAddQueueElem(int number, int info);
    void PaintAddStackElem(int number, int info);
    void PaintAddDoubleQueueElem(int number, int info);
    void PaintAddDoubleStackElem(int number, int info);
    void PaintAddCycleQueueAdd(int number, int info);
    //сортировка
    void Paint_Queue_Swap(int i, int j, int j_info, int j_next_info, QString i_name, QString j_name);
    void Paint_Stack_Swap(int number, int i, int j, int j_info, int j_next_info, QString i_name, QString j_name);
    //рисуют оба указателя снизу
    void Paint_Queue_i_j(int i, int j, QString i_name, QString j_name);  
    void Paint_Stack_i_j(int number, int i, int j, QString i_name, QString j_name);
    //маркировка кода
    void markSortSet(int n);
    void markSortBubble(int n);
    void markRemove(int n);
    void markInsert(int n);
    void markReverse(int n);
    //установка лэйблов
    void setLabel(QString string);
    void setLabelFlag(QString string);
    //нарисовать pred (сверху) и curr (снизу)
    void PaintQueuePredCurr(int number, int pred, int curr, QString pred_s, QString curr_s, int predmax = -1, int max = -1);
    void PaintStackPredCurr(int number, int pred, int curr, QString pred_s, QString curr_s, int predmax = -1, int max = -1);
    void PaintQueueCyclePointerUp(int,QString);
    //удаление
    void PaintRemoveQueueElem(int number);
    void PaintRemoveStackElem(int number);
    //удаление на позиции
    void PaintRemoveAtQueue(int number, int pos, int info);
    void PaintRemoveAtStack(int number, int pos, int info);
    //нарисовать элементы
    void PaintStackElem(int number, int pos, int info, bool isFirst, bool isLast);
    void PaintQueueElem(int number, int pos, int info, bool isFirst, bool isLast);
    //удаление последнего элемента
    void PaintRemoveLastStack(int number, int pos);
    void PaintRemoveLastQueue(int number, int pos);
    //вставка
    void PaintInsertAtQueue(int number, int pos, bool isFirst, bool isLast);
    void PaintInsertAtStack(int number, int pos, bool isFirst, bool isLast);
    //реверс
    void PaintReverseQueue(int number, int first_pos, int first_info, int tail_info);
    void PaintReverseStack(int number, int first_pos, int first_info, int tail_info);

public slots:
    //слот ожидания сигнала от объекта
    void wait(QObject * senderObj, const char * signalFromObj) const
    {
        QEventLoop loop;
        connect(senderObj, signalFromObj, &loop, SLOT(quit()));
        loop.exec();
    }
};

#endif // COMMONALL_H
