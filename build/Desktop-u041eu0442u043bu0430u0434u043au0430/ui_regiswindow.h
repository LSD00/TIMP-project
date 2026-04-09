/********************************************************************************
** Form generated from reading UI file 'regiswindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISWINDOW_H
#define UI_REGISWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_regiswindow
{
public:
    QTextBrowser *textBrowser;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *regiswindow)
    {
        if (regiswindow->objectName().isEmpty())
            regiswindow->setObjectName("regiswindow");
        regiswindow->resize(391, 422);
        textBrowser = new QTextBrowser(regiswindow);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(40, 40, 311, 51));
        label = new QLabel(regiswindow);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 120, 81, 16));
        lineEdit = new QLineEdit(regiswindow);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(40, 150, 211, 23));
        label_2 = new QLabel(regiswindow);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 200, 131, 16));
        lineEdit_2 = new QLineEdit(regiswindow);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(40, 230, 211, 23));
        label_3 = new QLabel(regiswindow);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(40, 280, 121, 16));
        lineEdit_3 = new QLineEdit(regiswindow);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(40, 310, 113, 23));
        pushButton = new QPushButton(regiswindow);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(40, 360, 141, 23));
        pushButton_2 = new QPushButton(regiswindow);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(200, 360, 151, 23));

        retranslateUi(regiswindow);

        QMetaObject::connectSlotsByName(regiswindow);
    } // setupUi

    void retranslateUi(QDialog *regiswindow)
    {
        regiswindow->setWindowTitle(QCoreApplication::translate("regiswindow", "Dialog", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("regiswindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20pt;\">\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("regiswindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\270\320\274\321\217", nullptr));
        label_2->setText(QCoreApplication::translate("regiswindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\277\320\276\321\207\321\202\321\203", nullptr));
        label_3->setText(QCoreApplication::translate("regiswindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        pushButton->setText(QCoreApplication::translate("regiswindow", "\320\227\320\260\321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214\321\201\321\217", nullptr));
        pushButton_2->setText(QCoreApplication::translate("regiswindow", "\320\222\320\265\321\200\320\275\321\203\321\202\321\214\321\201\321\217 \320\272 \320\260\320\262\321\202\320\276\321\200\320\270\320\267\320\260\321\206\320\270\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class regiswindow: public Ui_regiswindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISWINDOW_H
