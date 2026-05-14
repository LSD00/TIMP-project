#ifndef NET_H
#define NET_H
#include <string>
#include <QVector>
#include <nlohmann/json.hpp>
#include <fstream>
#include <ncrct.h>
#include <no_format_input.h>
#include <wrong_code.h>
inline int code_for_pass=0;
inline std::string nae, pas, malll;
void regist(std::string name, std::string mail, std::string password);
bool autor(std::string mail, std::string password);
bool respas(std::string mail);
bool nwpass(std::string password);
void otprdat();
QVector<double> crgrap(int a, int b, int c);
#endif // NET_H
