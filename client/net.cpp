#include <QDebug>
#include "net.h"
bool regist(std::string name, std::string mail, std::string password){
    qDebug()<<name<<mail<<password;
    return true;
}
bool autor(std::string mail, std::string password){
    qDebug()<<mail<<password;
    return true;
}
bool respas(std::string mail){
    qDebug()<<mail;
    return true;
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