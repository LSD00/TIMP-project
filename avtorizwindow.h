#ifndef AVTORIZWINDOW_H
#define AVTORIZWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class avtorizwindow;
}
QT_END_NAMESPACE

class avtorizwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit avtorizwindow(QWidget *parent = nullptr);
    ~avtorizwindow() override;

private:
    Ui::avtorizwindow *ui;
};
#endif // AVTORIZWINDOW_H
