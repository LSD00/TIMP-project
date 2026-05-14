#include "registration.h"
#include "avtorisation.h"
#include "net.h"
#include "pdtmail.h"
#include "ui_registration.h"
std::string ml, name, pss;
registration::registration(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::registration)
{
    ui->setupUi(this);
}

registration::~registration()
{
    delete ui;
}



void registration::on_pushButton_2_clicked()
{
    avtorisation *e=new avtorisation;
    e->show();
    close();
}


void registration::on_lineEdit_textChanged(const QString &arg1)
{
    name=arg1.toStdString();
}


void registration::on_lineEdit_2_textChanged(const QString &arg1)
{
    ml=arg1.toStdString();
}


void registration::on_lineEdit_3_textChanged(const QString &arg1)
{
    pss=arg1.toStdString();
}


void registration::on_pushButton_clicked()
{
    regist(name,ml,pss);
    if (code_for_pass!=0){
        Pdtmail *e=new Pdtmail;
        e->show();
        close();
    }
}

