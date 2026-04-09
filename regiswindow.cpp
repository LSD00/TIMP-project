#include "regiswindow.h"
#include "ui_regiswindow.h"

regiswindow::regiswindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::regiswindow)
{
    ui->setupUi(this);
}

regiswindow::~regiswindow()
{
    delete ui;
}
