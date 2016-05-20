#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "queue.h"
#include "stack.h"
#include "queuedouble.h"
#include "stackdouble.h"
#include "queueCycle.h"
#include "display.h"
#include "displaytext.h"
#include "authors.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_add_clicked();

    void on_Remove_clicked();

    void on_pushButton_SortBubble_clicked();

    void Off_Buttons();

    void On_Buttons();

    void On_Add();

    void on_pushButton_Insert_clicked();

    void on_pushButton_reverse_clicked();

    void on_pushButton_reset_clicked();

    void on_action_triggered();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    Queue *q;
    Stack *s;
    QueueDouble *qd;
    StackDouble *sd;
    QueueCycle *qc;
    CommonAll *a;
    Display *wnd;
    DisplayText *wndtext;

    void set_one(bool state);
};

#endif // MAINWINDOW_H
