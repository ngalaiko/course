#include "displaytext.h"
#include "ui_displaytext.h"

#include <QFile>

DisplayText::DisplayText(QWidget *parent) :
    QDialog(parent, Qt::WindowTitleHint),
    ui(new Ui::DisplayText)
{
    ui->setupUi(this);
}

DisplayText::~DisplayText()
{
    delete ui;
}

void DisplayText::ClearText()
{
    ui->textEdit->clear();
}

void DisplayText::queueCycleAddMark(int n)
{
    QFile file(":/code/queueCycleAdd.txt");
    ui->textEdit->clear();
    if(file.open(QIODevice::ReadOnly |QIODevice::Text))
        {
            for(int i = 1; !file.atEnd(); i++)
            {
                if (i == n)
                    ui->textEdit->append("<font color=red>" + file.readLine().simplified() + "</font>");
                else
                    ui->textEdit->append(file.readLine());
            }

        }
}

void DisplayText::queueAddMark(int n)
{
    QFile file(":/code/queueAdd.txt");
    ui->textEdit->clear();
    if(file.open(QIODevice::ReadOnly |QIODevice::Text))
        {
            for(int i = 1; !file.atEnd(); i++)
            {
                if (i == n)
                    ui->textEdit->append("<font color=red>" + file.readLine() + "</font>");
                else
                    ui->textEdit->append(file.readLine());
            }

        }
}

void DisplayText::removeMark(int n)
{
    QFile file(":/code/remove.txt");
    ui->textEdit->clear();
    if(file.open(QIODevice::ReadOnly |QIODevice::Text))
        {
            for(int i = 1; !file.atEnd(); i++)
            {
                if (i == n)
                    ui->textEdit->append("<font color=red>" + file.readLine() + "</font>");
                else
                    ui->textEdit->append(file.readLine());
            }

        }
}

void DisplayText::stackAddMark(int n)
{
    QFile file(":/code/stackAdd.txt");
    ui->textEdit->clear();
    if(file.open(QIODevice::ReadOnly |QIODevice::Text))
        {
            for(int i = 1; !file.atEnd(); i++)
            {
                if (i == n)
                    ui->textEdit->append("<font color=red>" + file.readLine() + "</font>");
                else
                    ui->textEdit->append(file.readLine());
            }

        }
}

void DisplayText::stackDoubleAddMark(int n)
{
    QFile file(":/code/stackDoubleAdd.txt");
    ui->textEdit->clear();
    if(file.open(QIODevice::ReadOnly |QIODevice::Text))
        {
            for(int i = 1; !file.atEnd(); i++)
            {
                if (i == n)
                    ui->textEdit->append("<font color=red>" + file.readLine() + "</font>");
                else
                    ui->textEdit->append(file.readLine());
            }

        }
}


void DisplayText::sortSetMark(int n)
{
    QFile file(":/code/sortSet.txt");
    ui->textEdit->clear();
    if(file.open(QIODevice::ReadOnly |QIODevice::Text))
        {
            for(int i = 1; !file.atEnd(); i++)
            {
                if (i == n)
                    ui->textEdit->append("<font color=red>" + file.readLine() + "</font>");
                else
                    ui->textEdit->append(file.readLine());
            }

        }
}

void DisplayText::sortBubbleMark(int n)
{
    QFile file(":/code/sortBubble.txt");
    ui->textEdit->clear();
    if(file.open(QIODevice::ReadOnly |QIODevice::Text))
        {
            for(int i = 1; !file.atEnd(); i++)
            {
                if (i == n)
                    ui->textEdit->append("<font color=red>" + file.readLine() + "</font>");
                else
                    ui->textEdit->append(file.readLine());
            }

        }
}

void DisplayText::insertMark(int n)
{
    QFile file(":/code/insert.txt");
    ui->textEdit->clear();
    if(file.open(QIODevice::ReadOnly |QIODevice::Text))
        {
            for(int i = 1; !file.atEnd(); i++)
            {
                if (i == n)
                    ui->textEdit->append("<font color=red>" + file.readLine() + "</font>");
                else
                    ui->textEdit->append(file.readLine());
            }

        }
}

void DisplayText::reverseMark(int n)
{
    QFile file(":/code/reverse.txt");
    ui->textEdit->clear();
    if(file.open(QIODevice::ReadOnly |QIODevice::Text))
        {
            for(int i = 1; !file.atEnd(); i++)
            {
                if (i == n)
                    ui->textEdit->append("<font color=red>" + file.readLine() + "</font>");
                else
                    ui->textEdit->append(file.readLine());
            }

        }
}
