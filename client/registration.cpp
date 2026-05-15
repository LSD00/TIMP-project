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
    if (ml.find('e') != std::string::npos and ml.find('t') != std::string::npos and pss.length()>3){
    regist(ml,pss);
    if (true){
        Pdtmail *e=new Pdtmail;
        e->show();
        close();
    } else {
        wrong_registration *e=new wrong_registration;
        e->show();
    }
    } else {
        no_format_input *e=new no_format_input;
        e->show();
    }
}

