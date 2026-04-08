#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSettings>
#include <QMutex>

enum class AuthResult {
    Success,
    UserAlreadyExists,
    InvalidCredentials,
    WeakPassword,
    InvalidUsername,
    DatabaseError,
    ConnectionError
};

class AuthManager {
public:
    static AuthManager& getInstance();

    AuthManager(const AuthManager&) = delete;
    AuthManager& operator=(const AuthManager&) = delete;

    AuthResult registerUser(const QString& username, const QString& password, QString* errorMsg = nullptr);
    AuthResult authenticate(const QString& username, const QString& password);
    
    bool isConnected() const;
    QString getLastError() const;

private:
    AuthManager();
    ~AuthManager();

    void initDatabase();
    bool loadDatabaseConfig();
    bool validateUsername(const QString& username, QString* errorMsg = nullptr);
    bool validatePassword(const QString& password, QString* errorMsg = nullptr);
    bool userExists(const QString& username);
    
    QSqlDatabase db;
    QString lastError;
    QMutex dbMutex;  // Для потокобезопасности
    
    // Константы валидации
    static constexpr int MIN_USERNAME_LENGTH = 3;
    static constexpr int MAX_USERNAME_LENGTH = 50;
    static constexpr int MIN_PASSWORD_LENGTH = 8;
    static constexpr int MAX_PASSWORD_LENGTH = 128;
};

#endif // AUTHMANAGER_H
