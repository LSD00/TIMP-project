#include "fstr.h"
#include "resmail.h"
#include "net.h"
#include <QApplication>
#include <client.h>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    client.connectToServer("127.0.0.1", 8080);
    fstr w;
    w.show();
    return QCoreApplication::exec();
}
