#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QMutex>
#include <QMap>
#include <QDateTime>
#include <QTimer>
#include <QObject>

enum class AuthResult {
    Success, ConnectionError, InvalidEmail, WeakPassword,
    UserAlreadyExists, UserNotFound, DatabaseError,
    InvalidCredentials, CodeExpired, InvalidCode,
    TooManyAttempts, CodeNotVerified
};

struct VerificationContext {
    QString code;
    QDateTime expiresAt;
    int attempts = 0;
    bool isVerified = false;
};

class AuthManager : public QObject {
    Q_OBJECT
public:
    static AuthManager& getInstance();
    
    AuthManager(const AuthManager&) = delete;
    AuthManager& operator=(const AuthManager&) = delete;

    AuthResult requestRegistrationCode(const QString& email, QString* errorMsg = nullptr);
    AuthResult verifyRegistrationCode(const QString& email, const QString& code, QString* errorMsg = nullptr);
    AuthResult finalizeRegistration(const QString& email, const QString& password, QString* errorMsg = nullptr);
    
    AuthResult authenticate(const QString& email, const QString& password);
    
    AuthResult requestPasswordReset(const QString& email, QString* errorMsg = nullptr);
    AuthResult verifyResetCode(const QString& email, const QString& code, QString* errorMsg = nullptr);
    AuthResult resetPassword(const QString& email, const QString& password, const QString& passwordConfirm, QString* errorMsg = nullptr);

    // ВОССТАНОВЛЕННЫЕ МЕТОДЫ:
    void cancelRegistration(const QString& email);
    QString getLastError() const;

    bool userExists(const QString& email);
    bool validateEmail(const QString& email);
    bool validatePassword(const QString& password, QString* errorMsg = nullptr);

private slots:
    void cleanExpiredCodes();

private:
    AuthManager();
    ~AuthManager();
    void initDatabase();
    bool sendEmailToUser(const QString& email, const QString& code);

    QSqlDatabase db;
    mutable QMutex dbMutex;
    mutable QMutex codesMutex;
    
    QString lastError;
    QTimer* gcTimer;
    
    QMap<QString, VerificationContext> registrationCodes;
    QMap<QString, VerificationContext> resetCodes;

    const int MAX_ATTEMPTS = 3;
    const int CODE_TTL_SECS = 90;
};

#endif // AUTHMANAGER_H
