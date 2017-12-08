/********************************************************************************
** Form generated from reading UI file 'rgswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RGSWIDGET_H
#define UI_RGSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RgsWidget
{
public:
    QLabel *label;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *countLineEdit;
    QLineEdit *passwdLineEdit;
    QLineEdit *passwdagainLineEdit;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *canclePushButton;
    QPushButton *countPushButton;
    QLabel *label_2;
    QTextEdit *textEdit;

    void setupUi(QWidget *RgsWidget)
    {
        if (RgsWidget->objectName().isEmpty())
            RgsWidget->setObjectName(QStringLiteral("RgsWidget"));
        RgsWidget->resize(300, 300);
        RgsWidget->setMinimumSize(QSize(300, 300));
        RgsWidget->setSizeIncrement(QSize(300, 300));
        label = new QLabel(RgsWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 300, 300));
        label->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/csky02.jpg);"));
        verticalLayoutWidget = new QWidget(RgsWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(60, 140, 181, 101));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        countLineEdit = new QLineEdit(verticalLayoutWidget);
        countLineEdit->setObjectName(QStringLiteral("countLineEdit"));

        verticalLayout->addWidget(countLineEdit);

        passwdLineEdit = new QLineEdit(verticalLayoutWidget);
        passwdLineEdit->setObjectName(QStringLiteral("passwdLineEdit"));
        passwdLineEdit->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(passwdLineEdit);

        passwdagainLineEdit = new QLineEdit(verticalLayoutWidget);
        passwdagainLineEdit->setObjectName(QStringLiteral("passwdagainLineEdit"));
        passwdagainLineEdit->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(passwdagainLineEdit);

        horizontalLayoutWidget = new QWidget(RgsWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(40, 250, 221, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(30);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        canclePushButton = new QPushButton(horizontalLayoutWidget);
        canclePushButton->setObjectName(QStringLiteral("canclePushButton"));
        canclePushButton->setStyleSheet(QStringLiteral("background-color: rgb(159, 251, 163);"));

        horizontalLayout->addWidget(canclePushButton);

        countPushButton = new QPushButton(horizontalLayoutWidget);
        countPushButton->setObjectName(QStringLiteral("countPushButton"));
        countPushButton->setStyleSheet(QStringLiteral("background-color: rgb(159, 251, 163);"));

        horizontalLayout->addWidget(countPushButton);

        label_2 = new QLabel(RgsWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 50, 71, 71));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/dog01_72.png")));
        label_2->setScaledContents(false);
        textEdit = new QTextEdit(RgsWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(110, 50, 131, 61));
        textEdit->setStyleSheet(QLatin1String("background-color: rgba(254, 252, 252, 0);\n"
""));

        retranslateUi(RgsWidget);

        QMetaObject::connectSlotsByName(RgsWidget);
    } // setupUi

    void retranslateUi(QWidget *RgsWidget)
    {
        RgsWidget->setWindowTitle(QApplication::translate("RgsWidget", "register", Q_NULLPTR));
        label->setText(QString());
        countLineEdit->setPlaceholderText(QApplication::translate("RgsWidget", "\350\276\223\345\205\245\347\224\250\346\210\267\345\220\215\357\274\232", Q_NULLPTR));
        passwdLineEdit->setText(QString());
        passwdLineEdit->setPlaceholderText(QApplication::translate("RgsWidget", "\350\276\223\345\205\245\345\257\206\347\240\201\357\274\232", Q_NULLPTR));
        passwdagainLineEdit->setPlaceholderText(QApplication::translate("RgsWidget", "\347\241\256\350\256\244\345\257\206\347\240\201\357\274\232", Q_NULLPTR));
        canclePushButton->setText(QApplication::translate("RgsWidget", "\345\217\226\346\266\210\346\263\250\345\206\214", Q_NULLPTR));
        countPushButton->setText(QApplication::translate("RgsWidget", "\347\253\213\345\215\263\346\263\250\345\206\214", Q_NULLPTR));
        label_2->setText(QString());
        textEdit->setHtml(QApplication::translate("RgsWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:600; font-style:italic;\">welcome to </span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:600; font-style:italic;\">join us !</span></p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RgsWidget: public Ui_RgsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RGSWIDGET_H
