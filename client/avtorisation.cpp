#include "avtorisation.h"
#include "registration.h"
#include "resmail.h"
#include "task.h"
#include "ui_avtorisation.h"
#include "net.h"

std::string mail, pass;

avtorisation::avtorisation(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::avtorisation)
{
    ui->setupUi(this);
}

avtorisation::~avtorisation()
{
    delete ui;
}

void avtorisation::on_pushButton_3_clicked()
{
    resmail *e=new resmail;
    e->show();
    close();
}


void avtorisation::on_pushButton_2_clicked()
{
    registration *e=new registration;
    e->show();
    close();
}


void avtorisation::on_pushButton_clicked()
{
    if (mail.find('@') != std::string::npos and mail.find('.') != std::string::npos and pass!=""){
    autor(mail, pass, [this](bool success) {
    if (success){
        Task *e=new Task;
        e->show();
        this->close();
    } else {
        ncrct *e=new ncrct;
        e->show();
    }
    });
    } else {
        no_format_input *e=new no_format_input;
        e->show();
    }

}





void avtorisation::on_lineEdit_textChanged(const QString &arg1)
{
    mail=arg1.toStdString();
}


void avtorisation::on_lineEdit_2_textChanged(const QString &arg1)
{
    pass=arg1.toStdString();
}

