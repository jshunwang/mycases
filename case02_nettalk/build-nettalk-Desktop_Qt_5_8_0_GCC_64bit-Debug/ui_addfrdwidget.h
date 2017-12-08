/********************************************************************************
** Form generated from reading UI file 'addfrdwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDFRDWIDGET_H
#define UI_ADDFRDWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddfrdWidget
{
public:
    QLabel *backgroundLabel;
    QLineEdit *fricountLineEdit;
    QTextEdit *descrpTextEdit;
    QPushButton *sendPushButton_2;
    QPushButton *sendPushButton_3;

    void setupUi(QWidget *AddfrdWidget)
    {
        if (AddfrdWidget->objectName().isEmpty())
            AddfrdWidget->setObjectName(QStringLiteral("AddfrdWidget"));
        AddfrdWidget->resize(300, 200);
        AddfrdWidget->setMinimumSize(QSize(300, 200));
        AddfrdWidget->setMaximumSize(QSize(300, 200));
        backgroundLabel = new QLabel(AddfrdWidget);
        backgroundLabel->setObjectName(QStringLiteral("backgroundLabel"));
        backgroundLabel->setGeometry(QRect(0, 0, 300, 200));
        backgroundLabel->setMinimumSize(QSize(300, 200));
        backgroundLabel->setMaximumSize(QSize(300, 200));
        backgroundLabel->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/csky05.jpg")));
        backgroundLabel->setScaledContents(true);
        fricountLineEdit = new QLineEdit(AddfrdWidget);
        fricountLineEdit->setObjectName(QStringLiteral("fricountLineEdit"));
        fricountLineEdit->setGeometry(QRect(30, 30, 240, 25));
        fricountLineEdit->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255, 230);"));
        descrpTextEdit = new QTextEdit(AddfrdWidget);
        descrpTextEdit->setObjectName(QStringLiteral("descrpTextEdit"));
        descrpTextEdit->setGeometry(QRect(30, 70, 240, 70));
        descrpTextEdit->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255, 230);"));
        sendPushButton_2 = new QPushButton(AddfrdWidget);
        sendPushButton_2->setObjectName(QStringLiteral("sendPushButton_2"));
        sendPushButton_2->setGeometry(QRect(30, 160, 90, 30));
        sendPushButton_2->setStyleSheet(QStringLiteral("background-color: rgba(120, 219, 101, 247);"));
        sendPushButton_3 = new QPushButton(AddfrdWidget);
        sendPushButton_3->setObjectName(QStringLiteral("sendPushButton_3"));
        sendPushButton_3->setGeometry(QRect(180, 160, 90, 30));
        sendPushButton_3->setStyleSheet(QStringLiteral("background-color: rgba(120, 219, 101, 247);"));

        retranslateUi(AddfrdWidget);

        QMetaObject::connectSlotsByName(AddfrdWidget);
    } // setupUi

    void retranslateUi(QWidget *AddfrdWidget)
    {
        AddfrdWidget->setWindowTitle(QApplication::translate("AddfrdWidget", "addfriend", Q_NULLPTR));
        backgroundLabel->setText(QString());
        fricountLineEdit->setPlaceholderText(QApplication::translate("AddfrdWidget", "\345\245\275\345\217\213\347\224\250\346\210\267\345\220\215\357\274\232", Q_NULLPTR));
        descrpTextEdit->setPlaceholderText(QApplication::translate("AddfrdWidget", "\351\252\214\350\257\201\344\277\241\346\201\257\357\274\232", Q_NULLPTR));
        sendPushButton_2->setText(QApplication::translate("AddfrdWidget", "\345\217\226\346\266\210", Q_NULLPTR));
        sendPushButton_3->setText(QApplication::translate("AddfrdWidget", "\346\267\273\345\212\240", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AddfrdWidget: public Ui_AddfrdWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDFRDWIDGET_H
