#ifndef AUTH_MANAGER_H
#define AUTH_MANAGER_H

#include <string>
#include <memory>
#include <pqxx/pqxx>

class AuthManager {
public:
    // Конструктор сам подцепится к БД
    AuthManager();

    bool registerUser(const std::string& username, const std::string& password);
    bool authenticate(const std::string& username, const std::string& password);
    bool deleteUser(const std::string& username);

private:
    std::unique_ptr<pqxx::connection> conn;
};

#endif
