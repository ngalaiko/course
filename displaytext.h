#ifndef DISPLAYTEXT_H
#define DISPLAYTEXT_H

#include <QDialog>
#include <fstream>
#include <QFile>

namespace Ui {
class DisplayText;
}

class DisplayText : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayText(QWidget *parent = 0);
    ~DisplayText();

    void ClearText();

private:
    Ui::DisplayText *ui;

public slots:
    void queueAddMark(int n);
    void stackAddMark(int n);
    void removeMark(int n);
    void sortSetMark(int n);
    void sortBubbleMark(int n);
    void insertMark(int n);
    void reverseMark(int n);
    void stackDoubleAddMark(int n);
    void queueCycleAddMark(int n);
};

#endif // DISPLAYTEXT_H
