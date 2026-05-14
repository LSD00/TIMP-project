#include "fstr.h"
#include "resmail.h"
#include "net.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    fstr w;
    w.show();
    return QCoreApplication::exec();
}
