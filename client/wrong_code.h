#ifndef WRONG_CODE_H
#define WRONG_CODE_H

#include <QDialog>

namespace Ui {
class wrong_code;
}

class wrong_code : public QDialog
{
    Q_OBJECT

public:
    explicit wrong_code(QWidget *parent = nullptr);
    ~wrong_code();

private slots:
    void on_pushButton_clicked();

private:
    Ui::wrong_code *ui;
};

#endif // WRONG_CODE_H
