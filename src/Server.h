#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QJsonObject>
#include "AuthManager.h"

class Server : public QTcpServer {
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    void startServer(quint16 port);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void onReadyRead();
    void onClientDisconnected();

private:
    void handleRequest(QTcpSocket* client, const QJsonObject& request);
    void sendResponse(QTcpSocket* client, const QJsonObject& response);
    void sendAuthResponse(QTcpSocket* client, AuthResult result, const QString& customErrorMsg = QString());

    QMap<QTcpSocket*, bool> authenticatedClients;
};

#endif