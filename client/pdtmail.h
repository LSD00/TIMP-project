#ifndef PDTMAIL_H
#define PDTMAIL_H

#include <QDialog>

namespace Ui {
class Pdtmail;
}

class Pdtmail : public QDialog
{
    Q_OBJECT

public:
    explicit Pdtmail(QWidget *parent = nullptr);
    ~Pdtmail();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::Pdtmail *ui;
};

#endif // PDTMAIL_H
