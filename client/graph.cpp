#include "graph.h"
#include "task.h"
#include "ui_graph.h"
#include "net.h"
#include <QTableWidgetItem>
#include <cmath>
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
    crgrap(a, b, c, [this](QVector<double> result) {
        printgraph(result);
    });
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

void graph::printgraph(QVector<double> p){
    QVector<double> x;
    QVector<double> y;
    for (int i = 0; i < p.size(); i=i+2) {
        x.push_back(p[i]);
    }
    for (int i = 1; i < p.size(); i=i+2) {
        y.push_back(p[i]);
    }
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x.mid(0, static_cast<int>(std::round(x.size()*9/20))),y.mid(0, static_cast<int>(std::round(x.size()*9/20))));
    ui->widget->graph(1)->setData(x.mid(static_cast<int>(std::round(x.size()*9/20)), static_cast<int>(std::round(x.size()/20))),y.mid(static_cast<int>(std::round(x.size()*9/20)), static_cast<int>(std::round(x.size()/20))));
    ui->widget->graph(1)->setData(x.mid(static_cast<int>(std::round(x.size()/2)), static_cast<int>(std::round(x.size()/20))),y.mid(static_cast<int>(std::round(x.size()/2)), static_cast<int>(std::round(x.size()/20))));
    ui->widget->graph(3)->setData(x.mid(static_cast<int>(std::round(x.size()*11/20)), static_cast<int>(std::round(x.size()*9/20))),y.mid(static_cast<int>(std::round(x.size()*11/20)), static_cast<int>(std::round(x.size()*9/20))));
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
    crgrap(a, b, c, [this](QVector<double> result) {
        printgraph(result);
    });
}


void graph::on_horizontalSlider_2_sliderMoved(int position)
{
    b=position;
    crgrap(a, b, c, [this](QVector<double> result) {
        printgraph(result);
    });
}


void graph::on_horizontalSlider_3_sliderMoved(int position)
{
    c=position;
    crgrap(a, b, c, [this](QVector<double> result) {
        printgraph(result);
    });
}

