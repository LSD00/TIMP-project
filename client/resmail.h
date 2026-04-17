#ifndef RESMAIL_H
#define RESMAIL_H

#include <QDialog>

namespace Ui {
class resmail;
}

class resmail : public QDialog
{
    Q_OBJECT

public:
    explicit resmail(QWidget *parent = nullptr);
    ~resmail();

private slots:
    void on_pushButton_2_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::resmail *ui;
};

#endif // RESMAIL_H
