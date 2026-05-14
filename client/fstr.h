#ifndef FSTR_H
#define FSTR_H

#include <QDialog>

namespace Ui {
class fstr;
}

class fstr : public QDialog
{
    Q_OBJECT

public:
    explicit fstr(QWidget *parent = nullptr);
    ~fstr();

private slots:
    void on_pushButton_clicked();

private:
    Ui::fstr *ui;
};

#endif // FSTR_H
