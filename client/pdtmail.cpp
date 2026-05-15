#include "pdtmail.h"
#include "ui_pdtmail.h"
#include "net.h"
#include "string"
#include "task.h"
#include <client.h>
std::string mal;

Pdtmail::Pdtmail(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Pdtmail)
{
    ui->setupUi(this);
}

Pdtmail::~Pdtmail()
{
    delete ui;
}

void Pdtmail::on_lineEdit_textChanged(const QString &arg1)
{
    mal=arg1.toStdString();
}


void Pdtmail::on_pushButton_clicked()
{
   for_pdtmail("123456", [this](bool success) {
    if (success){
        otprdat();
        Task *e=new Task;
        e->show();
        close();
    }
    });
}


