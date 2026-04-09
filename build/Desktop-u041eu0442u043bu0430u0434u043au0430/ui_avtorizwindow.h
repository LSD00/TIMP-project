/********************************************************************************
** Form generated from reading UI file 'avtorizwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AVTORIZWINDOW_H
#define UI_AVTORIZWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_avtorizwindow
{
public:
    QWidget *centralwidget;
    QLineEdit *lineEdit;
    QTextBrowser *textBrowser;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *avtorizwindow)
    {
        if (avtorizwindow->objectName().isEmpty())
            avtorizwindow->setObjectName("avtorizwindow");
        avtorizwindow->resize(333, 412);
        centralwidget = new QWidget(avtorizwindow);
        centralwidget->setObjectName("centralwidget");
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(40, 140, 113, 23));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(40, 40, 251, 51));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 110, 161, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 190, 91, 16));
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(40, 210, 113, 23));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(40, 260, 251, 41));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(40, 310, 111, 41));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(180, 310, 111, 41));
        avtorizwindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(avtorizwindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 333, 20));
        avtorizwindow->setMenuBar(menubar);
        statusbar = new QStatusBar(avtorizwindow);
        statusbar->setObjectName("statusbar");
        avtorizwindow->setStatusBar(statusbar);

        retranslateUi(avtorizwindow);

        QMetaObject::connectSlotsByName(avtorizwindow);
    } // setupUi

    void retranslateUi(QMainWindow *avtorizwindow)
    {
        avtorizwindow->setWindowTitle(QCoreApplication::translate("avtorizwindow", "avtorizwindow", nullptr));
        lineEdit->setText(QString());
        textBrowser->setHtml(QCoreApplication::translate("avtorizwindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20pt;\">\320\222\320\276\320\271\320\264\320\270\321\202\320\265 \320\262 \320\260\320\272\320\272\320\260\321\203\320\275\321\202</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("avtorizwindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\215\320\273\320\265\320\272\321\202\321\200\320\276\320\275\320\275\321\203\321\216 \320\277\320\276\321\207\321\202\321\203", nullptr));
        label_2->setText(QCoreApplication::translate("avtorizwindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        pushButton->setText(QCoreApplication::translate("avtorizwindow", "\320\222\320\276\320\271\321\202\320\270", nullptr));
        pushButton_2->setText(QCoreApplication::translate("avtorizwindow", "\320\241\320\261\321\200\320\276\321\201 \320\277\320\260\321\200\320\276\320\273\321\217", nullptr));
        pushButton_3->setText(QCoreApplication::translate("avtorizwindow", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class avtorizwindow: public Ui_avtorizwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AVTORIZWINDOW_H
