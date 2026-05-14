#ifndef SSTR_H
#define SSTR_H

#include <QDialog>

namespace Ui {
class sstr;
}

class sstr : public QDialog
{
    Q_OBJECT

public:
    explicit sstr(QWidget *parent = nullptr);
    ~sstr();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::sstr *ui;
};

#endif // SSTR_H
