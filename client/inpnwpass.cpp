#include "inpnwpass.h"
#include "ui_inpnwpass.h"
#include "net.h"
#include "avtorisation.h"
#include "string"
std::string strnwpass;
inpnwpass::inpnwpass(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::inpnwpass)
{
    ui->setupUi(this);
}

inpnwpass::~inpnwpass()
{
    delete ui;
}

void inpnwpass::on_pushButton_clicked()
{
    nwpass(strnwpass, [this](bool success) {
    if (success){
    avtorisation *e=new avtorisation;
    e->show();
    close();
    } else {
        no_format_input *e=new no_format_input;
        e->show();
    }
    });
}


void inpnwpass::on_lineEdit_textChanged(const QString &arg1)
{
    strnwpass=arg1.toStdString();
}

