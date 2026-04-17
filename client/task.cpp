#include "task.h"
#include "graph.h"
#include "ui_task.h"

Task::Task(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Task)
{
    ui->setupUi(this);
}

Task::~Task()
{
    delete ui;
}

void Task::on_pushButton_clicked()
{
    graph *e=new graph;
    e->show();
    close();
}

