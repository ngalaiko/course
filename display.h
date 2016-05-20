#ifndef DISPLAY_H
#define DISPLAY_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QEventLoop>

namespace Ui {
class Display;
}

class Display : public QDialog
{
    Q_OBJECT

public:
    explicit Display(QWidget *parent = 0);
    ~Display();

    void ClearScene();

private:
    Ui::Display *ui;
    QGraphicsScene *scene_stack;
    QGraphicsScene *scene_queue;
    QGraphicsScene *scene_doubleQueue;
    QGraphicsScene *scene_doubleStack;
    QGraphicsScene *scene_cycleQueue;
    int time;
    int field;
    int width;
    int height;
    int length;
    int x;
    int y;
    int info;
    int number;
    bool isAdd;
    int operation;
    bool endFlag;
    QTimer *timer;
    //положения элементов для swap и их значения
    int i1;
    int j1;
    int i1_info;
    int j1_info;
    QString i1_name;
    QString j1_name;
    //положение max и predmax
    int m1;
    int pm1;
    bool isFirst;
    bool isLast;
    //флаг для вызова/не вызова сигнала onAll() при удалении последнего элемента
    bool flag = false;
    //рисуют один элемент
    void Paint_1_elem_stack(bool isNew);
    void Paint_1_elem_queue(bool isNew);
    void Paint_1_elem_DoubleQueue(bool isNew);
    void Paint_1_elem_DoubleStack(bool isNew);
    void Paint_1_elem_CycleQueue(bool isNew);
    //рисуют указатель
    void Paint_Queue_Swap_Pointer(int x, QString string, bool isDelete);
    void Paint_Stack_Swap_Pointer(int x, QString string, bool isDelete);
    //меняют элементы местами
    void Paint_Queue_Swap_do(int j1, int j2, int j1_info, int j2_info);
    void Paint_Stack_Swap_do(int i1, int j1, int i1_info, int j1_info);
    //указатели
    void Paint_Queue_Pointer_up(int x, QString string);
    void Paint_Queue_Pointer_down(int x, QString string);
    void Paint_Stack_Pointer_up(int x, QString string);
    void Paint_DoubleStack_Pointer_up(int x, QString string);
    void Paint_Stack_Pointer_down(int x, QString string);
    void Paint_DoubleStack_Pointer_down(int x, QString string);
    void Paint_CycleQueue_Pointer_up(int x, QString string);

    void Paint_CycleQueue_Line();

public slots:
    //слоты добавления
    void PaintAddQueueElem(int number, int info);
    void PaintAddStackElem(int number, int info);
    void PaintAddDoubleQueueElem(int number, int info);
    void PaintAddDoubleStackElem(int number, int info);
    void PaintAddCycleQueueAdd(int number, int info);
    //слоты удаления
    void PaintRemoveStackElem(int number);
    void PaintRemoveQueueElem(int number);
    //слот для анимации
    void Timer_Elapsed();
    //слот для swap'а элементов
    void Paint_Queue_Swap(int i, int j, int i1_info, int j1_info, QString i1_name, QString j1_name);
    void Paint_Stack_Swap(int number, int i, int j, int i1_info, int j1_info, QString i1_name, QString j1_name);
    //слот для рисования указателей i и j
    void Paint_Queue_I_J(int i, int j, QString i1_name, QString j1_name);
    void Paint_Stack_I_J(int number, int i, int j, QString i1_name, QString j1_name);
    //слот написания на label
    void setLabel(QString string);
    //слот написания на label_flag
    void setLabelFlag(QString string);
    //нарисовать first и pred
    void Paint_Queue_pred_curr(int number, int pred, int curr, QString pred_s, QString curr_s, int predmax, int max);
    void Paint_Stack_pred_curr(int number, int pred, int curr, QString pred_s, QString curr_s, int predmax, int max);
    //удаление на позиции
    void PaintRemoveAtQueue(int number, int pos, int info);
    void PaintRemoveAtStack(int number, int pos, int info);
    //удаление последнего элемента
    void PaintRemoveLastStack(int number, int pos);
    void PaintRemoveLastQueue(int number, int pos);
    //нарисовать один элемент
    void PaintQueueElem(int number, int pos, int info, bool isFirst, bool isLast);
    void PaintStackElem(int number, int pos, int info, bool isFirst, bool isLast);
    //вставка
    void PaintInsertAtQueue(int number, int pos, bool isFirst, bool isLast);
    void PaintInsertAtStack(int number, int pos, bool isFirst, bool isLast);
    //реверс
    void PaintReverseQueue(int number, int first_pos, int first_info, int tail_info);
    void PaintReverseStack(int number, int first_pos, int first_info, int tail_info);
    //указатели
    void PaintQueueCyclePointerUp(int x, QString string);
signals:
    void onAll();
    void offAll();
    void onAdd();
    void markQueue(int n);
    void markStack(int n);
    void markRemove(int n);
    void markSort(int n);
    void markInsert(int n);
    void markReverse(int n);
    void markDoubleStack(int n);
    void MarkCycleQueue(int n);
};

#endif // DISPLAY_H
