#include <QDebug>
#include "net.h"
void regist(std::string name, std::string mail, std::string password){
    nlohmann::json for_registration;
    for_registration["name"]=name;
    for_registration["mail"]=mail;
    for_registration["password"]=password;
    std::ofstream file_for_registration("for_registration.json");
    file_for_registration << for_registration.dump(4);
    file_for_registration.close();
    std::ifstream for_code("for_code.json");
    nlohmann::json for_cod;
    for_code >> for_cod;
    code_for_pass=for_cod["code"];
}
bool autor(std::string mail, std::string password){
    nlohmann::json for_authorization;
    for_authorization["mail"]=mail;
    for_authorization["password"]=password;
    std::ofstream file_for_authorization("for_authorization.json");
    file_for_authorization << for_authorization.dump(4);
    file_for_authorization.close();
    std::ifstream for_allow("for_allow.json");
    nlohmann::json for_cod;
    for_allow >> for_cod;
    return for_cod["allow"];
}
bool respas(std::string mail){
    nlohmann::json for_registration;
    for_registration["mail"]=mail;
    std::ofstream file_for_registration("for_mail.json");
    file_for_registration << for_registration.dump(4);
    file_for_registration.close();
    std::ifstream for_allow("for_allow.json");
    nlohmann::json for_cod;
    for_allow >> for_cod;
    code_for_pass=for_cod["allow"];

}
bool nwpass(std::string password){

}
QVector<double> crgrap(int a, int b, int c){
    QVector<double> res;
    for (double i = -10; i < 10; i=i+0.067) {
        if (i < 0) {
            res.push_back(a / (i*i - 1));
        }
        if (i >= 0 && i < 1) {
            res.push_back((1 / i) + b);
        }
        if (i > 1) {
            res.push_back((c * i) / (i * i + 1));
        }
    }
    return res;
}
void otprdat(){};