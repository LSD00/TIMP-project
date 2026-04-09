#include "restmail.h"
#include "ui_restmail.h"

restmail::restmail(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::restmail)
{
    ui->setupUi(this);
}

restmail::~restmail()
{
    delete ui;
}
