#ifndef NET_H
#define NET_H
#include <string>
#include <QVector>
#include <QJsonArray>
#include <nlohmann/json.hpp>
#include <fstream>
#include <ncrct.h>
#include <no_format_input.h>
#include <wrong_code.h>
#include <wrong_registration.h>
#include <wrong_mail.h>
#include <client.h>
inline Client client;
inline int code_for_pass=0;
inline std::string pas, malll;
void regist(std::string mail, std::string password);
void autor(std::string mail, std::string password, std::function<void(bool)> callback);
void respas(std::string mail, std::function<void(bool)> callback);
void nwpass(std::string password, std::function<void(bool)> callback);
void otprdat();
void for_codereset(std::string code, std::function<void(bool)> callback);
void for_pdtmail(std::string code, std::function<void(bool)> callback);
void crgrap(int a, int b, int c, std::function<void(QVector<double>)> callback);
#endif // NET_H
