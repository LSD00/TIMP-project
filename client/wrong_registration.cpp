#include "wrong_registration.h"
#include "ui_wrong_registration.h"

wrong_registration::wrong_registration(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::wrong_registration)
{
    ui->setupUi(this);
}

wrong_registration::~wrong_registration()
{
    delete ui;
}
