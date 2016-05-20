#include "display.h"
#include "ui_display.h"
#include "QMessageBox"

Display::Display(QWidget *parent) :
    QDialog(parent, Qt::WindowTitleHint),
    ui(new Ui::Display)
{
    ui->setupUi(this);

    number = 0;
    time = 0;
    field = 10;
    width = 100;
    height = 30;
    length = width / 2;
    x = field + (width + width / 4) * number;
    y = width / 2 + field;

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(Timer_Elapsed()));

    scene_stack = new QGraphicsScene(0, 0, 1000, y + 4 * height);
    scene_queue = new QGraphicsScene(0, 0, 1000, y + 4 * height);
    scene_doubleStack = new QGraphicsScene(0, 0, 1000, y + 7 * height);
    scene_doubleQueue = new QGraphicsScene(0, 0, 1000, y + 7 * height);
    scene_cycleQueue = new QGraphicsScene(0, 0, 1000, y + 7 * height);

    connect(ui->pushButton_next, SIGNAL(clicked()), this, SLOT(Timer_Elapsed()));

    ui->pushButton_next->setEnabled(false);
    ui->label->setText("Добавьте элементы.");
}

Display::~Display()
{
    delete ui;
}

void Display::ClearScene()
{
    scene_queue->clear();
    scene_stack->clear();
    scene_cycleQueue->clear();
    scene_doubleQueue->clear();
    scene_doubleStack->clear();
    ui->label->setText("Добавьте элементы.");
}

void Display::setLabel(QString string)
{
    ui->label->setText(string);
}

void Display::setLabelFlag(QString string)
{
    ui->label_flag->setText(string);
}

void Display::Paint_1_elem_DoubleQueue(bool isNew)
{
    QPen pen(Qt::black);
    QBrush brush(Qt::white);
    int n = number;
    //рисуем стрелочку и замазываем NIL, если не первый элемент
    if (n >= 1 && isNew)
    {
        scene_doubleQueue->addRect(x - width / 2 - width / 4, y, width / 2, height, pen, brush);
        //scene_doubleQueue->addLine(x - width / 2, y + height / 2, x, y + height / 2, pen);
        //scene_doubleQueue->addLine(x, y + height / 2, x - 6, y + height / 2 - 3, pen);
        //scene_doubleQueue->addLine(x, y + height / 2, x - 6, y + height / 2 + 3, pen);
    }
    else
    {
        //сам элемент
        //прямоугольники
        scene_doubleQueue->addRect(x, y, width / 2, height, pen, brush);
        scene_doubleQueue->addRect(x, y + height, width / 2, height, pen, brush);
        scene_doubleQueue->addRect(x, y + 2 * height, width / 2, height, pen, brush);
    }
}

void Display::Paint_1_elem_DoubleStack(bool isNew)
{
    QPen pen(Qt::black);
    QBrush brush(Qt::white);
    int n = number;
    //рисуем стрелочку и замазываем NIL, если не первый элемент
    if (n >= 1 && isNew)
    {
        //scene_doubleStack->addRect(x - width / 2 - width / 4, y + height, width / 2, height, pen, brush);
        scene_doubleStack->addLine(x + width / 2 + width / 4, y + height + height / 2, x - (length - width / 4), y + height + height / 2, pen);
        scene_doubleStack->addLine(x - (length - width / 4), y + height + height / 2, x - (length - width / 4) + 6, y + height + height / 2 - 3, pen);
        scene_doubleStack->addLine(x - (length - width / 4), y + height + height / 2, x - (length - width / 4) + 6, y + height + height / 2 + 3, pen);
    }
    else
    {
        //сам элемент
        //прямоугольники
        scene_doubleStack->addRect(x + width / 2, y, width / 2, height, pen, brush);
        scene_doubleStack->addRect(x + width / 2, y + height, width / 2, height, pen, brush);
        scene_doubleStack->addRect(x + width / 2, y + 2 * height, width / 2, height, pen, brush);
    }
}

void Display::Paint_1_elem_CycleQueue(bool isNew)
{
    QPen pen(Qt::black);
    QBrush brush(Qt::white);
    int n = number;
    //рисуем стрелочку и замазываем NIL, если не первый элемент
    if (n >= 1 && isNew)
    {
        scene_cycleQueue->addRect(x - width / 2 - width / 4, y, width / 2, height, pen, brush);
        scene_cycleQueue->addLine(x - width / 2, y + height / 2, x, y + height / 2, pen);
        scene_cycleQueue->addLine(x, y + height / 2, x - 6, y + height / 2 - 3, pen);
        scene_cycleQueue->addLine(x, y + height / 2, x - 6, y + height / 2 + 3, pen);
    }
    else
    {
        //сам элемент
        //прямоугольники
        scene_cycleQueue->addRect(x, y, width / 2, height);
        scene_cycleQueue->addRect(x + width / 2, y, width / 2, height);
    }
}

void Display::Paint_CycleQueue_Line()
{
    scene_cycleQueue->addLine(x + width / 2 + width / 4, y + height / 2, x + width + width / 4, y + height / 2);
    scene_cycleQueue->addLine(x + width + width / 4, y + height / 2, x + width + width / 4, y + height + height / 2);
    scene_cycleQueue->addLine(x + width + width / 4, y + height + height / 2, field + width / 4, y + height + height / 2);
    scene_cycleQueue->addLine(field + width / 4, y + height + height / 2, field + width / 4, y + height);
    scene_cycleQueue->addLine(field + width / 4, y + height + 1, field + width / 4 - 3, y + height + 5);
    scene_cycleQueue->addLine(field + width / 4, y + height + 1, field + width / 4 + 3, y + height + 5);
}

void Display::PaintAddCycleQueueAdd(int number, int info)
{
    ui->pushButton_next->setEnabled(true);
    emit offAll();

    this->number = number;
    this->info = info;

    ui->label_flag->setText("n = " + QString::number(info));

    x = field + (width + width / 2) * number;

    ui->graphicsView->setScene(scene_cycleQueue);

    if (!number)
    {
        //первый элемент
        scene_cycleQueue->clear();
        ui->label->setText("Приравниваем lst = NULL.");
        emit MarkCycleQueue(0);

        QPen pen(Qt::black);
        QBrush brush(Qt::white);
        QGraphicsTextItem *name = NULL;

        scene_cycleQueue->addRect(x + width / 2 + 5, field + height / 2, width / 2 - 10, height / 2, pen, brush);
        name = scene_cycleQueue->addText("lst");
        name->setPos(x + width / 2 + 5, 3);
        name = scene_cycleQueue->addText("NULL");
        name->setPos(x + width / 2 + 5,  field + height / 2 - 5);

        operation = 10;
        time = -1;
    }
    else
    {
        operation = 10;
        time = -1;

        Timer_Elapsed();
    }
}

void Display::PaintAddDoubleQueueElem(int number, int info)
{
    ui->pushButton_next->setEnabled(true);
    emit offAll();

    this->number = number;
    this->info = info;

    ui->label_flag->setText("n = " + QString::number(info));

    x = field + (width + width / 4) * number;

    ui->graphicsView->setScene(scene_doubleQueue);

    ui->label->setText("делать или нет? ");
    /*if (!number)
    {
        QPen pen(Qt::black);
        scene_doubleQueue->clear();
        ui->label->setText("Создаем первый элемент.");
        //************emit markQueue(11);
        //рисуем пустой элемент
        Paint_1_elem_DoubleQueue(true);
        operation = 9;
        time = 1;
        //пишем новый curr
        //pen.setColor(Qt::black);
        //Paint_Queue_Pointer_up(x + width / 2, "curr");
        //запускаем таймер
    }
    else
    {
        //запускаем таймер
        isAdd = true;
        operation = 1;
        time = 0;
        Timer_Elapsed();
    }*/
}

void Display::PaintAddDoubleStackElem(int number, int info)
{
    ui->pushButton_next->setEnabled(true);
    emit offAll();

    ui->label_flag->setText("n = " + QString::number(info));

    this->number = number;
    this->info = info;

    x = field + (width + (length - width / 4)) * number;

    ui->graphicsView->setScene(scene_doubleStack);


    //если первый элемент, начинаем с first = NIL
    if (number == 0)
    {
        ui->label->setText("Приравниваем lst = NULL.");
        emit markDoubleStack(0);

        QPen pen(Qt::black);
        QBrush brush(Qt::white);
        QGraphicsTextItem *name = NULL;

        scene_doubleStack->addRect(x + width / 2 + 5, field + height / 2, width / 2 - 10, height / 2, pen, brush);
        name = scene_doubleStack->addText("lst");
        name->setPos(x + width / 2 + 5, 3);
        name = scene_doubleStack->addText("NULL");
        name->setPos(x + width / 2 + 5,  field + height / 2 - 5);

        //запускаем таймер
        operation = 9;
        time = -10;
    }
    else
    {
        //запускаем таймер
        operation = 9;
        time = -10;

        Timer_Elapsed();
    }
}

void Display::Paint_Queue_Pointer_up(int x, QString string)
{
    QPen pen(Qt::white);
    QBrush brush(Qt::white);
    QGraphicsTextItem *name = NULL;

    scene_queue->addRect(x, 0, width / 2 - 1, y - 1, pen, brush);

    pen.setColor(Qt::black);

    scene_queue->addRect(x + 5, field + height / 2, width / 2 - 10, height / 2, pen, brush);
    scene_queue->addLine(x + width / 4, height / 2 + height / 4 + field, x + width / 4, y, pen);
    scene_queue->addLine(x + width / 4, y , x + width / 4 - 3, y - 5, pen);
    scene_queue->addLine(x + width / 4, y , x + width / 4 + 3, y - 5, pen);
    name = scene_queue->addText(string);
    name->setPos(x + 5, 3);
}

void Display::Paint_CycleQueue_Pointer_up(int x, QString string)
{
    QPen pen(Qt::white);
    QBrush brush(Qt::white);
    QGraphicsTextItem *name = NULL;

    scene_cycleQueue->addRect(x, 0, width / 2 - 1, y - 1, pen, brush);

    pen.setColor(Qt::black);

    scene_cycleQueue->addRect(x + 5, field + height / 2, width / 2 - 10, height / 2, pen, brush);
    scene_cycleQueue->addLine(x + width / 4, height / 2 + height / 4 + field, x + width / 4, y, pen);
    scene_cycleQueue->addLine(x + width / 4, y , x + width / 4 - 3, y - 5, pen);
    scene_cycleQueue->addLine(x + width / 4, y , x + width / 4 + 3, y - 5, pen);
    name = scene_cycleQueue->addText(string);
    name->setPos(x + 5, 3);
}

void Display::PaintQueueCyclePointerUp(int x, QString string) {
    ui->pushButton_next->setEnabled(true);
    emit offAll();
    ui->graphicsView->setScene(scene_queue);

    Paint_CycleQueue_Pointer_up(x, string);

    ui->pushButton_next->setEnabled(false);
    emit onAll();
    operation = 0;
}

void Display::Paint_Queue_Pointer_down(int x, QString string)
{
    QPen pen(Qt::white);
    QBrush brush(Qt::white);
    QGraphicsTextItem *name = NULL;

    scene_queue->addRect(x, y + height + 1, width / 2 - 1, 2 * height, pen, brush);

    pen.setColor(Qt::black);

    scene_queue->addRect(x + 5, y + 2 * height, width / 2 - 10, height / 2, pen, brush);
    scene_queue->addLine(x + width / 4, y + 2 * height + height / 4, x + width / 4, y + height, pen);
    scene_queue->addLine(x + width / 4, y + height + 1, x + width / 4 - 3, y + height + 5, pen);
    scene_queue->addLine(x + width / 4, y + height + 1, x + width / 4 + 3, y + height + 5, pen);
    name = scene_queue->addText(string);
    name->setPos(x + 5, y + 2 * height + field + 2);
}

void Display::Paint_Stack_Pointer_up(int x, QString string)
{
    QPen pen(Qt::white);
    QBrush brush(Qt::white);
    QGraphicsTextItem *name = NULL;

    scene_stack->addRect(x, 0, width / 2 - 1, y - 1, pen, brush);

    pen.setColor(Qt::black);

    scene_stack->addRect(x + 5, field + height / 2, width / 2 - 10, height / 2, pen, brush);
    scene_stack->addLine(x + width / 4, height / 2 + height / 4 + field, x + width / 4, y, pen);
    scene_stack->addLine(x + width / 4, y , x + width / 4 - 3, y - 5, pen);
    scene_stack->addLine(x + width / 4, y , x + width / 4 + 3, y - 5, pen);
    name = scene_stack->addText(string);
    name->setPos(x + 5, 3);
}

void Display::Paint_DoubleStack_Pointer_up(int x, QString string)
{
    QPen pen(Qt::white);
    QBrush brush(Qt::white);
    QGraphicsTextItem *name = NULL;

    scene_doubleStack->addRect(x, 0, width / 2 - 1, y - 1, pen, brush);

    pen.setColor(Qt::black);

    scene_doubleStack->addRect(x + 5, field + height / 2, width / 2 - 10, height / 2, pen, brush);
    scene_doubleStack->addLine(x + width / 4, height / 2 + height / 4 + field, x + width / 4, y, pen);
    scene_doubleStack->addLine(x + width / 4, y , x + width / 4 - 3, y - 5, pen);
    scene_doubleStack->addLine(x + width / 4, y , x + width / 4 + 3, y - 5, pen);
    name = scene_doubleStack->addText(string);
    name->setPos(x + 5, 3);
}

void Display::Paint_Stack_Pointer_down(int x, QString string)
{
    QPen pen(Qt::white);
    QBrush brush(Qt::white);
    QGraphicsTextItem *name = NULL;

    scene_stack->addRect(x, y + height + 1, width / 2 - 1, 2 * height, pen, brush);

    pen.setColor(Qt::black);

    scene_stack->addRect(x + 5, y + 2 * height, width / 2 - 10, height / 2, pen, brush);
    scene_stack->addLine(x + width / 4, y + 2 * height + height / 4, x + width / 4, y + height, pen);
    scene_stack->addLine(x + width / 4, y + height + 1, x + width / 4 - 3, y + height + 5, pen);
    scene_stack->addLine(x + width / 4, y + height + 1, x + width / 4 + 3, y + height + 5, pen);
    name = scene_stack->addText(string);
    name->setPos(x + 5, y + 2 * height + field + 2);
}

void Display::Paint_DoubleStack_Pointer_down(int x, QString string)
{
    QPen pen(Qt::white);
    QBrush brush(Qt::white);
    QGraphicsTextItem *name = NULL;

    scene_doubleStack->addRect(x, y + height + 1, width / 2 - 1, 2 * height, pen, brush);

    pen.setColor(Qt::black);

    scene_doubleStack->addRect(x + 5, y + 4 * height, width / 2 - 10, height / 2, pen, brush);
    scene_doubleStack->addLine(x + width / 4, y + 4 * height + height / 4, x + width / 4, y + 3 * height, pen);
    scene_doubleStack->addLine(x + width / 4, y + 3 * height + 1, x + width / 4 - 3, y + 3 * height + 5, pen);
    scene_doubleStack->addLine(x + width / 4, y + 3 * height + 1, x + width / 4 + 3, y + 3 * height + 5, pen);
    name = scene_doubleStack->addText(string);
    name->setPos(x + 5, y + 4 * height + field + 2);
}

void Display::PaintReverseQueue(int number, int first_pos, int first_info, int tail_info)
{
    ui->pushButton_next->setEnabled(true);
    emit offAll();

    i1 = first_pos;
    info = first_info;
    j1 = tail_info;
    this->number = number;

    ui->graphicsView->setScene(scene_queue);

    emit setLabel("Переставляем NHead. Глубина: " + QString::number(first_pos));
    emit markReverse(9);

    x = field + (width + (length - width / 4)) * (number - 1);
    //рисуем NewHead снизу !последнего! элемента
    Paint_Queue_Pointer_down(x, "NHead");
    x = field + (width + (length - width / 4)) * first_pos;
    //указатель lst сверху
    Paint_Queue_Pointer_up(x + width / 2, "lst " + QString::number(i1));
    //указатель tail снизу
    Paint_Queue_Pointer_down(x + width + width / 4 + width / 2, "tail " + QString::number(i1));

    operation = 8;
    time = 44;
}

void Display::PaintReverseStack(int number, int first_pos, int first_info, int tail_info)
{
    ui->pushButton_next->setEnabled(true);
    emit offAll();

    i1 = first_pos;
    info = first_info;
    j1 = tail_info;
    this->number = number;

    ui->graphicsView->setScene(scene_stack);

    emit setLabel("Переставляем NHead. Глубина: " + QString::number(first_pos));
    emit markReverse(9);

    x = field + (width + (length - width / 4)) * (number - number);
    //рисуем NewHead снизу !последнего! элемента
    Paint_Stack_Pointer_down(x + width / 2, "NHead");
    x = field + (width + (length - width / 4)) * (number - first_pos - 1);
    //указатель lst сверху
    Paint_Stack_Pointer_up(x, "lst " + QString::number(i1));
    //указатель tail снизу
    Paint_Stack_Pointer_down(x - width - width / 4, "tail " + QString::number(i1));

    operation = 8;
    time = 46;
}

void Display::PaintInsertAtStack(int number, int pos, bool isFirst, bool isLast)
{
    ui->pushButton_next->setEnabled(true);
    emit offAll();

    QPen pen(Qt::black);
    QBrush brush(Qt::white);
    QGraphicsTextItem *name = NULL;

    this->number = number;
    this->isFirst = isFirst;
    this->isLast = isLast;

    ui->graphicsView->setScene(scene_stack);

    //элемент
    x = field + (width + (length - width / 4)) * (number - pos - 1);
    //100
    i1 = pos - 1;
    //1000
    j1 = pos + 1;

    ui->label->setText("Сдвигаем элементы для наглядности.");
    emit markInsert(-1);

    //стираем 100
    pen.setColor(Qt::white);
    scene_stack->addRect(x - width - width / 2 + 1, y, width + width / 2 - 2, height, pen, brush);
    //рисуем стрелку 100
    pen.setColor(Qt::black);
    scene_stack->addLine(x - width - width / 2, y + height / 2, x, y + height / 2, pen);
    scene_stack->addLine(x - width - width / 2, y + height / 2, x - width - width / 2 + 6, y + height / 2 - 3, pen);
    scene_stack->addLine(x - width - width / 2, y + height / 2, x - width - width / 2 + 6, y + height / 2 + 3, pen);
    //стираем 1000
    pen.setColor(Qt::white);
    scene_stack->addRect(x + width + 1, y, width + width / 2 - 2, height, pen, brush);
    //рисуем стрелку 1000
    pen.setColor(Qt::black);
    scene_stack->addLine(x + width, y + height / 2, x + width + width + width / 2, y + height / 2, pen);
    scene_stack->addLine(x + width, y + height / 2, x + width + 6, y + height / 2 - 3, pen);
    scene_stack->addLine(x + width, y + height / 2, x + width + 6, y + height / 2 + 3, pen);
    //рисуем max
    Paint_Stack_Pointer_down(x + width / 2, "max");
    //рисуем predmax
    Paint_Stack_Pointer_down(x + 3 * width, "prmax");

    if (isFirst)
    {
        //стираем first и стрелку
        pen.setColor(Qt::white);
        scene_stack->addRect(x + width + 1, field, width * 4, height * 10, pen, brush);
        //стираем какую-то линию слева
        scene_stack->addRect(-150, 0, 150 + field - 1, 5 * height, pen, brush);
        //рисуем first
        pen.setColor(Qt::black);
        Paint_Stack_Pointer_up(x + width / 2, "first");
        //пишем predmax
        Paint_Stack_Pointer_down(x, "prmax");
    }
    if (isLast)
    {
        //стираем стрелку
        pen.setColor(Qt::white);
        scene_stack->addRect(0, field, field + width + width / 4 - 1, height * 4, pen, brush);
        pen.setColor(Qt::black);
        //пишем NIL
        scene_stack->addRect(x, y, width / 2, height, pen, brush);
        name = scene_stack->addText("NIL");
        name->setPos(x + 7, y + 4);
    }

    operation = 8;
    time = 40;
}

void Display::PaintInsertAtQueue(int number, int pos, bool isFirst, bool isLast)
{
    ui->pushButton_next->setEnabled(true);
    emit offAll();

    QPen pen(Qt::black);
    QBrush brush(Qt::white);
    QGraphicsTextItem *name = NULL;

    this->number = number;
    this->isFirst = isFirst;
    this->isLast = isLast;

    ui->graphicsView->setScene(scene_queue);

    //элемент
    x = field + (width + (length - width / 4)) * (pos - 1);
    //100
    i1 = pos - 1;
    //1000
    j1 = pos + 1;

    ui->label->setText("Сдвигаем элементы для наглядности.");
    emit markInsert(-1);

    //стираем 100
    pen.setColor(Qt::white);
    scene_queue->addRect(x - width / 4 + 1, y, width + width / 4, height, pen, brush);
    //рисуем стрелку 100
    pen.setColor(Qt::black);
    scene_queue->addLine(x - width / 4, y + height / 2, x + width + width / 4, y + height / 2, pen);
    scene_queue->addLine(x + width + width / 4, y + height / 2, x + width + width / 4 - 6, y + height / 2 - 3, pen);
    scene_queue->addLine(x + width + width / 4, y + height / 2, x + width + width / 4 - 6, y + height / 2 + 3, pen);
    //стираем 1000
    pen.setColor(Qt::white);
    scene_queue->addRect(x + 2 * width + width / 4 + 1, y, width + width / 4, height, pen, brush);
    //рисуем стрелку 1000
    pen.setColor(Qt::black);
    scene_queue->addLine(x + 2 * width + width / 4, y + height / 2, x + 3 * width + width / 2 + 5, y + height / 2, pen);
    //рисуем max
    pen.setColor(Qt::black);
    Paint_Queue_Pointer_down(x + width + width / 4, "max");
    //рисуем predmax
    pen.setColor(Qt::black);
    Paint_Queue_Pointer_down(x - width - width / 4, "prmax");

    if (isFirst)
    {
        //стираем стрелку и first в начале
        pen.setColor(Qt::white);
        scene_queue->addRect(0, field,width + width / 4 + field - 1, height * 5, pen, brush);
        //стираем какие-то линии слева
        scene_queue->addRect(-150, 0, 150 + field - 1, 5 * height, pen, brush);
        //рисуем новый first
        pen.setColor(Qt::black);
        Paint_Queue_Pointer_up(x + width + width / 4, "first");
        //рисуем predmax
        pen.setColor(Qt::black);
        Paint_Queue_Pointer_down(x + width + width / 4, "prmax");
    }
    if (isLast)
    {
        //убираем стрелку
        pen.setColor(Qt::white);
        scene_queue->addRect(x + 2 * width + width / 4, y, width * 5, height, pen, brush);
        //пишем NIL
        pen.setColor(Qt::black);
        scene_queue->addRect(x + width + width / 4 + width / 2, y, width / 2, height, pen, brush);
        name = scene_queue->addText("NIL");
        name->setPos(x + width + width / 4 + width / 2 + 7, y + 4);
    }

    operation = 7;
    time = 11;
}

void Display::PaintStackElem(int number, int pos, int info, bool isFirst, bool isLast)
{
    QPen pen(Qt::black);
    QBrush brush(Qt::white);
    QGraphicsTextItem *name = NULL;

    this->number = number;
    x = field + (width + (length - width / 4)) * (number - pos - 1);

    //сам элемент
    scene_stack->addRect(x, y, width / 2, height, pen, brush);
    scene_stack->addRect(x + width / 2, y, width / 2, height, pen, brush);
    scene_stack->addLine(x, y + height / 2, x + width / 4, y + height / 2, pen);
    name = scene_stack->addText(QString::number(info));
    name->setPos(x + width / 2 + 12, y + 4);
    //стираем возможный first сверху
    pen.setColor(Qt::white);
    scene_stack->addRect(x, field, width, (y - field - 1), pen, brush);
    //стираем стрелочки перед элементами (остаются после реверса)
    scene_stack->addRect(x + width + 1, y, width / 4 - 2, height / 2 - 1, pen, brush);
    scene_stack->addRect(x + width + 1, y + height / 2 + 1, width / 4 - 2, height / 2, pen, brush);

    pen.setColor(Qt::black);

    if (!isFirst)
    {
        //рисуем стрелочки после элементов
        scene_stack->addLine(x + width, y + height / 2, x + width + width / 4, y + height / 2, pen);
        scene_stack->addLine(x + width, y + height / 2, x + width + 6, y + height / 2 - 3, pen);
        scene_stack->addLine(x + width, y + height / 2, x + width + 6, y + height / 2 + 3, pen);
    }
    if (isFirst)
    {
        //пишем first
        Paint_Stack_Pointer_up(x + width / 2, "first");
        if (number > 1)
        {
            //часть стрелочки
            scene_stack->addLine(x - width / 4, y + height / 2, x + width / 4, y + height / 2, pen);
            scene_stack->addLine(x - width / 4, y + height / 2, x - width / 4 + 6, y + height / 2 - 3, pen);
            scene_stack->addLine(x - width / 4, y + height / 2, x - width / 4 + 6, y + height / 2 + 3, pen);
        }
        //стираем элемент справа
        pen.setColor(Qt::white);
        scene_stack->addRect(x + width + 1, field, width * 4, 4 * height, pen, brush);
    }

    if (isLast)
    {
        pen.setColor(Qt::black);
        //пишем NIL
        scene_stack->addRect(x, y, width / 2, height, pen, brush);
        name = scene_stack->addText("NIL");
        name->setPos(x + 7, y + 4);
        if(!isFirst)
        {
            //дорисовываем честь стрелки
            scene_stack->addLine(x + width ,y + height / 2, x + width + width / 4, y + height / 2, pen);
            scene_stack->addLine(x + width, y + height / 2, x + width + 6, y + height / 2 - 3, pen);
            scene_stack->addLine(x + width, y + height / 2, x + width + 6, y + height / 2 + 3, pen);
        }
    }
}

void Display::PaintQueueElem(int number, int pos, int info, bool isFirst, bool isLast)
{
    QPen pen(Qt::black);
    QBrush brush(Qt::white);
    QGraphicsTextItem *name = NULL;

    this->number = number;

    x = field + (width + (length - width / 4)) * pos;

    //сам элемент
    scene_queue->addRect(x, y, width / 2, height, pen, brush);
    scene_queue->addRect(x + width / 2, y, width / 2, height, pen, brush);
    name = scene_queue->addText(QString::number(info));
    name->setPos(x + 12, y + 4);
    //часть стрелочки внутри элемента
    scene_queue->addLine(x + width / 2 + width / 4, y + height / 2, x + width, y + height / 2, pen);
    //стираем возможный last под ним
    pen.setColor(Qt::white);
    scene_queue->addRect(x, y + height + 1, width, 2 * height, pen, brush);
    //стираем стрелочки после элемента (остаются от реверса)
    scene_queue->addRect(x + width + 1, y, 6, height / 2 - 1, pen, brush);
    scene_queue->addRect(x + width + 1, y + height / 2 + 1, 6, height / 2, pen, brush);
    //стираем возможный curr над ним
    scene_queue->addRect(x, field, width, (y - field - 1), pen, brush);
    pen.setColor(Qt::black);

    if (!isFirst)
    {
        //рисуем стрелочки перед элементом
        scene_queue->addLine(x - width / 4, y + height / 2, x, y + height / 2, pen);
        scene_queue->addLine(x, y + height / 2, x - 6, y + height / 2 - 3, pen);
        scene_queue->addLine(x, y + height / 2, x - 6, y + height / 2 + 3, pen);      
    }

    if (isFirst)
    {
        //рисуем first
        Paint_Queue_Pointer_up(x, "first");
        //стираем возможный first справа
        pen.setColor(Qt::white);
        scene_queue->addRect(x + width + width / 4, field, width / 2, (y - 1) - field,pen, brush);
        //дорисовываем стрелку
        pen.setColor(Qt::black);
        scene_queue->addLine(x + width , y + height / 2, x + width + width / 4, y + height / 2, pen);
        scene_queue->addLine(x + width + width / 4, y + height / 2, x + width + width / 4 - 6, y + height / 2 - 3, pen);
        scene_queue->addLine(x + width + width / 4, y + height / 2, x + width + width / 4 - 6, y + height / 2 + 3, pen);
    }

    if(isLast)
    {
        //стираем то, что справа
        pen.setColor(Qt::white);
        scene_queue->addRect(x + width + 1, field, 4 * width, 6 * height, pen, brush);
        //пием NIL
        pen.setColor(Qt::black);
        scene_queue->addRect(x + width / 2, y, width / 2, height, pen, brush);
        name = scene_queue->addText("NIL");
        name->setPos(x + width / 2 + 7, y + 4);
        if (number > 1)
        {
            //дорисовываем стрелку
            scene_queue->addLine(x - width / 4 , y + height / 2, x, y + height / 2, pen);
            scene_queue->addLine(x, y + height / 2, x - 6, y + height / 2 - 3, pen);
            scene_queue->addLine(x, y + height / 2, x - 6, y + height / 2 + 3, pen);
        }
    }
}

void Display::PaintRemoveLastStack(int number, int pos)
{
    ui->pushButton_next->setEnabled(true);
    emit offAll();

    QPen pen(Qt::black);
    QBrush brush(Qt::white);
    QGraphicsTextItem *name = NULL;

    ui->graphicsView->setScene(scene_stack);

    this->number = number;
    x = field + (width + (length - width / 4)) * (number - pos);

    ui->label->setText("Соединяем предыдущий элемент и следующий.");
    emit markRemove(14);

    //закрашиваем стрелочку и пишем NIL
    pen.setColor(Qt::white);
    scene_stack->addRect(x + width + 1, y, width / 2 + width / 4 - 1, height, pen, brush);
    pen.setColor(Qt::black);
    scene_stack->addRect(x + width + width / 4, y, width / 2, height, pen, brush);
    name = scene_stack->addText("NIL");
    name->setPos(x + width + width / 4 + 7, y + 4);

    //пишем curr
    Paint_Stack_Pointer_down(x, "curr");
    //пишем pred
    Paint_Stack_Pointer_up(x + width + width / 4, "pred");

    operation = 6;
    time = 6;
}

void Display::PaintRemoveLastQueue(int number, int pos)
{
    ui->pushButton_next->setEnabled(true);
    emit offAll();
    ui->graphicsView->setScene(scene_queue);

    this->number = number;

    x = field + (width + (length - width / 4)) * pos;

    QPen pen(Qt::black);
    QBrush brush(Qt::white);
    QGraphicsTextItem *name = NULL;

    ui->label->setText("Соединяем предыдущий элемент и следующий (это последний, так что указывает на NIL).");
    emit markRemove(14);
    pen.setColor(Qt::black);

    //пишем curr
    Paint_Queue_Pointer_down(x + width / 2, "curr");
    //пишем pred
    Paint_Queue_Pointer_up(x - width / 2 - width / 4, "pred");
    //пишем NIL внутри предыдущего
    scene_queue->addRect(x - width - width / 4 + width / 2, y, width / 2, height, pen, brush);
    name = scene_queue->addText("NIL");
    name->setPos(x - width - width / 4 + width / 2 + 7, y + 4);
    //стираем стрелку
    pen.setColor(Qt::white);
    scene_queue->addRect(x - width / 4 + 1, y, width / 4 - 2, height, pen, brush);

    operation = 5;
    time = 24;
}

void Display::PaintAddStackElem(int number, int info)
{
    ui->pushButton_next->setEnabled(true);
    emit offAll();

    ui->label_flag->setText("n = " + QString::number(info));

    this->number = number;
    this->info = info;

    x = field + (width + (length - width / 4)) * number;

    ui->graphicsView->setScene(scene_stack);

    QPen pen(Qt::black);
    QBrush brush(Qt::white);  

    //если первый элемент, начинаем с first = NIL
    if (number == 0)
    {
        ui->label->setText("Приравниваем first = NIL.");
        emit markStack(6);

        QPen pen(Qt::black);
        QBrush brush(Qt::white);
        QGraphicsTextItem *name = NULL;

        scene_stack->addRect(x + width / 2 + 5, field + height / 2, width / 2 - 10, height / 2, pen, brush);
        name = scene_stack->addText("first");
        name->setPos(x + width / 2 + 5, 3);
        name = scene_stack->addText("NIL");
        name->setPos(x + width / 2 + 5,  field + height / 2 - 5);

        //запускаем таймер
        isAdd = true;
        operation = 2;
        time = -1;
    }
    else
    {
        //запускаем таймер
        isAdd = true;
        operation = 2;
        time = -1;

        Timer_Elapsed();
    }

}

void Display::Paint_1_elem_stack(bool isNew)
{
    QPen pen(Qt::black);
    QBrush brush(Qt::white);
    //рисуем стрелочку и замазываем NIL, если не первый элемент
    if (number >= 1 && isNew)
    {
        scene_stack->addRect(x, y, width / 2, height, pen, brush);
        scene_stack->addLine(x + width / 4 , y + height / 2, x - (length - width / 4), y + height / 2, pen);
        scene_stack->addLine(x - (length - width / 4), y + height / 2, x - (length - width / 4) + 6, y + height / 2 - 3, pen);
        scene_stack->addLine(x - (length - width / 4), y + height / 2, x - (length - width / 4) + 6, y + height / 2 + 3, pen);
    }
    else
    {
        //сам элемент
        //прямоугольники
        scene_stack->addRect(x, y, width / 2, height, pen, brush);
        scene_stack->addRect(x + width / 2, y, width / 2, height, pen, brush);
    }
}

void Display::PaintRemoveStackElem(int number)
{
    ui->pushButton_next->setEnabled(true);
    emit offAll();
    ui->graphicsView->setScene(scene_stack);

    this->number = number;
    x = field + (width + (length - width / 4)) * number;

    QPen pen(Qt::black);
    QBrush brush(Qt::white);
    QGraphicsTextItem *name = NULL;

    if (!number)
    {
        ui->label->setText("Если в стэке один элемент, просто переставляем first на NIL.");
        emit markRemove(11);
        x = field + (width + width / 4) * number;
        //очищаем сцену
        scene_stack->clear();
        //пишем NIL
        scene_stack->addRect(x + width / 2 + 5, field + height / 2, width / 2 - 10, height / 2, pen, brush);
        name = scene_stack->addText("first");
        name->setPos(x + width / 2 + 5, 3);
        name = scene_stack->addText("NIL");
        name->setPos(x + width / 2 + 5, field + height / 2 - 5);

        ui->pushButton_next->setEnabled(false);
        emit offAll();
        operation = 0;
    }
    else
    {
        ui->label->setText("Устанавливаем curr и pred на первый элемент.");
        emit markRemove(4);
        //рисуем curr
        Paint_Stack_Pointer_down(x, "curr");
        //рисуем pred
        Paint_Stack_Pointer_up(x, "pred");
        //запускаем таймер
        isAdd = false;
        operation = 2;
        time = 0;
    }
}

void Display::PaintRemoveAtStack(int number, int pos, int info)
{
    ui->pushButton_next->setEnabled(true);
    emit offAll();
    ui->graphicsView->setScene(scene_stack);

    this->number = number;

    x = field + (width + (length - width / 4)) * (number - pos);

    QPen pen(Qt::black);
    QBrush brush(Qt::white);
    QGraphicsTextItem *name = NULL;

    //переносим curr ниже для удобства
    ui->label->setText("Переносим элемент ниже для наглядности.");
    //удаляем старый
    pen.setColor(Qt::white);
    scene_stack->addRect(x - width / 4 + 1, y, width + width / 2 - 2, height, pen, brush);
    //рисуем
    //сам элемент
    pen.setColor(Qt::black);
    scene_stack->addRect(x, y + height, width / 2, height, pen, brush);
    scene_stack->addRect(x + width / 2, y + height, width / 2, height, pen, brush);
    name = scene_stack->addText(QString::number(info));
    name->setPos(x + width / 2 + 18, y + height + 4);
    //закрышиваем часть стрелочки в элементе
    scene_stack->addRect(x + width + width / 4, y, width / 2, height, pen, brush);
    //стрелочки
    scene_stack->addLine(x + width / 4 , y + height / 2 + height, x - (length - width / 4), y + height / 2, pen);
    scene_stack->addLine(x + width, y + height + height / 2, x + width + width / 2, y + height / 2, pen);
    //пишем curr
    scene_stack->addRect(x + 5, y + 2 * height + height / 2, width / 2 - 5, height / 2, pen, brush);
    scene_stack->addLine(x + width / 4, y + 2 * height + height / 2 + height / 4 + 1, x + width / 4, y + height + height, pen);
    scene_stack->addLine(x + width / 4, y + height + height + 1, x + width / 4 - 3, y + height + height + 5, pen);
    scene_stack->addLine(x + width / 4, y + height + height + 1, x + width / 4 + 3, y + height + height + 5, pen);
    name = scene_stack->addText("curr");
    name->setPos(x + 10, y + 2 * height + height + 3);
    //пишем pred
    pen.setColor(Qt::black);
    Paint_Stack_Pointer_up(x + width + width / 4, "pred");

    //запускаем таймер
    operation = 6;
    time = 30;
}

void Display::PaintAddQueueElem(int number, int info)
{
    ui->pushButton_next->setEnabled(true);
    emit offAll();

    this->number = number;
    this->info = info;

    ui->label_flag->setText("n = " + QString::number(info));

    x = field + (width + width / 4) * number;

    ui->graphicsView->setScene(scene_queue);

    if (!number)
    {
        QPen pen(Qt::black);
        /*Brush brush(Qt::white);
        QGraphicsTextItem *name = NULL;*/
        scene_queue->clear();
        ui->label->setText("Создаем первый элемент.");
        emit markQueue(11);
        //рисуем пустой элемент
        Paint_1_elem_queue(true);
        //пишем новый curr
        pen.setColor(Qt::black);
        Paint_Queue_Pointer_up(x + width / 2, "curr");
        //запускаем таймер
        isAdd = true;
        operation = 1;
        time = 5;
    }
    else
    {
        //запускаем таймер
        isAdd = true;
        operation = 1;
        time = 0;
        Timer_Elapsed();
    }
}

void Display::Paint_1_elem_queue(bool isNew)
{
    QPen pen(Qt::black);
    QBrush brush(Qt::white);
    int n = number;
    //рисуем стрелочку и замазываем NIL, если не первый элемент
    if (n >= 1 && isNew)
    {
        scene_queue->addRect(x - width / 2 - width / 4, y, width / 2, height, pen, brush);
        scene_queue->addLine(x - width / 2, y + height / 2, x, y + height / 2, pen);
        scene_queue->addLine(x, y + height / 2, x - 6, y + height / 2 - 3, pen);
        scene_queue->addLine(x, y + height / 2, x - 6, y + height / 2 + 3, pen);
    }
    else
    {
        //сам элемент
        //прямоугольники
        scene_queue->addRect(x, y, width / 2, height, pen, brush);
        scene_queue->addRect(x + width / 2, y, width / 2, height, pen, brush);
    }
}

void Display::PaintRemoveQueueElem(int number)
{
    ui->pushButton_next->setEnabled(true);
    emit offAll();
    ui->graphicsView->setScene(scene_queue);

    this->number = number;
    x = field;

    QPen pen(Qt::black);
    QBrush brush(Qt::white);
    QGraphicsTextItem *name = NULL;

    if (!number)
    {
        ui->label->setText("Если в очереди один элемент, просто переставляем first на NIL.");
        emit markRemove(9);
        x = field + (width + width / 4) * number;
        //очищаем сцену
        scene_queue->clear();
        //пишем NIL
        scene_queue->addRect(x + 5, field + height / 2, width / 2 - 10, height / 2, pen, brush);
        name = scene_queue->addText("first");
        name->setPos(x + 5, 3);
        name = scene_queue->addText("NIL");
        name->setPos(x + 5, field + height / 2 - 5);

        ui->pushButton_next->setEnabled(false);
        emit offAll();
        operation = 0;
    }
    else
    {
        ui->label->setText("Устанавливаем curr и pred на первый элемент.");
        emit markRemove(4);

        //рисуем curr
        Paint_Queue_Pointer_down(x + width / 2, "curr");
        //рисуем pred
        Paint_Queue_Pointer_up(x + width / 2, "pred");
        //запускаем таймер
        isAdd = false;
        operation = 1;
        time = 0;
    }
}

void Display::PaintRemoveAtQueue(int number, int pos, int info)
{
    ui->pushButton_next->setEnabled(true);
    emit offAll();
    ui->graphicsView->setScene(scene_queue);

    this->number = number;

    x = field + (width + (length - width / 4)) * pos;

    QPen pen(Qt::black);
    QBrush brush(Qt::white);
    QGraphicsTextItem *name = NULL;

    //переносим curr ниже для удобства
    ui->label->setText("Переносим элемент ниже для наглядности.");
    emit markRemove(-1);
    //удаляем старый
    pen.setColor(Qt::white);
    scene_queue->addRect(x - width / 4 + 1, y, width + width / 2 - 2, height * 10, pen, brush);
    //рисуем
    pen.setColor(Qt::black);
    //сам элемент
    scene_queue->addRect(x, y + height, width / 2, height, pen, brush);
    scene_queue->addRect(x + width / 2, y + height, width / 2, height, pen, brush);
    name = scene_queue->addText(QString::number(info));
    name->setPos(x + 18, y + height + 4);   
    //закрышиваем старую стрелочку внутри предыдущего элемента
    pen.setColor(Qt::white);
    scene_queue->addRect(x - width / 2 - width / 4 + 1, y + 1, width / 2 - 2, height - 2, pen, brush);
    //стрелочки
    pen.setColor(Qt::black);
    scene_queue->addLine(x - width / 2, y + height / 2, x, y + height + height / 2, pen);
    scene_queue->addLine(x + width / 2 + width / 4, y + height + height / 2, x + width + width / 4, y + height / 2, pen);
    //пишем curr
    scene_queue->addRect(x + width / 2 + 5, y + height / 2 + 2 * height, width / 2 - 5, height / 2, pen, brush);
    scene_queue->addLine(x + width / 2 + width / 4, y + height - height / 4 + 2 * height + 1, x + width / 2 + width / 4, y + height + height, pen);
    scene_queue->addLine(x + width / 2 + width / 4, y + height + height + 1, x + width / 2 + width / 4 - 3, y + height + height + 5, pen);
    scene_queue->addLine(x + width / 2 + width / 4, y + height + height + 1, x + width / 2 + width / 4 + 3, y + height + height + 5, pen);
    name = scene_queue->addText("curr");
    name->setPos(x + width / 2 + 10, y + height + 2 * height + 3);
    //пишем pred
    Paint_Queue_Pointer_up(x - width / 2 - width / 4, "pred");

    //запускаем таймер
    operation = 5;
    time = 20;
}

void Display::Paint_Queue_I_J(int i, int j, QString i1_name, QString j1_name)
{
    this->j1_name = i1_name;
    this->j1_name = i1_name;

    ui->pushButton_next->setEnabled(true);
    emit offAll();
    ui->graphicsView->setScene(scene_queue);

    //рисуем указатель i
    i1 = field + (width + (length - width / 4)) * i;
    Paint_Queue_Swap_Pointer(i1, i1_name, false);

    //рисуем указатель j
    j1 = field + (width + (length - width / 4)) * j + width / 2;
    Paint_Queue_Swap_Pointer(j1, j1_name, false);
    //запускаем таймер
    operation = 3;
    time = 2;
}

void Display::Paint_Stack_I_J(int number, int i, int j, QString i1_name, QString j1_name)
{
    this->j1_name = i1_name;
    this->j1_name = i1_name;

    ui->pushButton_next->setEnabled(true);
    emit offAll();
    ui->graphicsView->setScene(scene_stack);

    //рисуем указатель i
    i1 = field + (width + (length - width / 4)) * (number - i - 1) + width / 2;
    Paint_Stack_Swap_Pointer(i1, i1_name, false);

    //рисуем указатель j
    j1 = field + (width + (length - width / 4)) * (number - j - 1);
    Paint_Stack_Swap_Pointer(j1, j1_name, false);

    operation = 3;
    time = 5;
}

void Display::Paint_Queue_Swap(int i, int j, int i1_info, int j1_info, QString i1_name, QString j1_name)
{
    this->i1_info = i1_info;
    this->j1_info = j1_info;
    this->j1_name = i1_name;
    this->j1_name = i1_name;

    ui->pushButton_next->setEnabled(true);
    emit offAll();
    ui->graphicsView->setScene(scene_queue);

    //рисуем указатель i
    i1 = field + (width + (length - width / 4)) * i + width / 2;
    Paint_Queue_Swap_Pointer(i1, i1_name, false);

    //рисуем указатель j
    j1 = field + (width + (length - width / 4)) * j + width / 2;
    Paint_Queue_Swap_Pointer(j1, j1_name, false);

    operation = 3;
    time = 0;
}

void Display::Paint_Stack_Swap(int number, int i, int j, int i1_info, int j1_info, QString i1_name, QString j1_name)
{
    this->i1_info = i1_info;
    this->j1_info = j1_info;
    this->j1_name = i1_name;
    this->j1_name = i1_name;

    ui->pushButton_next->setEnabled(true);
    emit offAll();
    ui->graphicsView->setScene(scene_stack);

    //рисуем указатель i
    i1 = field + (width + (length - width / 4)) * (number - i - 1);
    Paint_Stack_Swap_Pointer(i1, i1_name, false);

    //рисуем указатель j
    j1 = field + (width + (length - width / 4)) * (number - j - 1);
    Paint_Stack_Swap_Pointer(j1, j1_name, false);

    operation = 3;
    time = 3;
}

void Display::Paint_Queue_Swap_do(int j1, int j2, int j1_info, int j2_info)
{
    QPen pen(Qt::black);
    QBrush brush(Qt::white);
    QGraphicsTextItem *name = NULL;
    //первый элемент j1
    scene_queue->addRect(j1 - width / 2, y, width / 2, height, pen, brush);
    name = scene_queue->addText(QString::number(j2_info));
    name->setPos(j1 - width / 2 + 12, y + 4);
    //второй элемент j2
    scene_queue->addRect(j2 - width / 2, y, width / 2, height, pen, brush);
    name = scene_queue->addText(QString::number(j1_info));
    name->setPos(j2 - width / 2 + 12, y + 4);
}

void Display::Paint_Stack_Swap_do(int i1, int j1, int i1_info, int j1_info)
{
    QPen pen(Qt::black);
    QBrush brush(Qt::white);
    QGraphicsTextItem *name = NULL;
    //первый элемент i
    scene_stack->addRect(i1 + width / 2, y, width / 2, height, pen, brush);
    name = scene_stack->addText(QString::number(j1_info));
    name->setPos(i1 + width / 2 + 12, y + 4);
    //второй элемент j
    scene_stack->addRect(j1 + width / 2, y, width / 2, height, pen, brush);
    name = scene_stack->addText(QString::number(i1_info));
    name->setPos(j1 + width / 2 + 12, y + 4);
}

void Display::Paint_Queue_Swap_Pointer(int x, QString string, bool isDelete)
{
    QPen pen(Qt::black);
    QBrush brush(Qt::white);
    //QGraphicsTextItem *name = NULL;

    if (isDelete)
    {
        pen.setColor(Qt::white);
        scene_queue->addRect(x + 5, y + height + 1, width / 2 - 5, height * 2, pen, brush);
    }
    else
    {
        Paint_Queue_Pointer_down(x, string);
    }
}
void Display::Paint_Stack_Swap_Pointer(int x, QString string, bool isDelete)
{
    QPen pen(Qt::black);
    QBrush brush(Qt::white);
    //QGraphicsTextItem *name = NULL;

    if (isDelete)
    {
        pen.setColor(Qt::white);
        scene_stack->addRect(x + 5, y + height + 1, width / 2 - 5, height * 2, pen, brush);
    }
    else
    {
        Paint_Stack_Pointer_down(x, string);
    }
}

void Display::Paint_Queue_pred_curr(int number, int pred, int curr, QString pred_s, QString curr_s, int predmax, int max)
{
    ui->pushButton_next->setEnabled(true);
    emit offAll();
    ui->graphicsView->setScene(scene_queue);

    QPen pen(Qt::black);
    QBrush brush(Qt::white);
    QGraphicsTextItem *name = NULL;

    pen.setColor(Qt::white);

    this->number = number;

    if (predmax == -1 && max == -1)
    {
        i1 = field + (width + (length - width / 4)) * curr;
        if (number != curr)
        {
            //рисуем curr снизу
            pen.setColor(Qt::black);
            Paint_Queue_Pointer_down(i1 + width / 2, curr_s);
            flag = true;
        }
        else
        {
            pen.setColor(Qt::black);
            //пишем NIL
            scene_queue->addRect(i1 + width / 2 + 5, y + 2 * height, width / 2 - 10, height / 2, pen, brush);
            name = scene_queue->addText(curr_s);
            name->setPos(i1 + width / 2 + 5, y + 2 * height + field + 2);
            name = scene_queue->addText("NIL");
            name->setPos(i1 + width / 2 + 5, y + 2 * height - 5);
        }
    }
    else
    {
        //рисуем curr сверху
        i1 = field + (width + (length - width / 4)) * curr;
        if (number != curr)
        {
            //рисуем
            Paint_Queue_Pointer_up(i1 + width / 2, curr_s);
        }
        else
        {
            //рисуем NIL
            pen.setColor(Qt::black);
            scene_queue->addRect(i1 + width / 2 + 5, field + height / 2, width / 2 - 10, height / 2, pen, brush);
            name = scene_queue->addText(curr_s);
            name->setPos(i1 + width / 2 + 5, 3);
            name = scene_queue->addText("NIL");
            name->setPos(i1 + width / 2 + 5, field + height / 2 - 5);
        }

        //рисуем max
        m1 = field + (width + (length - width / 4)) * max;
        Paint_Queue_Pointer_down(m1 + width / 2, "max");

        //рисуем predmax
        pm1 = field + (width + (length - width / 4)) * predmax;
        Paint_Queue_Pointer_down(pm1, "prmax");
    }

    //рисуем pred
    j1 = field + (width + (length - width / 4)) * pred;
    Paint_Queue_Pointer_up(j1 + width / 2, pred_s);

    operation = 4;
    time = 3;
}

void Display::Paint_Stack_pred_curr(int number, int pred, int curr, QString pred_s, QString curr_s, int predmax, int max)
{
    ui->pushButton_next->setEnabled(true);
    emit offAll();
    ui->graphicsView->setScene(scene_stack);

    QPen pen(Qt::black);
    QBrush brush(Qt::white);
    QGraphicsTextItem *name = NULL;

    if (predmax == -1 && max == -1)
    {
        //рисуем curr снизу
        if (number != curr)
        {
            //рисуем
            i1 = field + (width + (length - width / 4)) * (number - curr - 1);
            Paint_Stack_Pointer_down(i1, curr_s);
        }
        else
        {
            pen.setColor(Qt::black);
            //рисуем NIL
            scene_stack->addRect(i1 + 5, y + 2 * height, width / 2 - 10, height / 2, pen, brush);
            name = scene_stack->addText(curr_s);
            name->setPos(i1 + 5, y + 2 * height + field + 2);
            name = scene_stack->addText("NIL");
            name->setPos(i1 + 5, y + 2 * height - 5);
        }
    }
    else
    {
        //рисуем curr сверху
        if (number != curr)
        {
            //рисуем
            i1 = field + (width + (length - width / 4)) * (number - curr - 1);
            Paint_Stack_Pointer_up(i1, curr_s);
        }
        else
        {
            //рисуем NIL
            scene_stack->addRect(i1 + 5, field + height / 2, width / 2 - 10, height / 2, pen, brush);
            name = scene_stack->addText(curr_s);
            name->setPos(i1 + 5, 3);
            name = scene_stack->addText("NIL");
            name->setPos(i1 + 5, field + height / 2 - 5);
            flag = true;
        }

        //рисуем max
        m1 = field + (width + (length - width / 4)) * (number - max - 1);
        Paint_Stack_Pointer_down(m1 + width / 2, "max");
        //рисуем predmax
        pm1 = field + (width + (length - width / 4)) * (number - predmax - 1);
        Paint_Stack_Pointer_down(pm1, "prmax");
    }
    if (!flag)
    {
        //рисуем pred
        j1 = field + (width + (length - width / 4)) * (number - pred - 1);
        Paint_Stack_Pointer_up(j1, pred_s);
    }
    else
        flag = false;

    operation = 4;
    time = 1;
}

void Display::Timer_Elapsed()
{
    QPen pen(Qt::white);
    QBrush brush(Qt::white);
    QGraphicsTextItem *name = NULL;
    switch (operation)
    {
        case 1:
            if (isAdd)
            {
                switch (time)
                {
                case 0:
                    if (info)
                    {
                        ui->label->setText("Переставляем last на новый элемент.");
                        emit markQueue(14);
                        //стираем старый last
                        pen.setColor(Qt::white);
                        scene_queue->addRect(x - width - width / 4, y + height + 1, width / 2, 2 * height , pen, brush);
                        //пишем last и рисуем вокруг него прямоугольник и стрелочку один раз
                        pen.setColor(Qt::black);
                        Paint_Queue_Pointer_down(x, "last");
                        isAdd = true;
                        operation = 1;
                        time++;
                        break;
                    }
                    else
                    {
                        ui->label->setText("Обнуляем указатель последнего элемента.");
                        emit markQueue(20);
                        //записываем в last.next NIL
                        pen.setColor(Qt::black);
                        scene_queue->addRect(x - width / 4 - width / 2, y, width / 2, height, pen, brush);
                        name = scene_queue->addText("NIL");
                        name->setPos(x - width / 4 - width / 2 + 7, y + 4);
                        //стираем стрелочку
                        pen.setColor(Qt::white);
                        scene_queue->addRect(x - width / 4 + 1, y, width / 4 - 2, height, pen, brush);
                        pen.setColor(Qt::black);

                        isAdd = true;
                        operation = 1;
                        time = 6;
                        break;
                    }
                case 1:
                    ui->label->setText("Создаем новый элемент.");
                    emit markQueue(15);
                    //стираем curr и стрелочки
                    pen.setColor(Qt::white);
                    scene_queue->addRect(x + width / 2 + 1, field, width * 2, (y - 1) - field, pen, brush);
                    //пишем новый curr справа
                    pen.setColor(Qt::black);
                    Paint_Queue_Pointer_up(x + width + width / 4 + width / 2, "curr");
                    //рисуем элемент справа
                    //сам элемент
                    //прямоугольники
                    scene_queue->addRect(x + width + width / 4, y, width / 2, height, pen, brush);
                    scene_queue->addRect(x + width + width / 4 + width / 2, y, width / 2, height, pen, brush);

                    isAdd = true;
                    operation = 1;
                    time++;
                    break;
                case 2:
                    ui->label->setText("Соединяем last с новым элементом");
                    emit markQueue(16);
                    //стрелочка
                    pen.setColor(Qt::black);
                    scene_queue->addRect(x + width + width / 4 - width / 2 - width / 4, y, width / 2, height, pen, brush);
                    scene_queue->addLine(x + width + width / 4 - width / 2, y + height / 2, x + width + width / 4, y + height / 2, pen);
                    scene_queue->addLine(x + width + width / 4, y + height / 2, x + width + width / 4 - 6, y + height / 2 - 3, pen);
                    scene_queue->addLine(x + width + width / 4, y + height / 2, x + width + width / 4 - 6, y + height / 2 + 3, pen);

                    isAdd = true;
                    operation = 1;
                    time++;
                    break;
                case 3:
                    ui->label->setText("Записываем в last новое значение.  Для окончания добавления введите 0.");
                    emit markQueue(17);
                    pen.setColor(Qt::black);
                    scene_queue->addRect(x, y, width / 2, height, pen, brush);
                    name = scene_queue->addText(QString::number(info));
                    name->setPos(x + 12, y + 4);

                    isAdd = true;
                    operation = 1;
                    time++;

                    ui->pushButton_next->setEnabled(false);

                    ui->label_flag->setText(" ");

                    emit offAll();
                    emit onAdd();
                    operation = 0;
                    break;
                case 5:
                    ui->label->setText("Устанавливаем first на него.");
                    emit markQueue(12);
                    //пишем first и рисуем вокруг него прямоугольник и стрелочку один раз
                    pen.setColor(Qt::black);
                    Paint_Queue_Pointer_up(x, "first");

                    isAdd = true;
                    operation = 1;
                    time = 0;
                    break;
                case 6:
                    ui->label->setText("Стираем curr. Добавление закончено.");
                    emit markQueue(21);
                    ui->label_flag->clear();

                    //стираем curr
                    pen.setColor(Qt::white);
                    scene_queue->addRect(x - width / 4 + 1, field, width * 3, 4 * height, pen, brush);
                    //стираем last
                    pen.setColor(Qt::white);
                    scene_queue->addRect(x - width - width / 4, y + height + 1, width / 2, 2 * height , pen, brush);

                    ui->pushButton_next->setEnabled(false);
                    emit onAll();

                    break;
                }
            }
            else
            {
                QPen pen(Qt::white);
                QBrush brush(Qt::white);
                switch (time)
                {
                case 0:
                    ui->label->setText("Переставляем curr на следующий элемент.");
                    emit markRemove(8);

                    //стираем curr
                    pen.setColor(Qt::white);
                    scene_queue->addRect(x + width / 2 + 5, y + height + 1, width / 2 - 5, 2 * height, pen, brush);
                    //рисуем curr
                    pen.setColor(Qt::black);
                    Paint_Queue_Pointer_down(x + width + width / 4 + width / 2, "curr");

                    isAdd = false;
                    operation = 1;
                    time++;
                    break;
                case 1:
                    ui->label->setText("Стираем первый элемент.");
                    emit markRemove(9);

                    //стираем первый элемент
                    scene_queue->addRect(x, field, width + width / 4 - 1, height * 3, pen, brush);

                    isAdd = false;
                    operation = 1;
                    time++;
                    break;
                case 2:
                    ui->label->setText("Устанавливаем first на curr.");
                    emit markRemove(10);
                    //рисуем first
                    pen.setColor(Qt::black);
                    Paint_Queue_Pointer_up(x + width + width / 4, "first");

                    isAdd = false;
                    operation = 1;
                    time++;
                    break;
                case 3:
                    ui->label->setText("Устанавливаем pred на first.");
                    emit markRemove(11);
                    //рисуем pred
                    pen.setColor(Qt::black);
                    Paint_Queue_Pointer_up(x + width + width / 4 + width / 2, "pred");

                    isAdd = false;
                    operation = 1;
                    time++;
                    break;
                case 4:
                    ui->label->setText("Удаление закончено.");
                    //стираем pred
                    pen.setColor(Qt::white);
                    scene_queue->addRect(x + width + width / 4 + width / 2 + 5, field, width / 2 - 5, (y - 1) - field, pen, brush);
                    //стираем curr
                    scene_queue->addRect(x + width / 2 + width + width / 4 + 5, y + height + 1, width / 2 - 5, 2 * height, pen, brush);
                    ui->pushButton_next->setEnabled(false);
                    emit onAll();
                    operation = 0;
                    break;
                }
            }
            break;
        case 2:
            if (isAdd)
            {
                switch (time)
                {
                case -1:
                    if (info)
                    {
                        ui->label->setText("Создаем новый элемент.");

                        emit markStack(11);

                        //стираем старый temp
                        pen.setColor(Qt::white);
                        scene_stack->addRect(x - width - width / 4, 0, width / 2 - 1, y - 1, pen, brush);
                        pen.setColor(Qt::black);
                        //пишем temp
                        Paint_Stack_Pointer_up(x, "temp");

                        if (!number)
                        {
                            //scene_stack->clear();
                            //рисуем единственный элемент
                            Paint_1_elem_stack(true);
                            //запускаем таймер
                            isAdd = true;
                            operation = 2;
                            time = 3;
                        }
                        else
                        {
                            //рисуем элемент
                            Paint_1_elem_stack(false);
                            //запускаем таймер
                            isAdd = true;
                            operation = 2;
                            time = 0;
                        }
                    }
                    else
                    {
                        ui->label->setText("Добавление закончено.");
                        emit markStack(17);
                        ui->label_flag->clear();

                        pen.setColor(Qt::white);
                        //стираем temp
                        scene_stack->addRect(x - width - width / 4, 0, width / 2 - 1, y - 1 , pen, brush);

                        ui->pushButton_next->setEnabled(false);
                        emit onAll();
                        operation = 0;
                    }
                    break;
                case 0:
                    ui->label->setText("Соединяем новый элемент с предыдущим.");
                    emit markStack(12);
                    //рисуем пустой элемент со стрелкой
                    Paint_1_elem_stack(true);

                    isAdd = true;
                    operation = 2;
                    time++;

                    break;
                case 1:
                    ui->label->setText("Записываем в новый элемент новое значение.");
                    emit markStack(13);
                    //пишем записываем новое значение
                    //прямоугольник
                    pen.setColor(Qt::black);
                    scene_stack->addRect(x + width / 2, y, width / 2, height, pen, brush);
                    //текст
                    name = scene_stack->addText(QString::number(info));
                    name->setPos(x + width / 2 + 12, y + 4);

                    isAdd = true;
                    operation = 2;
                    time++;
                    break;
                case 2:
                    ui->label->setText("Переставляем указатель first на новый элемент. Для окончания добавления введите 0.");
                    emit markStack(14);
                    //стираем старый first и стрелочку
                    scene_stack->addRect(x - width / 2 - width / 4, 0, width / 2, y - 1 , pen, brush);
                    //пишем first и рисуем стрелочку
                    pen.setColor(Qt::black);
                    Paint_Stack_Pointer_up(x + width / 2, "first");

                    time = 0;

                    ui->pushButton_next->setEnabled(false);
                    emit offAll();
                    emit onAdd();

                    operation = 0;

                    ui->label_flag->setText(" ");

                    break;
                case 3:
                    ui->label->setText("Соединяем элемент с предыдущим (в данном случае, его нет).");
                    emit markStack(12);

                    name = scene_stack->addText("NIL");
                    name->setPos(x + 7, y + 4);

                    isAdd = true;
                    operation = 2;
                    time++;
                    break;
                case 4:
                    ui->label->setText("Записываем в него новое значение.");
                    emit markStack(13);

                    name = scene_stack->addText(QString::number(info));
                    name->setPos(x + width / 2 + 12, y + 4);

                    isAdd = true;
                    operation = 2;
                    time = 2;
                    break;
                }
            }
            else
            {
                QPen pen(Qt::white);
                QBrush brush(Qt::white);
                switch (time)
                {
                case 0:
                {
                    ui->label->setText("Переставляем curr на следующий элемент.");
                    emit markRemove(8);

                    //стираем curr
                    pen.setColor(Qt::white);
                    scene_stack->addRect(x , y + height + 1, width / 2 - 1, 2 * height, pen, brush);
                    //рисуем curr
                    pen.setColor(Qt::black);
                    Paint_Stack_Pointer_down(x - width - width / 4, "curr");

                    isAdd = false;
                    operation = 2;
                    time++;
                    break;
                }
                case 1:
                    ui->label->setText("Стираем первый элемент.");
                    emit markRemove(9);

                    //стираем первый элемент
                    pen.setColor(Qt::white);
                    scene_stack->addRect(x - width / 4 + 1, field, width + width / 4 , height * 3, pen, brush);

                    isAdd = false;
                    operation = 2;
                    time++;
                    break;
                case 2:
                    ui->label->setText("Устанавливаем first на curr.");
                    emit markRemove(10);
                    //рисуем first
                    pen.setColor(Qt::black);
                    Paint_Stack_Pointer_up(x - width - width / 4 + width / 2, "first");

                    isAdd = false;
                    operation = 2;
                    time++;
                    break;
                case 3:
                    ui->label->setText("Устанавливаем pred на first.");
                    emit markRemove(11);
                    //рисуем pred
                    pen.setColor(Qt::black);
                    Paint_Stack_Pointer_up(x - width - width / 4, "pred");

                    isAdd = false;
                    operation = 2;
                    time++;
                    break;
                case 4:
                    ui->label->setText("Удаление закончено.");
                    //стираем pred
                    pen.setColor(Qt::white);
                    scene_stack->addRect(x - width - width / 4 + 5, field, width / 2 - 10, (y - 1) - field, pen, brush);
                    //стираем curr
                    scene_stack->addRect(x - width - width / 4 + 5, y + height + 1, width / 2 - 5, 2 * height, pen, brush);
                    ui->pushButton_next->setEnabled(false);
                    emit onAll();
                    operation = 0;
                    break;
                }
            }
        break;
    case 3:
        switch (time)
        {
        case 0:
            //переставляем местами i и j
            Paint_Queue_Swap_do(i1, j1, i1_info, j1_info);

            //стираем j и i указатели
            Paint_Queue_Swap_Pointer(i1, i1_name, true);
            Paint_Queue_Swap_Pointer(j1, j1_name, true);

            ui->pushButton_next->setEnabled(false);
            emit onAll();
            operation = 0;
            break;
        case 2:
            //стираем i и j указатели
            Paint_Queue_Swap_Pointer(i1, i1_name, true);
            Paint_Queue_Swap_Pointer(j1, j1_name, true);

            ui->pushButton_next->setEnabled(false);
            emit onAll();
            operation = 0;
            break;
        case 3:
            //переставляем местами i и j
            Paint_Stack_Swap_do(i1, j1, i1_info, j1_info);

            //стираем j и i  указатели
            Paint_Stack_Swap_Pointer(i1, i1_name, true);
            Paint_Stack_Swap_Pointer(j1, j1_name, true);

            ui->pushButton_next->setEnabled(false);
            emit onAll();
            operation = 0;
            break;
        case 5:
            //стираем i и j указатели
            Paint_Stack_Swap_Pointer(i1, i1_name, true);
            Paint_Stack_Swap_Pointer(j1, j1_name, true);

            ui->pushButton_next->setEnabled(false);
            emit onAll();
            operation = 0;
            break;
        }
        break;
    case 4:
        switch (time)
        {
        case 3:
            pen.setColor(Qt::white);
            //стираем curr
            scene_queue->addRect(i1 + width / 2 + 5, y + height + 1, width / 2 - 5, 2 * height, pen, brush);
            scene_queue->addRect(i1 + width / 2 + 5, field, width / 2 - 5, (y - 1) - field, pen, brush);
            //стираем pred
            scene_queue->addRect(j1 + width / 2 + 5, field, width / 2 - 5, (y - 1) - field, pen, brush);
            //стираем max
            scene_queue->addRect(m1 + width / 2 + 5, y + height + 1, width / 2 - 5, 2 * height, pen, brush);
            //стираем predmax
            scene_queue->addRect(pm1 + 5, y + height + 1, width / 2 - 5, 2 * height, pen, brush);

            ui->pushButton_next->setEnabled(false);
            emit onAll();
            operation = 0;
            break;
        case 1:
            pen.setColor(Qt::white);
            //стираем curr
            scene_stack->addRect(i1 + 5, y + height + 1, width / 2 - 5, 2 * height, pen, brush);
            scene_stack->addRect(i1 + 5, field, width / 2 - 10, (y - 1) - field, pen, brush);
            //стираем pred
            scene_stack->addRect(j1 + 5, field, width / 2 - 10, (y - 1) - field, pen, brush);
            //стираем max
            scene_stack->addRect(m1 + width / 2 + 5, y + height + 1, width / 2 - 5, 2 * height, pen, brush);
            //стираем predmax
            scene_stack->addRect(pm1 + 5, y + height + 1, width / 2 - 5, 2 * height, pen, brush);

            ui->pushButton_next->setEnabled(false);
            emit onAll();
            operation = 0;
            break;
        }
        break;
    case 5:
        switch (time)
        {
        case 20:
            ui->label->setText("Соединяем предыдущий элемент и следующий.");
            emit markRemove(14);

            //стираем старую стрелочку
            pen.setColor(Qt::white);
            scene_queue->addRect(x - width / 4 + 1, y, width / 4 - 2, height * 3, pen, brush);
            pen.setColor(Qt::black);
            scene_queue->addRect(x - width / 2 - width / 4, y, width / 2, height, pen, brush);
            //рисуем стрелочку
            scene_queue->addLine(x - width / 2, y + height / 2, x + width + width / 4, y + height / 2, pen);
            scene_queue->addLine(x + width + width / 4, y + height / 2, x + width + width / 4 - 6, y + height / 2 - 3, pen);
            scene_queue->addLine(x + width + width / 4, y + height / 2, x + width + width / 4 - 6, y + height / 2 + 3, pen);

            operation = 5;
            time++;
            break;
        case 21:
            ui->label->setText("Удаляем текущий элемент.");
            emit markRemove(15);

            //закрашиваем часть стрелочки внутри предыдущего элемента
            scene_queue->addRect(x - width / 2, y + height / 2 + 1, width / 4 - 1, height / 2 - 2, pen, brush);
            //закрашиваем все остальное
            scene_queue->addRect(x - width / 4 + 1, y + height / 2 + 1, width + width / 2 - 2, height * 4, pen, brush);
            //дорисовываем нижнюю часть стрелочки
            pen.setColor(Qt::black);
            scene_queue->addLine(x + width + width / 4, y + height / 2, x + width + width / 4 - 6, y + height / 2 + 3, pen);

            operation = 5;
            time++;
            break;
        case 22:
            ui->label->setText("Устанавливаем curr на следующий элемент.");
            emit markRemove(16);

            //рисуем curr
            pen.setColor(Qt::black);
            Paint_Queue_Pointer_down(x + width + width / 4 + width / 2, "curr");

            operation = 5;
            time++;
            break;
        case 23:
            ui->label->setText("Удаление завершено.");
            emit markRemove(17);
            //стираем curr
            pen.setColor(Qt::white);
            scene_queue->addRect(x + width / 2 + width + width / 4 + 5, y + height + 1, width / 2 - 5, height * 2, pen, brush);
            //стираем pred
            scene_queue->addRect(x - width / 2 - width / 4 + 5, field, width / 2 - 5, (y - 1) - field, pen, brush);

            ui->pushButton_next->setEnabled(false);
            emit onAll();
            operation = 0;
            break;
        case 24:
            ui->label->setText("Удаляем текущий элемент.");
            emit markRemove(15);

            //удаляем элемент
            pen.setColor(Qt::white);
            scene_queue->addRect(x - width / 4 + 1, y, width + width / 4, height * 3, pen, brush);

            operation = 5;
            time++;
            break;
        case 25:
            ui->label->setText("Переставляем curr на следующий (все равно NIL). Удаление завершено.");
            emit markRemove(17);

            ui->pushButton_next->setEnabled(false);
            emit onAll();
            operation = 0;
            break;
        }
        break;
    case 6:
        switch (time)
        {
        case 30:
            ui->label->setText("Соединяем предыдущий элемент и следующий.");
            emit markRemove(14);

            //стираем стрелочку старую
            scene_stack->addRect(x + width + 1, y, width / 4 - 2, height * 2, pen, brush);
            pen.setColor(Qt::black);
            scene_stack->addRect(x + width + width / 4, y, width / 2, height, pen, brush);
            //рисуем стрелочку
            scene_stack->addLine(x + width + width / 2, y + height / 2, x - width / 4, y + height / 2, pen);
            scene_stack->addLine(x - width / 4, y + height / 2, x - width / 4 + 6, y + height / 2 - 3, pen);
            scene_stack->addLine(x - width / 4, y + height / 2, x - width / 4 + 6, y + height / 2 + 3, pen);

            operation = 6;
            time++;
            break;
        case 31:
            ui->label->setText("Удаляем текущий элемент.");
            emit markRemove(15);

            //закрашиваем часть стрелочки внутри предыдущего элемента
            scene_stack->addRect(x + width + width / 4 + 1, y + height / 2 + 1, width / 4 - 1, height / 2 - 2, pen, brush);
            //закрашиваем все остальное
            scene_stack->addRect(x - width / 4 + 1, y + height / 2 + 1, width + width / 2 - 2, height * 4, pen, brush);
            //дорисовываем нижнюю часть стрелочки
            pen.setColor(Qt::black);
            scene_stack->addLine(x - width / 4, y + height / 2, x - width / 4 + 6, y + height / 2 + 3, pen);

            operation = 6;
            time++;
            break;
        case 32:
            ui->label->setText("Устанавливаем curr на следующий элемент.");
            emit markRemove(16);

            //рисуем curr
            pen.setColor(Qt::black);
            Paint_Stack_Pointer_down(x - width - width / 4, "curr");

            operation = 6;
            time++;
            break;
        case 33:
            ui->label->setText("Удаление завершено.");
            emit markRemove(17);

            //стираем curr
            pen.setColor(Qt::white);
            scene_stack->addRect(x - width - width / 4 + 5, y + height + 1, width / 2 - 5, height * 2, pen, brush);
            //стираем pred
            scene_stack->addRect(x + width + width / 4 + 5, field, width / 2 - 4, (y - 1) - field, pen, brush);

            ui->pushButton_next->setEnabled(false);
            emit onAll();
            operation = 0;
            break;
        case 6:
            ui->label->setText("Удаляем текущий элемент.");
            emit markRemove(15);

            pen.setColor(Qt::white);
            scene_stack->addRect(x, y, width, height * 3, pen, brush);

            operation = 6;
            time++;
            break;
        case 7:
            ui->label->setText("Устанавливаем curr на следующий элемент (curr = NIL).");
            emit markRemove(16);
            //стираем curr
            pen.setColor(Qt::white);
            scene_stack->addRect(x - width - width / 4 + 5, y + height + 1, width / 2 - 5, height * 2, pen, brush);

            operation = 6;
            time++;
            break;
        case 8:
            ui->label->setText("Удаление завершено.");
            emit markRemove(17);

            //стираем pred
            scene_stack->addRect(x + width + width / 4 + 5, field, width / 2 - 4, (y - 1) - field, pen, brush);

            ui->pushButton_next->setEnabled(false);
            emit onAll();
            operation = 0;
            break;
        }
        break;
    case 7:
        switch (time)
        {
        case 11:
            ui->label->setText("Создаем элементы 100 и 1000.");
            emit markInsert(13);

            //рисуем элемент r100
            pen.setColor(Qt::black);
            scene_queue->addRect(x, y + height, width / 2, height, pen, brush);
            scene_queue->addRect(x + width / 2, y + height, width / 2, height, pen, brush);
            //рисуем указатель r100
            scene_queue->addRect(x + 5, y + height / 2 + 2 * height, width / 2 - 5, height / 2, pen, brush);
            scene_queue->addLine(x + width / 4, y + height - height / 4 + 2 * height + 1, x + width / 4, y + height + height, pen);
            scene_queue->addLine(x + width / 4, y + height + height + 1, x + width / 4 - 3, y + height + height + 5, pen);
            scene_queue->addLine(x + width / 4, y + height + height + 1, x + width / 4 + 3, y + height + height + 5, pen);
            name = scene_queue->addText("r100");
            name->setPos(x + 10, y + height + 2 * height + 3);

            //рисуем элемент r1000
            pen.setColor(Qt::black);
            scene_queue->addRect(x + 2 * (width + width / 4), y + height, width / 2, height, pen, brush);
            scene_queue->addRect(x + 2 * (width + width / 4) + width / 2, y + height, width / 2, height, pen, brush);
            //рисуем указатель r1000
            scene_queue->addRect(x + 2 * (width + width / 4) + 5, y + height / 2 + 2 * height, width / 2 - 5, height / 2, pen, brush);
            scene_queue->addLine(x + 2 * (width + width / 4) + width / 4, y + height - height / 4 + 2 * height + 1, x + 2 * (width + width / 4) + width / 4, y + height + height, pen);
            scene_queue->addLine(x + 2 * (width + width / 4) + width / 4, y + height + height + 1, x + 2 * (width + width / 4) + width / 4 - 3, y + height + height + 5, pen);
            scene_queue->addLine(x + 2 * (width + width / 4) + width / 4, y + height + height + 1, x + 2 * (width + width / 4) + width / 4 + 3, y + height + height + 5, pen);
            name = scene_queue->addText("r1000");
            name->setPos(x + 2 * (width + width / 4) + 10, y + height + 2 * height + 3);

            operation = 7;
            time ++;
            break;
        case 12:
            ui->label->setText("Записываем в них значения.");
            emit markInsert(14);

            name = scene_queue->addText("100");
            name->setPos(x + 12, y + height + 4);

            name = scene_queue->addText("1000");
            name->setPos(x + 2 * (width + width / 4) + 12, y + height + 4);

            operation = 7;
            time++;
            break;
        case 13:
            ui->label->setText("Присоединяем 1000 элемент.");
            emit markInsert(15);

            //закрашиваем 1000
            pen.setColor(Qt::white);
            scene_queue->addRect(x + 2 * (width + width / 4), y, width, height * 4, pen, brush);

            //рисуем стрелочку к 1000
            pen.setColor(Qt::black);
            scene_queue->addLine(x + 2 * (width + width / 4), y + height / 2, x + 2 * (width + width / 4) - 6, y + height / 2 - 3, pen);
            scene_queue->addLine(x + 2 * (width + width / 4), y + height / 2, x + 2 * (width + width / 4) - 6, y + height / 2 + 3, pen);

            //рисуем 1000 присоединенным
            if (!isLast)
                PaintQueueElem(number, j1, 1000, false, false);
            else
                PaintQueueElem(number, j1, 1000, false, true);

            //стираем NIL в предыдущем
            scene_queue->addRect(x - width / 4 - width / 2, y, width / 2, height, pen, brush);
            scene_queue->addLine(x - width / 2, y + height / 2, x - width / 4, y + height / 2, pen);

            //рисуем указатель r1000
            Paint_Queue_Pointer_down(x, "r1000");

            operation = 7;
            time++;
            break;
        case 14:
            ui->label->setText("Присоединяем 100 элемент.");
            if (i1)
                emit markInsert(22);
            else
                emit markInsert(18);

            //закрашиваем 100
            pen.setColor(Qt::white);
            scene_queue->addRect(x - 2 * (width + width / 4), y, width, height * 4, pen, brush);

            //рисуем 100 присоединенным
            if (!isFirst)
            {
                PaintQueueElem(number, i1, 100, false, false);
                //рисуем стрелочку к 100
                pen.setColor(Qt::black);
                scene_queue->addLine(x, y + height / 2, x - 6, y + height / 2 - 3, pen);
                scene_queue->addLine(x, y + height / 2, x - 6, y + height / 2 + 3, pen);
            }
            else
                PaintQueueElem(number, i1, 100, true, false);

            pen.setColor(Qt::black);
            //рисуем указатель r100
            Paint_Queue_Pointer_down(x, "r100");

            operation = 7;
            time++;
            break;
        case 15:
            ui->label->setText("Вставка закончена.");
            emit markInsert(24);

            //стираем r100 и r1000
            scene_queue->addRect(x + 5, y + height + 1, width / 2 - 5, 2 * height, pen, brush);
            scene_queue->addRect(x + 2 * (width + width / 4) + 5, y + height + 1, width / 2 - 5, 2 * height, pen, brush);
            //стираем max и predmax
            pen.setColor(Qt::white);
            scene_queue->addRect(x - width - width / 4, y + height + 1, width, 2 * height, pen, brush);
            scene_queue->addRect(x + width + width / 4, y + height + 1, width, 2 * height, pen, brush);

            ui->pushButton_next->setEnabled(false);
            emit onAll();
            operation = 0;
            break;
        }
        break;
    case 8:
        switch (time)
        {
        case 40:
            ui->label->setText("Создаем элементы 100 и 1000.");
            emit markInsert(13);
            //рисуем элемент 1000
            pen.setColor(Qt::black);
            scene_stack->addRect(x - width - width / 4, y + height, width / 2, height, pen, brush);
            scene_stack->addRect(x - width - width / 4 + width / 2, y + height, width / 2, height, pen, brush);
            //рисуем указатель r1000
            scene_stack->addRect(x - width - width / 4 + width / 2 + 5, y + height / 2 + 2 * height, width / 2 - 5, height / 2, pen, brush);
            scene_stack->addLine(x - width - width / 4 + width / 2 + width / 4, y + height - height / 4 + 2 * height + 1, x - width - width / 4 + width / 4 + width / 2, y + height + height, pen);
            scene_stack->addLine(x - width - width / 4 + width / 2 + width / 4, y + height + height + 1, x - width - width / 4 + width / 4 + width / 2 - 3, y + height + height + 5, pen);
            scene_stack->addLine(x - width - width / 4 + width / 2 + width / 4, y + height + height + 1, x - width - width / 4 + width / 4 + width / 2 + 3, y + height + height + 5, pen);
            name = scene_stack->addText("r1000");
            name->setPos(x - width - width / 4 + width / 2 + 10, y + height + 2 * height + 3);
            //рисуем элемент 100
            pen.setColor(Qt::black);
            scene_stack->addRect(x + width + width / 4, y + height, width / 2, height, pen, brush);
            scene_stack->addRect(x + width + width / 4 + width / 2, y + height, width / 2, height, pen, brush);
            //рисуем указатель r100
            scene_stack->addRect(x + width + width / 4 + width / 2 + 5, y + height / 2 + 2 * height, width / 2 - 5, height / 2, pen, brush);
            scene_stack->addLine(x + width + width / 4 + width / 2 + width / 4, y + height - height / 4 + 2 * height + 1, x + width + width / 4 + width / 4 + width / 2, y + height + height, pen);
            scene_stack->addLine(x + width + width / 4 + width / 2 + width / 4, y + height + height + 1, x + width + width / 4 + width / 4 + width / 2 - 3, y + height + height + 5, pen);
            scene_stack->addLine(x + width + width / 4 + width / 2 + width / 4, y + height + height + 1, x + width + width / 4 + width / 2 + width / 4 + 3, y + height + height + 5, pen);
            name = scene_stack->addText("r100");
            name->setPos(x + width + width / 4 + width / 2 + 8, y + height + 2 * height + 3);

            operation = 8;
            time ++;
            break;
        case 41:
            ui->label->setText("Записываем в них значения.");
            emit markInsert(14);

            name = scene_stack->addText(QString::number(100));
            name->setPos(x + width + width / 4 + width / 2 + 15, y + height + 4);

            name = scene_stack->addText(QString::number(1000));
            name->setPos(x - width - width / 4 + width / 2 + 12, y + height + 4);

            operation = 8;
            time++;
            break;
        case 42:
            ui->label->setText("Присоединяем 1000 элемент.");
            emit markInsert(15);

            //закрашиваем 1000
            pen.setColor(Qt::white);
            scene_stack->addRect(x - width - width / 4, y, width, height * 4, pen, brush);

            //рисуем 1000 присоединенным
            if (!isLast)
                PaintStackElem(number, j1, 1000, false, false);
            else
                PaintStackElem(number, j1, 1000, false, true);

            pen.setColor(Qt::black);

            //закрашиваем NIL
            scene_stack->addRect(x + width + width / 4, y, width / 2, height, pen, brush);
            scene_stack->addLine(x + width + width / 4, y + height / 2, x + width + width / 2, y + height / 2, pen);

            //рисуем указатель r1000
            Paint_Stack_Pointer_down(x + width / 2, "r1000");

            //рисуем стрелочку к 1000
            scene_stack->addLine(x + width, y + height / 2, x + width + 6, y + height / 2 - 3, pen);
            scene_stack->addLine(x + width, y + height / 2, x + width + 6, y + height / 2 + 3, pen);

            operation = 8;
            time++;
            break;
        case 43:
            ui->label->setText("Присоединяем 100 элемент.");
            if (i1)
                emit markInsert(22);
            else
                emit markInsert(18);

            //закрашиваем 100
            pen.setColor(Qt::white);
            scene_stack->addRect(x + 2 * (width + width / 4), y, width, height * 4, pen, brush);

            //рисуем 100 присоединенным
            if (!isFirst)
            {
                PaintStackElem(number, i1, 100, false, false);
                //рисуем стрелочку к 100
                pen.setColor(Qt::black);
                scene_stack->addLine(x + width, y + height / 2, x + width + 6, y + height / 2 - 3, pen);
                scene_stack->addLine(x + width, y + height / 2, x + width + 6, y + height / 2 + 3, pen);
            }
            else
            {
                PaintStackElem(number, i1, 100, true, false);
                //закрашиваем first
                scene_stack->addRect(x - width - width / 4, field, width, y - field - 1, pen, brush);
            }

            pen.setColor(Qt::black);
            //рисуем указатель r100
            Paint_Stack_Pointer_down(x + width / 2, "r100");

            operation = 8;
            time = 50;
            break;
        case 50:
            ui->label->setText("Вставка закончена.");
            emit markInsert(24);

            //стираем prmax и max
            pen.setColor(Qt::white);
            scene_stack->addRect(x - width - width / 4, y + height + 1, width, 2 * height, pen, brush);
            scene_stack->addRect(x + width + width / 4, y + height + 1, width, 2 * height, pen, brush);
            //закрашиваем r100 и r1000
            scene_stack->addRect(x + width / 2 + 5, y + height + 1, width / 2 - 5, 2 * height, pen, brush);
            scene_stack->addRect(x - 2 * (width + width / 4) + width / 2 + 5, y + height + 1, width / 2 - 5, 2 * height, pen, brush);

            ui->pushButton_next->setEnabled(false);
            emit onAll();
            operation = 0;
            break;
        case 44:
            if (i1)
                emit setLabel("Переставляем указатели на следующий элементов lst и tail. Глубина: " + QString::number(i1));
            else
            {
                emit setLabel("Переставляем указатели на следующий элементов lst и tail. Глубина: " + QString::number(i1));
                emit setLabelFlag("Реверс завершен, переставляем first на NewHead (вернем список в начальный вид).");
            }
            emit markReverse(10);

            pen.setColor(Qt::black);
            //рисуем новый lst
            scene_queue->addRect(x, y, width / 2, height, pen, brush);
            scene_queue->addRect(x + width / 2, y, width / 2, height, pen, brush);
            //пишем значение lst справа
            name = scene_queue->addText(QString::number(info));
            name->setPos(x + width / 2 + 12, y + 4);
            //рисуем новый tail
            scene_queue->addRect(x + width + width / 4, y, width / 2, height, pen, brush);
            scene_queue->addRect(x + width + width / 4 + width / 2, y, width / 2, height, pen, brush);
            //пишем значение tail справа
            name = scene_queue->addText(QString::number(j1));
            name->setPos(x + width + width / 4 + width / 2 + 12, y + 4);
            //закрашиваем стрелочку
            pen.setColor(Qt::white);
            scene_queue->addRect(x + width + 1, y, width / 4 - 2, height, pen, brush);
            //рисуем новую стрелочку
            pen.setColor(Qt::black);
            scene_queue->addLine(x + width, y + height / 2, x + width + width / 2, y + height / 2, pen);
            scene_queue->addLine(x + width, y + height / 2, x + width + 6, y + height / 2 - 3, pen);
            scene_queue->addLine(x + width, y + height / 2, x + width + 6, y + height / 2 + 3, pen);
            //Пишем NIL
            name = scene_queue->addText("NIL");
            name->setPos(x + 12, y + 4);

            operation = 8;
            time++;
            break;
        case 45:
            pen.setColor(Qt::white);
            //стираем указатель lst сверху
            scene_queue->addRect(x + width / 2 + 5, field, width / 2 - 5, y - field - 1, pen, brush);
            //стираем указатель tail снизу
            scene_queue->addRect(x + width + width / 4 + width / 2 + 5, y + height + 1, width / 2 - 5, 2 * height, pen, brush);

            x = field + (width + (length - width / 4)) * number;
            //стираем NewHead
            scene_queue->addRect(x + 5, y + height + 1, width / 2 - 5, 2 * height, pen, brush);

            ui->pushButton_next->setEnabled(false);
            emit onAll();
            operation = 0;
            break;
        case 46:
            if (i1)
                emit setLabel("Переставляем указатели на следующий элементов lst и tail. Глубина: " + QString::number(i1));
            else
            {
                emit setLabel("Переставляем указатели на следующий элементов lst и tail. Глубина: " + QString::number(i1));
                emit setLabelFlag("Реверс завершен, переставляем first на NewHead (вернем список в начальный вид).");
            }
            emit markReverse(10);

            pen.setColor(Qt::black);
            //рисуем новый lst
            scene_stack->addRect(x, y, width / 2, height, pen, brush);
            scene_stack->addRect(x + width / 2, y, width / 2, height, pen, brush);
            //пишем значение lst справа
            name = scene_stack->addText(QString::number(info));
            name->setPos(x + 12, y + 4);
            //рисуем новый tail
            scene_stack->addRect(x - width - width / 4, y, width / 2, height, pen, brush);
            scene_stack->addRect(x - width - width / 4 + width / 2, y, width / 2, height, pen, brush);
            //пишем значение tail справа
            name = scene_stack->addText(QString::number(j1));
            name->setPos(x - width - width / 4 + 12, y + 4);
            //закрашиваем стрелочку
            pen.setColor(Qt::white);
            scene_stack->addRect(x - width / 4 + 1, y, width / 4 - 2, height, pen, brush);
            //рисуем новую стрелочку
            pen.setColor(Qt::black);
            scene_stack->addLine(x, y + height / 2, x - width / 2, y + height / 2, pen);
            scene_stack->addLine(x, y + height / 2, x - 6, y + height / 2 - 3, pen);
            scene_stack->addLine(x, y + height / 2, x - 6, y + height / 2 + 3, pen);
            //Пишем NIL
            name = scene_stack->addText("NIL");
            name->setPos(x + width / 2 + 12, y + 4);

            operation = 8;
            time++;
            break;
        case 47:
            pen.setColor(Qt::white);
            //стираем указатель lst сверху
            scene_stack->addRect(x + 5, field, width / 2 - 10, y - field - 1, pen, brush);
            //стираем указатель tail снизу
            scene_stack->addRect(x - width - width / 4 + 5, y + height + 1, width / 2 - 5, 2 * height, pen, brush);

            x = field + (width + (length - width / 4)) * (number - number);
            //стираем NewHead
            scene_stack->addRect(x + width / 2 + 5, y + height + 1, width / 2 - 5, 2 * height, pen, brush);

            ui->pushButton_next->setEnabled(false);
            emit onAll();
            operation = 0;
            break;
        }
        break;
    case 9:
        switch (time)
        {
        case -10:
            if (info)
            {
                ui->label->setText("Создаем новый элемент.");

                emit markDoubleStack(3);

                //стираем старый p
                scene_doubleStack->addRect(x - width / 2 - width / 4, y + 3 * height + 1, width / 2 - 1, y - 1, QPen(Qt::white), QBrush(Qt::white));
                pen.setColor(Qt::black);
                //пишем p
                Paint_DoubleStack_Pointer_down(x + width / 2, "p");

                if (!number)
                {
                    //scene_stack->clear();
                    //рисуем единственный элемент
                    Paint_1_elem_DoubleStack(true);
                    //запускаем таймер
                    isAdd = true;
                    operation = 9;
                    time = 3;
                }
                else
                {
                    //рисуем элемент
                    Paint_1_elem_DoubleStack(false);
                    //запускаем таймер
                    isAdd = true;
                    operation = 9;
                    time = 0;
                }
            }
            else
            {
                ui->label->setText("Добавление закончено.");
                emit markDoubleStack(10);
                ui->label_flag->clear();

                pen.setColor(Qt::white);
                //стираем temp
                scene_doubleStack->addRect(x - width / 2 - width / 4, y + 3 * height + 1, width / 2 - 1, y - 1, QPen(Qt::white), QBrush(Qt::white));

                ui->pushButton_next->setEnabled(false);
                emit onAll();
                operation = 0;
            }
            break;
        case 0:
            ui->label->setText("Записываем в него новое значение.");
            emit markDoubleStack(4);
            //пишем записываем новое значение
            //прямоугольник
            pen.setColor(Qt::black);
            scene_doubleStack->addRect(x + width / 2, y, width / 2, height, pen, brush);
            //текст
            name = scene_doubleStack->addText(QString::number(info));
            name->setPos(x + width / 2 + 12, y + 4);

            operation = 9;
            time++;
            break;
        case 1:
            ui->label->setText("Соединяем предыдущий элемент с новым.");
            emit markDoubleStack(6);
            scene_doubleStack->addRect(x - width / 4 - width / 2, y + 2 * height, width / 2, height, QPen(Qt::black), QBrush(Qt::white));
            scene_doubleStack->addLine(x + width / 2, y + 2 * height + height / 2, x - width / 2, y + 2 * height + height / 2);
            scene_doubleStack->addLine(x + width / 2, y + 2 * height + height / 2, x + width / 2 - 6, y + 2 * height + height / 2 - 3);
            scene_doubleStack->addLine(x + width / 2, y + 2 * height + height / 2, x + width / 2 - 6, y + 2 * height + height / 2 + 3);

            operation = 9;
            time = 345;
            break;
        case 345:
            ui->label->setText("Соединяем новый элемент со следующим.");
            emit markDoubleStack(7);
            //рисуем пустой элемент со стрелкой
            Paint_1_elem_DoubleStack(true);

            operation = 9;
            time = 347;
            break;
        case 347:
            ui->label->setText("Соединяем новый элемент с предыдущим (присваеваем NULL, так как это новый первый элемент).");
            emit markDoubleStack(8);
            //рисуем пустой элемент со стрелкой
            name = scene_doubleStack->addText("NULL");
            name->setPos(x + width / 2 +  7, y + 2 * height + 4);

            operation = 9;
            time = 2;
            break;
        case 2:
            ui->label->setText("Переставляем указатель lst на новый элемент. Для окончания добавления введите 0.");
            emit markDoubleStack(9);
            //стираем старый first и стрелочку
            scene_doubleStack->addRect(x - width / 2 - width / 4, 0, width / 2, y - 1 , pen, brush);
            //пишем first и рисуем стрелочку
            pen.setColor(Qt::black);
            Paint_DoubleStack_Pointer_up(x + width / 2, "lst");

            time = 0;

            ui->pushButton_next->setEnabled(false);
            emit offAll();
            emit onAdd();

            operation = 0;

            ui->label_flag->setText(" ");

            break;
        case 3:
            ui->label->setText("Записываем в него новое значение.");
            emit markDoubleStack(4);

            name = scene_doubleStack->addText(QString::number(info));
            name->setPos(x + width / 2 + 12, y + 4);

            operation = 9;
            time = 123;
            break;
        case 123:
            ui->label->setText("Соединяем элемент со следующим (в данном случае, его нет).");
            emit markDoubleStack(7);

            name = scene_doubleStack->addText("NULL");
            name->setPos(x + width / 2 +  7, y + height + 4);

            operation = 9;
            time = 4;
            break;
        case 4:
            ui->label->setText("Соединяем элемент с предыдущим (в данном случае, его нет).");
            emit markDoubleStack(8);

            name = scene_doubleStack->addText("NULL");
            name->setPos(x + width / 2 +  7, y + 2 * height + 4);

            operation = 9;
            time = 2;
            break;
        }
        break;
    case 10:
        switch (time)
        {
        case -1:
            if (info)
            {
                ui->label->setText("Создаем новый элемент.");
                emit MarkCycleQueue(4);
                //стираем старый p
                scene_cycleQueue->addRect(x - width - width / 2, field, width / 2 - 1, field + height + height / 2 - 6, QPen(Qt::white), QBrush(Qt::white));
                pen.setColor(Qt::black);
                //пишем p
                Paint_CycleQueue_Pointer_up(x, "p");

                if (!number) //очередь пуста
                {
                    //рисуем единственный элемент
                    Paint_1_elem_CycleQueue(true);
                    //запускаем таймер
                    operation = 10;
                    time = 3;
                }
                else //очередь не пуста
                {
                    //рисуем элемент
                    Paint_1_elem_CycleQueue(false);
                    //запускаем таймер
                    operation = 10;
                    time = 0;
                }
            }
            else
            {
                ui->label->setText("Добавление закончено.");
                emit MarkCycleQueue(14);

                //стираем p
                scene_cycleQueue->addRect(x - width - width / 2, field, width / 2 - 1, field + height + height / 2 - 6, QPen(Qt::white), QBrush(Qt::white));

                ui->label_flag->clear();

                ui->pushButton_next->setEnabled(false);
                emit onAll();
                operation = 0;
            }
            break;
        case 0:
            ui->label->setText("Записываем в него новое значение.");
            emit MarkCycleQueue(5);
            //пишем записываем новое значение
            //прямоугольник
            pen.setColor(Qt::black);
            scene_cycleQueue->addRect(x + width / 2, y, width / 2, height, pen, brush);
            //текст
            name = scene_cycleQueue->addText(QString::number(info));
            name->setPos(x + 12, y + 4);

            operation = 10;
            time = 543;
            break;
        case 543:
            ui->label->setText("Связываем новый элемент с первым.");
            emit MarkCycleQueue(10);

            Paint_CycleQueue_Line();

            operation = 10;
            time = 867;
            break;
        case 867:
            ui->label->setText("Связываем предыдущий элемент с новым.");
            emit MarkCycleQueue(11);

            scene_cycleQueue->addRect(x - width / 2 + 1, y, width / 2 - 2, height + height / 2  - 1, QPen(Qt::white), QBrush(Qt::white));
            scene_cycleQueue->addLine(x - width / 2, y + height / 2, x, y + height / 2);
            scene_cycleQueue->addLine(x, y + height / 2, x - 6, y + height / 2 - 3);
            scene_cycleQueue->addLine(x, y + height / 2, x - 6, y + height / 2 + 3);

            operation = 10;
            time = 2;
            break;
        case 2:
            ui->label->setText("Переставляем указатель lst на новый элемент. Для окончания добавления введите 0.");
            emit MarkCycleQueue(13);
            //emit markDoubleStack(9);
            //стираем старый first и стрелочку
            scene_cycleQueue->addRect(x - width, 0, width / 2, y - 1, QPen(Qt::white), QBrush(Qt::white));
            //пишем first и рисуем стрелочку
            pen.setColor(Qt::black);
            Paint_CycleQueue_Pointer_up(x + width / 2, "lst");

            time = 0;

            ui->pushButton_next->setEnabled(false);
            emit offAll();
            emit onAdd();

            operation = 0;

            ui->label_flag->setText(" ");

            break;
        case 3:
            ui->label->setText("Записываем в него новое значение.");
            emit MarkCycleQueue(5);
            name = scene_cycleQueue->addText(QString::number(info));
            name->setPos(x + 12, y + 4);

            operation = 10;
            time++;
            break;
        case 4:
            ui->label->setText("Соединяем новый элемент с первым в очереди (в данном случае с самим собой).");
            emit MarkCycleQueue(7);

            Paint_CycleQueue_Line();

            operation = 10;
            time = 2;
            break;
        }
        break;
    }
}
