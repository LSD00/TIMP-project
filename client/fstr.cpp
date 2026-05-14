#include "fstr.h"
#include "sstr.h"
#include "ui_fstr.h"

fstr::fstr(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fstr)
{
    ui->setupUi(this);
}

fstr::~fstr()
{
    delete ui;
}

void fstr::on_pushButton_clicked()
{
    sstr *e=new sstr;
    e->show();
    close();
}

