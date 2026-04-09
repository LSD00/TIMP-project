/********************************************************************************
** Form generated from reading UI file 'restmail.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESTMAIL_H
#define UI_RESTMAIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_restmail
{
public:
    QTextBrowser *textBrowser;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *restmail)
    {
        if (restmail->objectName().isEmpty())
            restmail->setObjectName("restmail");
        restmail->resize(373, 265);
        textBrowser = new QTextBrowser(restmail);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(40, 40, 291, 51));
        label = new QLabel(restmail);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 120, 131, 16));
        lineEdit = new QLineEdit(restmail);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(40, 150, 191, 23));
        pushButton = new QPushButton(restmail);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(40, 200, 111, 23));
        pushButton_2 = new QPushButton(restmail);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(180, 200, 151, 23));

        retranslateUi(restmail);

        QMetaObject::connectSlotsByName(restmail);
    } // setupUi

    void retranslateUi(QDialog *restmail)
    {
        restmail->setWindowTitle(QCoreApplication::translate("restmail", "Dialog", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("restmail", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20pt;\">\320\241\320\261\321\200\320\276\321\201 \320\277\320\260\321\200\320\276\320\273\321\217</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("restmail", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\201\320\262\320\276\321\216 \320\277\320\276\321\207\321\202\321\203", nullptr));
        pushButton->setText(QCoreApplication::translate("restmail", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214 \320\277\320\270\321\201\321\214\320\274\320\276", nullptr));
        pushButton_2->setText(QCoreApplication::translate("restmail", "\320\222\320\265\321\200\320\275\321\203\321\202\321\214\321\201\321\217 \320\272 \320\260\320\262\321\202\320\276\321\200\320\270\320\267\320\260\321\206\320\270\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class restmail: public Ui_restmail {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESTMAIL_H
