#ifndef REGISWINDOW_H
#define REGISWINDOW_H

#include <QDialog>

namespace Ui {
class regiswindow;
}

class regiswindow : public QDialog
{
    Q_OBJECT

public:
    explicit regiswindow(QWidget *parent = nullptr);
    ~regiswindow();

private:
    Ui::regiswindow *ui;
};

#endif // REGISWINDOW_H
