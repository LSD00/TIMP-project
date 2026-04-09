#include "avtorizwindow.h"
#include "ui_avtorizwindow.h"

avtorizwindow::avtorizwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::avtorizwindow)
{
    ui->setupUi(this);
}

avtorizwindow::~avtorizwindow()
{
    delete ui;
}
