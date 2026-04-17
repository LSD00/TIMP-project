#include "graph.h"
#include "task.h"
#include "ui_graph.h"
#include "net.h"
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
    printgraph(crgrap(a,b,c));
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
    ui->widget->graph(0)->setData(x,y);
    ui->widget->xAxis->setRange(-10, 10);
    ui->widget->yAxis->setRange(-10, 10);
    ui->widget->replot();
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

