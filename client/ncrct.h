#ifndef NCRCT_H
#define NCRCT_H

#include <QDialog>

namespace Ui {
class ncrct;
}

class ncrct : public QDialog
{
    Q_OBJECT

public:
    explicit ncrct(QWidget *parent = nullptr);
    ~ncrct();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ncrct *ui;
};

#endif // NCRCT_H
