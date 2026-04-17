#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>

namespace Ui {
class graph;
}

class graph : public QDialog
{
    Q_OBJECT

public:
    explicit graph(QWidget *parent = nullptr);
    ~graph();

private slots:
    void printgraph(QVector<double> y);

    void on_pushButton_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_horizontalSlider_2_sliderMoved(int position);

    void on_horizontalSlider_3_sliderMoved(int position);

private:
    Ui::graph *ui;
};

#endif // GRAPH_H
