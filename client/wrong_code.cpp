#include "wrong_code.h"
#include "ui_wrong_code.h"

wrong_code::wrong_code(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::wrong_code)
{
    ui->setupUi(this);
}

wrong_code::~wrong_code()
{
    delete ui;
}

void wrong_code::on_pushButton_clicked()
{
    close();
}

