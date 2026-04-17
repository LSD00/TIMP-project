#ifndef AVTORISATION_H
#define AVTORISATION_H

#include <QMainWindow>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui {
class avtorisation;
}
QT_END_NAMESPACE

class avtorisation : public QMainWindow
{
    Q_OBJECT

public:
    explicit avtorisation(QWidget *parent = nullptr);
    ~avtorisation() override;

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

private:
    Ui::avtorisation *ui;
};
#endif // AVTORISATION_H
