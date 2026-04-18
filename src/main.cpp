#include <QCoreApplication>
#include "Server.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    Server server;
    server.startServer(8080);
    return a.exec();
}