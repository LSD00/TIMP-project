#ifndef WRONG_REGISTRATION_H
#define WRONG_REGISTRATION_H

#include <QDialog>

namespace Ui {
class wrong_registration;
}

class wrong_registration : public QDialog
{
    Q_OBJECT

public:
    explicit wrong_registration(QWidget *parent = nullptr);
    ~wrong_registration();

private:
    Ui::wrong_registration *ui;
};

#endif // WRONG_REGISTRATION_H
