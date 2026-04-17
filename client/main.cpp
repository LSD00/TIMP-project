#include "avtorisation.h"
#include "resmail.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    avtorisation w;
    w.show();
    return QCoreApplication::exec();
}
