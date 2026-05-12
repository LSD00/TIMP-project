#include "Server.h"
#include "calc.h"
#include <QJsonDocument>
#include <QJsonArray>

Server::Server(QObject *parent) : QTcpServer(parent) {}

void Server::startServer(quint16 port) {
    if (this->listen(QHostAddress::Any, port)) qInfo() << "Server running on port" << port;
}

void Server::incomingConnection(qintptr socketDescriptor) {
    QTcpSocket* client = new QTcpSocket(this);
    client->setSocketDescriptor(socketDescriptor);
    authenticatedClients.insert(client, false);
    connect(client, &QTcpSocket::readyRead, this, &Server::onReadyRead);
    connect(client, &QTcpSocket::disconnected, this, &Server::onClientDisconnected);
}

void Server::onReadyRead() {
    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender());
    if (!client) return;
    QByteArray rawData = client->readAll();
    
    // Парсинг изолирован от сети. Сделано для удобства тестирования
    QJsonObject requestObj = processPayload(rawData); 
    if (!requestObj.isEmpty()) {
        handleRequest(client, requestObj);
    }
}

QJsonObject Server::processPayload(const QByteArray& data) {
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    
    if (parseError.error != QJsonParseError::NoError || !doc.isObject()) {
        qWarning() << "Invalid JSON payload:" << parseError.errorString();
        return QJsonObject(); 
    }
    return doc.object();
}

void Server::sendAuthResponse(QTcpSocket* client, AuthResult result, const QString& customErrorMsg) {
    if (result == AuthResult::Success) {
        sendResponse(client, {{"status", "success"}});
    } else {
        sendResponse(client, {{"status", "error"}, {"message", customErrorMsg.isEmpty() ? "Auth Error" : customErrorMsg}});
    }
}

void Server::handleRequest(QTcpSocket* client, const QJsonObject& request) {
    QString action = request.value("action").toString();
    QString email = request.value("email").toString();
    QString errorMsg;

    // ==========================================
    // 1. ОТКРЫТЫЕ ЭНДПОИНТЫ (Не требуют логина)
    // ==========================================

    if (action == "login") {
        AuthResult res = AuthManager::getInstance().authenticate(email, request.value("password").toString());
        if (res == AuthResult::Success) {
            authenticatedClients[client] = true;
        }
        sendAuthResponse(client, res);
        return;
    }
    
    // --- Цикл регистрации ---
    if (action == "register_request") {
        sendAuthResponse(client, AuthManager::getInstance().requestRegistrationCode(email, &errorMsg), errorMsg);
        return;
    }
    if (action == "register_verify") {
        sendAuthResponse(client, AuthManager::getInstance().verifyRegistrationCode(email, request.value("code").toString(), &errorMsg), errorMsg);
        return;
    }
    if (action == "register_finalize") {
        sendAuthResponse(client, AuthManager::getInstance().finalizeRegistration(email, request.value("password").toString(), &errorMsg), errorMsg);
        return;
    }

    // --- Цикл сброса пароля ---
    if (action == "reset_request") {
        sendAuthResponse(client, AuthManager::getInstance().requestPasswordReset(email, &errorMsg), errorMsg);
        return;
    }
    if (action == "reset_verify") {
        sendAuthResponse(client, AuthManager::getInstance().verifyResetCode(email, request.value("code").toString(), &errorMsg), errorMsg);
        return;
    }
    if (action == "reset_finalize") {
        sendAuthResponse(client, AuthManager::getInstance().resetPassword(email, request.value("password").toString(), request.value("password_confirm").toString(), &errorMsg), errorMsg);
        return;
    }

    // ==========================================
    // 2. ЗАЩИЩЕННЫЕ ЭНДПОИНТЫ (Требуют логина)
    // ==========================================
    
    // Если клиент дошел до этой строчки и у него нет флага true, отсекаем его.
    if (!authenticatedClients.value(client, false)) {
        sendResponse(client, {{"status", "error"}, {"message", "Unauthorized"}});
        return;
    }

    if (action == "calc") {
        auto res = MainCalcSafe(request.value("a").toInt(), request.value("b").toInt(), request.value("c").toInt());
        QJsonArray arr;
        for (const auto& p : res) {
            arr.append(QJsonObject{{"x", p.x}, {"y", p.y}});
        }
        sendResponse(client, {{"status", "success"}, {"data", arr}});
        return;
    }

    // Если экшен вообще неизвестен
    sendResponse(client, {{"status", "error"}, {"message", "Unknown action"}});
}

void Server::sendResponse(QTcpSocket* client, const QJsonObject& response) {
    client->write(QJsonDocument(response).toJson(QJsonDocument::Compact) + "\n");
}

void Server::onClientDisconnected() {
    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender());
    if (client) { authenticatedClients.remove(client); client->deleteLater(); }
}
