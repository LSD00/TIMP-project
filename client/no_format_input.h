#ifndef NO_FORMAT_INPUT_H
#define NO_FORMAT_INPUT_H

#include <QDialog>

namespace Ui {
class no_format_input;
}

class no_format_input : public QDialog
{
    Q_OBJECT

public:
    explicit no_format_input(QWidget *parent = nullptr);
    ~no_format_input();

private slots:
    void on_pushButton_clicked();

private:
    Ui::no_format_input *ui;
};

#endif // NO_FORMAT_INPUT_H
