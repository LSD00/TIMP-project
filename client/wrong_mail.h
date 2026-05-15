#ifndef WRONG_MAIL_H
#define WRONG_MAIL_H

#include <QDialog>

namespace Ui {
class wrong_mail;
}

class wrong_mail : public QDialog
{
    Q_OBJECT

public:
    explicit wrong_mail(QWidget *parent = nullptr);
    ~wrong_mail();

private slots:
    void on_pushButton_clicked();

private:
    Ui::wrong_mail *ui;
};

#endif // WRONG_MAIL_H
