#ifndef NET_H
#define NET_H
#include <string>
#include <QVector>
bool regist(std::string name, std::string mail, std::string password);
bool autor(std::string mail, std::string password);
bool respas(std::string mail);
QVector<double> crgrap(int a, int b, int c);
#endif // NET_H
