#include "graph.h"
#include "task.h"
#include "ui_graph.h"
#include "net.h"
#include <QTableWidgetItem>
int a=1,b=0,c=1;

graph::graph(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::graph)
{
    ui->setupUi(this);
    ui->horizontalSlider->setRange(-10,10);
    ui->horizontalSlider->setValue(a);
    ui->horizontalSlider_2->setRange(-10,10);
    ui->horizontalSlider_2->setValue(b);
    ui->horizontalSlider_3->setRange(-10,10);
    ui->horizontalSlider_3->setValue(c);
    ui->tableWidget->setRowCount(20);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels({"x", "y"});
    ui->tableWidget->verticalHeader()->setVisible(false);
    for (int i=-10;i<10;i++){
        std::string st=std::to_string(i);
        ui->tableWidget->setItem(i+10, 0, new QTableWidgetItem(QString::fromStdString(st)));
    }
    printgraph(crgrap(a,b,c));
    ui->widget->replot();
    this->setStyleSheet("QMainWindow { background-color: #f0f0f0; }");
}

graph::~graph()
{
    delete ui;
}

void graph::on_pushButton_clicked()
{
    Task *e=new Task;
    e->show();
    close();
}

void graph::printgraph(QVector<double> y){
    QVector<double> x;
    for (double i = -10; i < 10; i=i+0.067) {
        x.push_back(i);
    }

    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x.mid(0, 135),y.mid(0, 135));
    ui->widget->graph(1)->setData(x.mid(135, 15),y.mid(135, 15));
    ui->widget->graph(2)->setData(x.mid(150, 15),y.mid(150, 15));
    ui->widget->graph(3)->setData(x.mid(165, 135),y.mid(165, 135));
    ui->widget->graph(0)->setPen(QPen(Qt::red, 2));
    ui->widget->graph(1)->setPen(QPen(Qt::red, 2));
    ui->widget->graph(2)->setPen(QPen(Qt::green, 2));
    ui->widget->graph(3)->setPen(QPen(Qt::blue, 2));

    ui->widget->xAxis->setRange(-10, 10);
    ui->widget->yAxis->setRange(-10, 10);
    ui->widget->replot();
    for (int i=0;i<20;i++){
        std::string st=std::to_string(y[i*15]);
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(st)));
    }
}

void graph::on_horizontalSlider_sliderMoved(int position)
{
    a=position;
    printgraph(crgrap(a,b,c));
}


void graph::on_horizontalSlider_2_sliderMoved(int position)
{
    b=position;
    printgraph(crgrap(a,b,c));
}


void graph::on_horizontalSlider_3_sliderMoved(int position)
{
    c=position;
    printgraph(crgrap(a,b,c));
}

