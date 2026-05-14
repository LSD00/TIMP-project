#include "ncrct.h"
#include "ui_ncrct.h"

ncrct::ncrct(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ncrct)
{
    ui->setupUi(this);
}

ncrct::~ncrct()
{
    delete ui;
}

void ncrct::on_pushButton_clicked()
{
    close();
}

