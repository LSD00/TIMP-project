#include "client.h"
#include <QEventLoop>
#include <QTimer>
Client::Client(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::connected, this, &Client::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &Client::onDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(socket, &QTcpSocket::errorOccurred, this, &Client::onError);
}

void Client::connectToServer(const QString &host, quint16 port)
{
    qDebug() << "Connecting to" << host << ":" << port;
    socket->connectToHost(host, port);
}

void Client::sendJson(const QJsonObject &json)
{
    if (socket->state() != QAbstractSocket::ConnectedState) {
        emit error("Not connected to server");
        return;
    }

    QJsonDocument doc(json);
    QByteArray jsonData = doc.toJson(QJsonDocument::Compact);
    jsonData += "\n";
    socket->flush();
}


void Client::onConnected()
{
    emit connected();
}

void Client::onReadyRead()
{
    buffer.append(socket->readAll());
    parseBuffer();
}
void Client::parseBuffer()
{
    int newlinePos;
    while ((newlinePos = buffer.indexOf('\n')) != -1) {
        QByteArray jsonLine = buffer.left(newlinePos);
        buffer.remove(0, newlinePos + 1);

        if (jsonLine.trimmed().isEmpty()) {
            continue;
        }
        QJsonDocument doc = QJsonDocument::fromJson(jsonLine);
        if (!doc.isNull() && doc.isObject()) {
            lastResponse = doc.object();
            emit responseReady();
        } else {
            emit error("Invalid JSON received: " + jsonLine);
        }
    }
}

void Client::onDisconnected()
{
    emit disconnected();
}

void Client::onError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    emit error(socket->errorString());
}