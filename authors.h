#ifndef AUTHORS_H
#define AUTHORS_H

#include <QDialog>

namespace Ui {
class authors;
}

class authors : public QDialog
{
    Q_OBJECT

public:
    explicit authors(QWidget *parent = 0);
    ~authors();

private:
    Ui::authors *ui;
};

#endif // AUTHORS_H
