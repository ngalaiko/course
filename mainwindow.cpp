#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //запускаем окна
    wnd = new Display(this);
    wnd->show();

    wndtext = new DisplayText(this);
    wndtext->show();

    //создаем списки
    q = new Queue(wnd);
    s = new Stack(wnd);
    qd = new QueueDouble(wnd);
    sd = new StackDouble(wnd);
    qc = new QueueCycle(wnd);

    //connect для вкл/выкл кнопок
    connect(wnd, SIGNAL(offAll()), this, SLOT(Off_Buttons()));
    connect(wnd, SIGNAL(onAll()), this, SLOT(On_Buttons()));
    connect(wnd, SIGNAL(onAdd()), this, SLOT(On_Add()));

    //connect выделения кода
    connect(wnd, SIGNAL(markQueue(int)), wndtext, SLOT(queueAddMark(int)));
    connect(wnd, SIGNAL(markStack(int)), wndtext, SLOT(stackAddMark(int)));
    connect(wnd, SIGNAL(markRemove(int)), wndtext, SLOT(removeMark(int)));
    connect(wnd, SIGNAL(markInsert(int)), wndtext, SLOT(insertMark(int)));
    connect(wnd, SIGNAL(markReverse(int)), wndtext, SLOT(reverseMark(int)));
    connect(wnd, SIGNAL(markDoubleStack(int)), wndtext, SLOT(stackDoubleAddMark(int)));
    connect(wnd, SIGNAL(MarkCycleQueue(int)), wndtext, SLOT(queueCycleAddMark(int)));

    //connect добавления
    connect(q, SIGNAL(PaintAddQueueElem(int,int)), wnd, SLOT(PaintAddQueueElem(int,int)));
    connect(s, SIGNAL(PaintAddStackElem(int,int)), wnd, SLOT(PaintAddStackElem(int,int)));
    connect(qd, SIGNAL(PaintAddDoubleQueueElem(int,int)), wnd, SLOT(PaintAddDoubleQueueElem(int,int)));
    connect(sd, SIGNAL(PaintAddDoubleStackElem(int,int)), wnd, SLOT(PaintAddDoubleStackElem(int,int)));
    connect(qc, SIGNAL(PaintAddCycleQueueAdd(int,int)), wnd, SLOT(PaintAddCycleQueueAdd(int,int)));
    //connect удаления
    connect(q, SIGNAL(PaintRemoveQueueElem(int)), wnd, SLOT(PaintRemoveQueueElem(int)));
    connect(s, SIGNAL(PaintRemoveStackElem(int)), wnd, SLOT(PaintRemoveStackElem(int)));
    connect(q, SIGNAL(PaintRemoveAtQueue(int,int,int)), wnd, SLOT(PaintRemoveAtQueue(int,int,int)));
    connect(s, SIGNAL(PaintRemoveAtStack(int,int,int)), wnd, SLOT(PaintRemoveAtStack(int,int,int)));
    connect(q, SIGNAL(PaintRemoveLastQueue(int,int)), wnd, SLOT(PaintRemoveLastQueue(int,int)));
    connect(s, SIGNAL(PaintRemoveLastStack(int,int)), wnd, SLOT(PaintRemoveLastStack(int,int)));
    //connect рисования элемента
    connect(q, SIGNAL(PaintQueueElem(int,int,int,bool,bool)), wnd, SLOT(PaintQueueElem(int,int,int,bool,bool)));
    connect(s, SIGNAL(PaintStackElem(int,int,int,bool,bool)), wnd, SLOT(PaintStackElem(int,int,int,bool,bool)));
    //connect сортировки
    connect(q, SIGNAL(Paint_Queue_Swap(int,int,int,int,QString,QString)), wnd, SLOT(Paint_Queue_Swap(int,int,int,int,QString,QString)));
    connect(q, SIGNAL(Paint_Queue_i_j(int,int,QString,QString)), wnd, SLOT(Paint_Queue_I_J(int,int,QString,QString)));
    connect(s, SIGNAL(Paint_Stack_Swap(int,int,int,int,int,QString,QString)), wnd, SLOT(Paint_Stack_Swap(int,int,int,int,int,QString,QString)));
    connect(s, SIGNAL(Paint_Stack_i_j(int,int,int,QString,QString)), wnd, SLOT(Paint_Stack_I_J(int,int,int,QString,QString)));
    //connect вставки на позицию
    connect(q, SIGNAL(PaintInsertAtQueue(int,int,bool,bool)), wnd, SLOT(PaintInsertAtQueue(int,int,bool,bool)));
    connect(s, SIGNAL(PaintInsertAtStack(int,int,bool,bool)), wnd, SLOT(PaintInsertAtStack(int,int,bool,bool)));
    //connect рисования pred и curr
    connect(q, SIGNAL(PaintQueuePredCurr(int,int,int,QString,QString,int,int)), wnd, SLOT(Paint_Queue_pred_curr(int,int,int,QString,QString,int,int)));
    connect(s, SIGNAL(PaintStackPredCurr(int,int,int,QString,QString,int,int)), wnd, SLOT(Paint_Stack_pred_curr(int,int,int,QString,QString,int,int)));
    //connect реверса
    connect(q, SIGNAL(PaintReverseQueue(int,int,int,int)), wnd, SLOT(PaintReverseQueue(int,int,int,int)));
    connect(s, SIGNAL(PaintReverseStack(int,int,int,int)), wnd, SLOT(PaintReverseStack(int,int,int,int)));

    //маски
    QRegExp exp("[0-9,-]{1,3}");
    ui->lineEdit_add->setValidator(new QRegExpValidator(exp,this));
    QRegExp exp1("[0-9]{1,4}");
    ui->lineEdit_remove->setValidator(new QRegExpValidator(exp1, this));

    //выключаем все кнопки, кроме добавления
    Off_Buttons();
    ui->pushButton_add->setEnabled(true);

}

MainWindow::~MainWindow()
{
    delete wnd;
    delete wndtext;
    delete ui;
}

void MainWindow::on_pushButton_reset_clicked()
{
    q->Reset();
    s->Reset();
    qd->Reset();
    sd->Reset();
    qc->Reset();
    wnd->ClearScene();
    wndtext->ClearText();
    //выключаем все кнопки, кроме добавления
    Off_Buttons();
    ui->pushButton_add->setEnabled(true);
}

void MainWindow::Off_Buttons()
{
    ui->pushButton_add->setEnabled(false);
    ui->pushButton_SortBubble->setEnabled(false);
    ui->Remove->setEnabled(false);
    ui->pushButton_Insert->setEnabled(false);
    ui->pushButton_reverse->setEnabled(false);
    ui->pushButton_reset->setEnabled(false);
}

void MainWindow::On_Buttons()
{
    //ui->pushButton_add->setEnabled(true);
    ui->pushButton_SortBubble->setEnabled(true);
    ui->Remove->setEnabled(true);
    ui->pushButton_Insert->setEnabled(true);
    ui->pushButton_reverse->setEnabled(true);
    ui->pushButton_reset->setEnabled(true);
}

void MainWindow::On_Add()
{
    ui->pushButton_add->setEnabled(true);
}

void MainWindow::on_pushButton_add_clicked()
{
    switch (ui->comboBox->currentIndex())
    {
    case 0:
        a = q;
        break;
    case 1:
        a = s;
        break;
    case 2:
        a = qc;
        break;
    case 3:
        a = sd;
        break;
    }
    a->Add(ui->lineEdit_add->text().toInt());
}

void MainWindow::on_Remove_clicked()
{
    switch (ui->comboBox->currentIndex())
    {
    case 0:
        a = q;
        break;
    case 1:
        a = s;
        break;
    }
    //установка label
    connect(a, SIGNAL(setLabel(QString)), wnd, SLOT(setLabel(QString)));
    //выделение в удалении
    connect(a, SIGNAL(markRemove(int)), wndtext, SLOT(removeMark(int)));

    a->Remove(ui->lineEdit_remove->text().toInt());
}

void MainWindow::on_pushButton_SortBubble_clicked()
{
    switch (ui->comboBox->currentIndex())
    {
    case 0:
        a = q;
        break;
    case 1:
        a = s;
        break;
    }
    //выделение в сортировке установкой
    connect(a, SIGNAL(markSortSet(int)), wndtext, SLOT(sortSetMark(int)));
    //выделение в сортировке пузырьком
    connect(a, SIGNAL(markSortBubble(int)), wndtext, SLOT(sortBubbleMark(int)));
    //установка label
    connect(a, SIGNAL(setLabel(QString)), wnd, SLOT(setLabel(QString)));
    //установка label_flag
    connect(a, SIGNAL(setLabelFlag(QString)), wnd, SLOT(setLabelFlag(QString)));

    if (!ui->comboBox_sort->currentIndex())
        a->SortSet();
    else
        a->SortBubble();
}

void MainWindow::on_pushButton_Insert_clicked()
{
    switch (ui->comboBox->currentIndex())
    {
    case 0:
        a = q;
        break;
    case 1:
        a = s;
        break;
    }

    //установка label
    connect(a, SIGNAL(setLabel(QString)), wnd, SLOT(setLabel(QString)));
    //connect выдления в вставке
    connect(a, SIGNAL(markInsert(int)), wndtext, SLOT(insertMark(int)));

    a->Insert();
}

void MainWindow::on_pushButton_reverse_clicked()
{
    switch (ui->comboBox->currentIndex())
    {
    case 0:
        a = q;
        break;
    case 1:
        a = s;
        break;
    }

    //установка label
    connect(a, SIGNAL(setLabel(QString)), wnd, SLOT(setLabel(QString)));
    connect(a, SIGNAL(setLabelFlag(QString)), wnd, SLOT(setLabelFlag(QString)));
    //выделение в реверсе
    connect(a, SIGNAL(markReverse(int)), wndtext, SLOT(reverseMark(int)));

    a->Reverse();
}

void MainWindow::on_action_triggered()
{
    authors *wnd = new authors(this);
    wnd->show();
}
