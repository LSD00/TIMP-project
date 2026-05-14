#ifndef CODERESET_H
#define CODERESET_H

#include <QDialog>

namespace Ui {
class codereset;
}

class codereset : public QDialog
{
    Q_OBJECT

public:
    explicit codereset(QWidget *parent = nullptr);
    ~codereset();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::codereset *ui;
};

#endif // CODERESET_H
