#include "codereset.h"
#include "ui_codereset.h"
#include "net.h"
#include "inpnwpass.h"
std::string code="";
codereset::codereset(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::codereset)
{
    ui->setupUi(this);
}

codereset::~codereset()
{
    delete ui;
}

void codereset::on_pushButton_clicked()
{
    for_codereset(code, [this](bool success) {
    if (success){
    inpnwpass *e=new inpnwpass;
    e->show();
    close();
    } else{
        wrong_code *e=new wrong_code;
        e->show();
    }
    });
}


void codereset::on_lineEdit_textChanged(const QString &arg1)
{
    code=arg1.toStdString();
}

