#include "AuthManager.h"
#include <QRegularExpression>
#include <QMutexLocker>

AuthManager& AuthManager::getInstance() {
    static AuthManager instance;
    return instance;
}

AuthManager::AuthManager() {
    if (!loadDatabaseConfig()) {
        lastError = "Не удалось загрузить конфигурацию БД";
        return;
    }

    // Используем именованное соединение для потокобезопасности
    db = QSqlDatabase::addDatabase("QPSQL", "AuthConnection");
    
    if (!db.open()) {
        lastError = QString("Ошибка подключения к БД: %1").arg(db.lastError().text());
        qCritical() << lastError;
    } else {
        initDatabase();
    }
}

AuthManager::~AuthManager() {
    if (db.isOpen()) {
        db.close();
    }
    QSqlDatabase::removeDatabase("AuthConnection");
}

bool AuthManager::loadDatabaseConfig() {
    // Приоритет: переменные окружения -> config файл -> дефолтные значения
    QString host = qEnvironmentVariable("DB_HOST", "localhost");
    QString dbName = qEnvironmentVariable("DB_NAME", "users_db");
    QString user = qEnvironmentVariable("DB_USER", "postgres");
    QString password = qEnvironmentVariable("DB_PASSWORD");
    
    // Если пароль не в env, пробуем конфиг файл
    if (password.isEmpty()) {
        QSettings settings("config.ini", QSettings::IniFormat);
        host = settings.value("Database/host", host).toString();
        dbName = settings.value("Database/name", dbName).toString();
        user = settings.value("Database/user", user).toString();
        password = settings.value("Database/password").toString();
    }
    
    if (password.isEmpty()) {
        qWarning() << "ВНИМАНИЕ: Пароль БД не настроен! Используйте переменные окружения или config.ini";
        return false;
    }
    
    db.setHostName(host);
    db.setDatabaseName(dbName);
    db.setUserName(user);
    db.setPassword(password);
    
    return true;
}

void AuthManager::initDatabase() {
    QMutexLocker locker(&dbMutex);
    QSqlQuery query(db);

    // Включаем расширение pgcrypto
    if (!query.exec("CREATE EXTENSION IF NOT EXISTS pgcrypto;")) {
        lastError = QString("Ошибка создания расширения: %1").arg(query.lastError().text());
        qCritical() << lastError;
        return;
    }

    QString createTable = 
        "CREATE TABLE IF NOT EXISTS users ("
        "id SERIAL PRIMARY KEY, "
        "username TEXT UNIQUE NOT NULL, "
        "password_hash CHAR(60) NOT NULL, "
        "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP);";
    
    if (!query.exec(createTable)) {
        lastError = QString("Ошибка инициализации таблицы: %1").arg(query.lastError().text());
        qCritical() << lastError;
    }
}

bool AuthManager::validateUsername(const QString& username, QString* errorMsg) {
    if (username.isEmpty()) {
        if (errorMsg) *errorMsg = "Имя пользователя не может быть пустым";
        return false;
    }
    
    if (username.length() < MIN_USERNAME_LENGTH) {
        if (errorMsg) *errorMsg = QString("Имя пользователя должно содержать минимум %1 символа").arg(MIN_USERNAME_LENGTH);
        return false;
    }
    
    if (username.length() > MAX_USERNAME_LENGTH) {
        if (errorMsg) *errorMsg = QString("Имя пользователя не может быть длиннее %1 символов").arg(MAX_USERNAME_LENGTH);
        return false;
    }
    
    // Проверка на допустимые символы (буквы, цифры, подчеркивание, дефис)
    QRegularExpression regex("^[a-zA-Z0-9_-]+$");
    if (!regex.match(username).hasMatch()) {
        if (errorMsg) *errorMsg = "Имя пользователя может содержать только буквы, цифры, подчеркивание и дефис";
        return false;
    }
    
    return true;
}

bool AuthManager::validatePassword(const QString& password, QString* errorMsg) {
    if (password.isEmpty()) {
        if (errorMsg) *errorMsg = "Пароль не может быть пустым";
        return false;
    }
    
    if (password.length() < MIN_PASSWORD_LENGTH) {
        if (errorMsg) *errorMsg = QString("Пароль должен содержать минимум %1 символов").arg(MIN_PASSWORD_LENGTH);
        return false;
    }
    
    if (password.length() > MAX_PASSWORD_LENGTH) {
        if (errorMsg) *errorMsg = QString("Пароль слишком длинный (максимум %1 символов)").arg(MAX_PASSWORD_LENGTH);
        return false;
    }
    
    // Проверка на наличие хотя бы одной цифры и одной буквы
    bool hasDigit = false;
    bool hasLetter = false;
    
    for (const QChar& ch : password) {
        if (ch.isDigit()) hasDigit = true;
        if (ch.isLetter()) hasLetter = true;
        if (hasDigit && hasLetter) break;
    }
    
    if (!hasDigit || !hasLetter) {
        if (errorMsg) *errorMsg = "Пароль должен содержать хотя бы одну букву и одну цифру";
        return false;
    }
    
    return true;
}

bool AuthManager::userExists(const QString& username) {
    QMutexLocker locker(&dbMutex);
    QSqlQuery query(db);
    
    query.prepare("SELECT id FROM users WHERE username = :user LIMIT 1");
    query.bindValue(":user", username);
    
    if (!query.exec()) {
        lastError = QString("Ошибка проверки существования пользователя: %1").arg(query.lastError().text());
        return false;
    }
    
    return query.next();
}

AuthResult AuthManager::registerUser(const QString& username, const QString& password, QString* errorMsg) {
    if (!isConnected()) {
        if (errorMsg) *errorMsg = "Нет соединения с базой данных";
        return AuthResult::ConnectionError;
    }
    
    // Валидация username
    if (!validateUsername(username, errorMsg)) {
        return AuthResult::InvalidUsername;
    }
    
    // Валидация password
    if (!validatePassword(password, errorMsg)) {
        return AuthResult::WeakPassword;
    }
    
    // Проверка на существование пользователя
    if (userExists(username)) {
        if (errorMsg) *errorMsg = "Пользователь с таким именем уже существует";
        return AuthResult::UserAlreadyExists;
    }
    
    // Регистрация
    QMutexLocker locker(&dbMutex);
    QSqlQuery query(db);
    
    query.prepare("INSERT INTO users (username, password_hash) "
                  "VALUES (:user, crypt(:pass, gen_salt('bf')))");
    query.bindValue(":user", username);
    query.bindValue(":pass", password);
    
    if (!query.exec()) {
        lastError = QString("Ошибка регистрации: %1").arg(query.lastError().text());
        if (errorMsg) *errorMsg = lastError;
        qWarning() << lastError;
        return AuthResult::DatabaseError;
    }
    
    qInfo() << "Пользователь успешно зарегистрирован:" << username;
    return AuthResult::Success;
}

AuthResult AuthManager::authenticate(const QString& username, const QString& password) {
    if (!isConnected()) {
        return AuthResult::ConnectionError;
    }
    
    // Базовая валидация (без детальных сообщений для безопасности)
    if (username.isEmpty() || password.isEmpty()) {
        return AuthResult::InvalidCredentials;
    }
    
    QMutexLocker locker(&dbMutex);
    QSqlQuery query(db);
    
    query.prepare("SELECT id FROM users "
                  "WHERE username = :user "
                  "AND password_hash = crypt(:pass, password_hash)");
    query.bindValue(":user", username);
    query.bindValue(":pass", password);
    
    if (!query.exec()) {
        lastError = QString("Ошибка аутентификации: %1").arg(query.lastError().text());
        qWarning() << lastError;
        return AuthResult::DatabaseError;
    }
    
    if (!query.next()) {
        // Не раскрываем, что именно неправильно (username или password)
        return AuthResult::InvalidCredentials;
    }
    
    qInfo() << "Успешная аутентификация пользователя:" << username;
    return AuthResult::Success;
}

bool AuthManager::isConnected() const {
    return db.isOpen() && db.isValid();
}

QString AuthManager::getLastError() const {
    return lastError;
}
