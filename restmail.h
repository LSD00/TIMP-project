#ifndef RESTMAIL_H
#define RESTMAIL_H

#include <QDialog>

namespace Ui {
class restmail;
}

class restmail : public QDialog
{
    Q_OBJECT

public:
    explicit restmail(QWidget *parent = nullptr);
    ~restmail();

private:
    Ui::restmail *ui;
};

#endif // RESTMAIL_H
