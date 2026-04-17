#include "resmail.h"
#include "avtorisation.h"
#include "ui_resmail.h"
#include "net.h"
#include <QWidget>
std::string mal;
resmail::resmail(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::resmail)
{
    ui->setupUi(this);
}

resmail::~resmail()
{
    delete ui;
}

void resmail::on_pushButton_2_clicked()
{
    avtorisation *e=new avtorisation;
    e->show();
    close();
}


void resmail::on_lineEdit_textChanged(const QString &arg1)
{
    mal=arg1.toStdString();
}


void resmail::on_pushButton_clicked()
{
    respas(mal);
}

