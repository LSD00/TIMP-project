#include "AuthManager.h"
#include <stdexcept>
#include <cstdlib>


AuthManager::AuthManager() {

    std::string conn_str = "host=localhost port=5432 dbname=users_db user=postgres password=root";

    try {
        conn = std::make_unique<pqxx::connection>(conn_str);

        // САМОНАСТРОЙКА БАЗЫ
        pqxx::work W(*conn);

        // 1. Включаем криптографию внутри БД
        W.exec("CREATE EXTENSION IF NOT EXISTS pgcrypto;");

        // 2. Создаем таблицу, если её нет
        W.exec("CREATE TABLE IF NOT EXISTS users ("
        "id SERIAL PRIMARY KEY, "
        "username VARCHAR(50) UNIQUE NOT NULL, "
        "password_hash TEXT NOT NULL);");

        W.commit();
        // Всё! Теперь база готова к работе навсегда.

    } catch (const std::exception& e) {
        throw std::runtime_error("Критическая ошибка БД: " + std::string(e.what()));
    }
}

bool AuthManager::registerUser(const std::string& username, const std::string& password) {
    try {
        pqxx::work W(*conn);
        // Вся магия криптографии внутри SQL, код просто шлет строки
        W.exec("INSERT INTO users (username, password_hash) VALUES ($1, crypt($2, gen_salt('bf')))",
               pqxx::params{username, password});
        W.commit();
        return true;
    } catch (...) { return false; }
}

bool AuthManager::authenticate(const std::string& username, const std::string& password) {
    try {
        pqxx::nontransaction N(*conn);
        pqxx::result R = N.exec("SELECT id FROM users WHERE username = $1 AND password_hash = crypt($2, password_hash)",
                                pqxx::params{username, password});
        return !R.empty();
    } catch (...) { return false; }
}

bool AuthManager::deleteUser(const std::string& username) {
    try {
        pqxx::work W(*conn);
        W.exec("DELETE FROM users WHERE username = $1", pqxx::params{username});
        W.commit();
        return true;
    } catch (...) { return false; }
}
