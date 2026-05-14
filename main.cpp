#include <QCoreApplication>
#include <QDebug>
#include <QSocketNotifier>
#include <QTextStream>
#include <unistd.h>
#include "AuthManager.h"

QString resultToString(AuthResult r) {
    switch (r) {
        case AuthResult::Success: return "Success";
        case AuthResult::ConnectionError: return "ConnectionError";
        case AuthResult::InvalidEmail: return "InvalidEmail";
        case AuthResult::WeakPassword: return "WeakPassword";
        case AuthResult::UserAlreadyExists: return "UserAlreadyExists";
        case AuthResult::UserNotFound: return "UserNotFound";
        case AuthResult::DatabaseError: return "DatabaseError";
        case AuthResult::InvalidCredentials: return "InvalidCredentials";
        case AuthResult::CodeExpired: return "CodeExpired";
        case AuthResult::InvalidCode: return "InvalidCode";
        case AuthResult::TooManyAttempts: return "TooManyAttempts";
        case AuthResult::CodeNotVerified: return "CodeNotVerified";
    }
    return "Unknown";
}

class AsyncAuthTester : public QObject {
    Q_OBJECT
public:
    AsyncAuthTester(QObject* parent = nullptr) : QObject(parent), currentState(State::WaitingForRegCode) {
        auth = &AuthManager::getInstance();
        email = "dropovodovod@gmail.com";
        password = "StrongPass1234";

        notifier = new QSocketNotifier(STDIN_FILENO, QSocketNotifier::Read, this);
        connect(notifier, &QSocketNotifier::activated, this, &AsyncAuthTester::processInput);
    }

    void startTest() {
        qDebug() << "=== REQUEST REGISTRATION CODE ===";
        qDebug() << resultToString(auth->requestRegistrationCode(email));
        qDebug() << ">> Запрос улетел в фоне. Ожидаем ответ от Brevo...";
        qDebug() << ">> Введи код из письма:";
    }

private slots:
    void processInput() {
        QTextStream stream(stdin);
        QString code = stream.readLine().trimmed();
        if (code.isEmpty()) return;

        if (currentState == State::WaitingForRegCode) {
            qDebug() << "\n=== VERIFY CODE ===";
            qDebug() << resultToString(auth->verifyRegistrationCode(email, code));

            qDebug() << "=== FINALIZE REGISTRATION ===";
            qDebug() << resultToString(auth->finalizeRegistration(email, password));

            qDebug() << "=== AUTHENTICATE ===";
            qDebug() << resultToString(auth->authenticate(email, password));

            qDebug() << "\n=== REQUEST PASSWORD RESET ===";
            qDebug() << resultToString(auth->requestPasswordReset(email));
            qDebug() << ">> Письмо для сброса отправлено. Введи новый код:";

            currentState = State::WaitingForResetCode;

        } else if (currentState == State::WaitingForResetCode) {
            qDebug() << "\n=== VERIFY RESET CODE ===";
            qDebug() << resultToString(auth->verifyResetCode(email, code));

            qDebug() << "=== RESET PASSWORD ===";
            qDebug() << resultToString(auth->resetPassword(email, "NewPass123", "NewPass123"));

            qDebug() << "=== AUTHENTICATE WITH NEW PASSWORD ===";
            qDebug() << resultToString(auth->authenticate(email, "NewPass123"));

            qDebug() << "\nТест завершен.";
            qApp->quit();
        }
    }

private:
    enum class State { WaitingForRegCode, WaitingForResetCode };
    State currentState;
    AuthManager* auth;
    QString email;
    QString password;
    QSocketNotifier* notifier;
};

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    AsyncAuthTester tester;
    tester.startTest();

    return app.exec();
}

#include "main.moc"
