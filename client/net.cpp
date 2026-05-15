#include <QDebug>
#include "net.h"
void regist(std::string mail, std::string password){
    malll=mail;
    pas=password;
    QJsonObject json;
    json["action"]="register_request";
    json["email"]=QString::fromStdString(mail);
    client.sendJson(json);
}
void for_codereset(std::string code, std::function<void(bool)> callback) {
    QJsonObject json;
    json["action"] = "reset_verify";
    json["email"] = QString::fromStdString(malll);
    json["code"] = QString::fromStdString(code);
    client.sendJson(json);

    QObject::connect(&client, &Client::responseReady, [callback]() {
        bool success = (client.lastResponse["status"] == "success");
        callback(success);
    });
}
void autor(std::string mail, std::string password, std::function<void(bool)> callback) {
    QJsonObject json;
    json["action"] = "login";
    json["email"] = QString::fromStdString(mail);
    json["password"] = QString::fromStdString(password);
    client.sendJson(json);
    QObject::connect(&client, &Client::responseReady, [callback]() {
        bool success = (client.lastResponse["status"] == "success");
        callback(success);
    });
}
void for_pdtmail(std::string code, std::function<void(bool)> callback) {
    QJsonObject json;
    json["action"] = "register_verify";
    json["email"] = QString::fromStdString(malll);
    json["code"] = QString::fromStdString(code);
    client.sendJson(json);

    QObject::connect(&client, &Client::responseReady, [callback]() {
        bool success = (client.lastResponse["status"] == "success");
        callback(success);
    });
}
void respas(std::string mail, std::function<void(bool)> callback) {
    QJsonObject json;
    json["action"] = "reset_request";
    json["email"] = QString::fromStdString(mail);
    client.sendJson(json);
    QObject::connect(&client, &Client::responseReady, [callback]() {
        bool success = (client.lastResponse["status"] == "success");
        callback(success);
    });
}
void nwpass(std::string password, std::function<void(bool)> callback) {
    QJsonObject json;
    json["action"] = "reset_finalize";
    json["email"] = QString::fromStdString(malll);
    json["password"] = QString::fromStdString(password);
    client.sendJson(json);
    QObject::connect(&client, &Client::responseReady, [callback]() {
        bool success = (client.lastResponse["status"] == "success");
        callback(success);
    });
}
void crgrap(int a, int b, int c, std::function<void(QVector<double>)> callback) {
    QJsonObject json;
    json["action"] = "register_finalize";
    json["email"] = QString::fromStdString(malll);
    json["a"] = a;
    json["b"] = b;
    json["c"] = c;
    client.sendJson(json);

    QObject::connect(&client, &Client::responseReady, [callback]() {
        QVector<double> res;
        if (client.lastResponse["status"] == "success") {
            QJsonArray ar = client.lastResponse["data"].toArray();
            for (int i = 0; i < ar.size(); i++) {
                res.append(ar[i].toDouble());
            }
        }
        callback(res); // Вызываем колбэк с результатом
    });
}
void otprdat(){
    QJsonObject json;
    json["action"]="register_finalize";
    json["email"]=QString::fromStdString(malll);
    json["password"]=QString::fromStdString(pas);
    client.sendJson(json);
}