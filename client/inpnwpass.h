#ifndef INPNWPASS_H
#define INPNWPASS_H

#include <QDialog>

namespace Ui {
class inpnwpass;
}

class inpnwpass : public QDialog
{
    Q_OBJECT

public:
    explicit inpnwpass(QWidget *parent = nullptr);
    ~inpnwpass();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::inpnwpass *ui;
};

#endif // INPNWPASS_H
