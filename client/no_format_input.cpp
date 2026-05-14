#include "no_format_input.h"
#include "ui_no_format_input.h"

no_format_input::no_format_input(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::no_format_input)
{
    ui->setupUi(this);
}

no_format_input::~no_format_input()
{
    delete ui;
}

void no_format_input::on_pushButton_clicked()
{
    close();
}

