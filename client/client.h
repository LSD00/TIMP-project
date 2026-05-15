#ifndef CLIENT_H
#define CLIENT_H


#include <QObject>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    QJsonObject lastResponse;
    void connectToServer(const QString &host, quint16 port);
    void sendJson(const QJsonObject &json);
signals:
    void connected();
    void disconnected();
    void jsonReceived(const QJsonObject &json);
    void error(const QString &message);
    void responseReady();

private slots:
    void onConnected();
    void onReadyRead();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket *socket;
    QByteArray buffer;
    void parseBuffer();
};

#endif // CLIENT_H