#include "sstr.h"
#include "fstr.h"
#include "avtorisation.h"
#include "ui_sstr.h"

sstr::sstr(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::sstr)
{
    ui->setupUi(this);
}

sstr::~sstr()
{
    delete ui;
}

void sstr::on_pushButton_clicked()
{
    fstr *e=new fstr;
    e->show();
    close();
}


void sstr::on_pushButton_2_clicked()
{
    avtorisation *e=new avtorisation;
    e->show();
    close();
}

