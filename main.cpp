#include "avtorizwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    avtorizwindow w;
    w.show();
    return QCoreApplication::exec();
}
