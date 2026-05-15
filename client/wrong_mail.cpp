#include "wrong_mail.h"
#include "ui_wrong_mail.h"

wrong_mail::wrong_mail(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::wrong_mail)
{
    ui->setupUi(this);
}

wrong_mail::~wrong_mail()
{
    delete ui;
}

void wrong_mail::on_pushButton_clicked()
{
    close();
}

