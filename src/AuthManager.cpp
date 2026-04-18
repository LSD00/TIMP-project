#include "AuthManager.h"
#include <QSettings>
#include <QSqlQuery>
#include <QSqlError>
#include <QRegularExpression>
#include <QRandomGenerator>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QEventLoop>
#include <QDebug>

#include "AuthManager.h"
#include <QSettings>
#include <QSqlQuery>
#include <QSqlError>
#include <QRegularExpression>
#include <QRandomGenerator>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QEventLoop>
#include <QDebug>

AuthManager& AuthManager::getInstance() {
    static AuthManager instance;
    return instance;
}

AuthManager::AuthManager() {
    db = QSqlDatabase::addDatabase("QPSQL", "AuthConnection");
    QSettings settings("config.ini", QSettings::IniFormat);
    db.setHostName(settings.value("Database/host", "localhost").toString());
    db.setDatabaseName(settings.value("Database/name").toString());
    db.setUserName(settings.value("Database/user").toString());
    db.setPassword(settings.value("Database/password").toString());

    if (!db.open()) {
        qCritical() << "DB Open Error:" << db.lastError().text();
    } else {
        initDatabase();
    }

    gcTimer = new QTimer(this);
    connect(gcTimer, &QTimer::timeout, this, &AuthManager::cleanExpiredCodes);
    gcTimer->start(60000);
}

AuthManager::~AuthManager() {
    { QMutexLocker locker(&dbMutex); if (db.isOpen()) db.close(); }
    QSqlDatabase::removeDatabase("AuthConnection");
}

void AuthManager::initDatabase() {
    QMutexLocker locker(&dbMutex);
    QSqlQuery query(db);
    query.exec("CREATE EXTENSION IF NOT EXISTS pgcrypto;");
    query.exec("CREATE TABLE IF NOT EXISTS users (id SERIAL PRIMARY KEY, email TEXT UNIQUE NOT NULL, password_hash CHAR(64), created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP);");
}

void AuthManager::cleanExpiredCodes() {
    QMutexLocker locker(&codesMutex);
    auto now = QDateTime::currentDateTime();

    auto clean = [&](QMap<QString, VerificationContext>& map) {
        for (auto it = map.begin(); it != map.end(); ) {
            if (now > it.value().expiresAt) it = map.erase(it);
            else ++it;
        }
    };

    clean(registrationCodes);
    clean(resetCodes);
}


AuthResult AuthManager::requestRegistrationCode(const QString& email, QString* errorMsg) {
    if (!validateEmail(email)) return AuthResult::InvalidEmail;
    if (userExists(email)) return AuthResult::UserAlreadyExists;

    QString code = QString::number(QRandomGenerator::global()->bounded(100000, 1000000));

    VerificationContext ctx;
    ctx.code = code;
    ctx.expiresAt = QDateTime::currentDateTime().addSecs(CODE_TTL_SECS);

    {
        QMutexLocker locker(&codesMutex);
        registrationCodes.insert(email, ctx);
    }

    if (!sendEmailToUser(email, code)) return AuthResult::ConnectionError;
    return AuthResult::Success;
}

AuthResult AuthManager::verifyRegistrationCode(const QString& email, const QString& code, QString* errorMsg) {
    QMutexLocker locker(&codesMutex);

    if (!registrationCodes.contains(email)) return AuthResult::InvalidCode;

    auto& ctx = registrationCodes[email];

    if (QDateTime::currentDateTime() > ctx.expiresAt) {
        registrationCodes.remove(email);
        return AuthResult::CodeExpired;
    }

    if (ctx.code != code) {
        ctx.attempts++;
        if (ctx.attempts >= MAX_ATTEMPTS) {
            registrationCodes.remove(email);
            return AuthResult::TooManyAttempts;
        }
        return AuthResult::InvalidCode;
    }

    ctx.isVerified = true;

    QMutexLocker dbLocker(&dbMutex);
    QSqlQuery query(db);
    query.prepare("INSERT INTO users (email) VALUES (:email) ON CONFLICT DO NOTHING");
    query.bindValue(":email", email);
    query.exec();

    return AuthResult::Success;
}

bool AuthManager::sendEmailToUser(const QString& email, const QString& code) {
    QSettings settings("config.ini", QSettings::IniFormat);
    QString apiKey = settings.value("Email/api_key").toString();

    if (apiKey.isEmpty()) {
        qCritical() << "API Key is missing in config.ini!";
        return false;
    }

    QNetworkAccessManager manager;
    QNetworkRequest request(QUrl("https://api.brevo.com/v3/smtp/email"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("api-key", apiKey.toUtf8());

    QJsonObject body;
    body["sender"] = QJsonObject{{"name", "AuthSystem"}, {"email", "ovcarenkoaleksandr180@gmail.com"}};
    body["to"] = QJsonArray{QJsonObject{{"email", email}}};
    body["subject"] = "Verification Code";
    body["htmlContent"] = QString("Your code: <b>%1</b>").arg(code);

    QEventLoop loop;
    QNetworkReply* reply = manager.post(request, QJsonDocument(body).toJson());
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    bool ok = (reply->error() == QNetworkReply::NoError);
    qDebug() << "Sending email to:" << email << "code:" << code;

    if (!ok) qWarning() << "Email error:" << reply->errorString();
    qDebug() << "HTTP status:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << "Response:" << reply->readAll();


    reply->deleteLater();
    return ok;
}


AuthResult AuthManager::authenticate(const QString& email, const QString& password) {
    QMutexLocker locker(&dbMutex);
    QSqlQuery query(db);
    query.prepare("SELECT id FROM users WHERE email = :email "
    "AND password_hash IS NOT NULL "
    "AND password_hash = crypt(:pass, password_hash)");
    query.bindValue(":email", email);
    query.bindValue(":pass", password);

    if (!query.exec()) return AuthResult::DatabaseError;
    return query.next() ? AuthResult::Success : AuthResult::InvalidCredentials;
}

bool AuthManager::userExists(const QString& email) {
    QMutexLocker locker(&dbMutex);
    QSqlQuery query(db);
    query.prepare("SELECT 1 FROM users WHERE email = :email LIMIT 1");
    query.bindValue(":email", email);
    return query.exec() && query.next();
}

bool AuthManager::validateEmail(const QString& email) {
    static QRegularExpression re("^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\\.[a-zA-Z0-9-.]+$");
    return re.match(email).hasMatch();
}

bool AuthManager::validatePassword(const QString& password, QString* errorMsg) {
    if (password.length() < 8) {
        if (errorMsg) *errorMsg = "Пароль слишком короткий (минимум 8 символов)";
        return false;
    }
    if (password.length() > 64) {
        if (errorMsg) *errorMsg = "Пароль слишком длинный (максимум 64 символа)";
        return false;
    }
    return true;
}

AuthResult AuthManager::finalizeRegistration(const QString& email, const QString& password, QString* errorMsg) {
    QMutexLocker locker(&codesMutex);
    if (!registrationCodes.contains(email) || !registrationCodes[email].isVerified)
        return AuthResult::CodeNotVerified;

    if (!validatePassword(password)) return AuthResult::WeakPassword;

    QMutexLocker dbLocker(&dbMutex);
    QSqlQuery query(db);
    query.prepare("UPDATE users SET password_hash = crypt(:pass, gen_salt('bf')) WHERE email = :email");
    query.bindValue(":pass", password);
    query.bindValue(":email", email);

    if (!query.exec()) return AuthResult::DatabaseError;

    registrationCodes.remove(email);
    return AuthResult::Success;
}

void AuthManager::cancelRegistration(const QString& email) {
    QMutexLocker locker(&codesMutex);
    registrationCodes.remove(email);

    QMutexLocker dbLocker(&dbMutex);
    QSqlQuery query(db);
    query.prepare("DELETE FROM users WHERE email = :email AND password_hash IS NULL");
    query.bindValue(":email", email);
    query.exec();
}

AuthResult AuthManager::requestPasswordReset(const QString& email, QString* errorMsg) {
    if (!userExists(email)) return AuthResult::UserNotFound;

    QString code = QString::number(QRandomGenerator::global()->bounded(100000, 1000000));

    VerificationContext ctx;
    ctx.code = code;
    ctx.expiresAt = QDateTime::currentDateTime().addSecs(CODE_TTL_SECS);

    {
        QMutexLocker locker(&codesMutex);
        resetCodes.insert(email, ctx);
    }

    if (!sendEmailToUser(email, code)) return AuthResult::ConnectionError;
    return AuthResult::Success;
}

AuthResult AuthManager::verifyResetCode(const QString& email, const QString& code, QString* errorMsg) {
    QMutexLocker locker(&codesMutex);

    if (!resetCodes.contains(email)) return AuthResult::InvalidCode;

    auto& ctx = resetCodes[email];

    if (QDateTime::currentDateTime() > ctx.expiresAt) {
        resetCodes.remove(email);
        return AuthResult::CodeExpired;
    }

    if (ctx.code != code) {
        ctx.attempts++;
        if (ctx.attempts >= MAX_ATTEMPTS) {
            resetCodes.remove(email);
            return AuthResult::TooManyAttempts;
        }
        return AuthResult::InvalidCode;
    }

    ctx.isVerified = true;
    return AuthResult::Success;
}

AuthResult AuthManager::resetPassword(const QString& email, const QString& password, const QString& passwordConfirm, QString* errorMsg) {
    if (password != passwordConfirm) {
        if (errorMsg) *errorMsg = "Пароли не совпадают";
        return AuthResult::WeakPassword;
    }

    if (!validatePassword(password, errorMsg)) return AuthResult::WeakPassword;

    {
        QMutexLocker locker(&codesMutex);
        if (!resetCodes.contains(email) || !resetCodes[email].isVerified)
            return AuthResult::CodeNotVerified;
    }

    QMutexLocker dbLocker(&dbMutex);
    QSqlQuery query(db);
    query.prepare("UPDATE users SET password_hash = crypt(:pass, gen_salt('bf')) WHERE email = :email");
    query.bindValue(":pass", password);
    query.bindValue(":email", email);

    if (!query.exec()) return AuthResult::DatabaseError;

    resetCodes.remove(email);
    return AuthResult::Success;
}



