/********************************************************************************
** Form generated from reading UI file 'logion.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGION_H
#define UI_LOGION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogIon
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *countLineEdit;
    QLineEdit *passwdLineEdit;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *countPushButton;
    QPushButton *loginPushButton;
    QLabel *versionLabel;
    QLabel *loginbackgroundLabel;

    void setupUi(QWidget *LogIon)
    {
        if (LogIon->objectName().isEmpty())
            LogIon->setObjectName(QStringLiteral("LogIon"));
        LogIon->resize(300, 200);
        LogIon->setMinimumSize(QSize(300, 200));
        LogIon->setMaximumSize(QSize(300, 200));
        LogIon->setCursor(QCursor(Qt::UpArrowCursor));
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/prefix1/dog01.png"), QSize(), QIcon::Normal, QIcon::Off);
        LogIon->setWindowIcon(icon);
        verticalLayoutWidget = new QWidget(LogIon);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(60, 60, 181, 71));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        countLineEdit = new QLineEdit(verticalLayoutWidget);
        countLineEdit->setObjectName(QStringLiteral("countLineEdit"));

        verticalLayout->addWidget(countLineEdit);

        passwdLineEdit = new QLineEdit(verticalLayoutWidget);
        passwdLineEdit->setObjectName(QStringLiteral("passwdLineEdit"));

        verticalLayout->addWidget(passwdLineEdit);

        horizontalLayoutWidget = new QWidget(LogIon);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(40, 150, 221, 33));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(30);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        countPushButton = new QPushButton(horizontalLayoutWidget);
        countPushButton->setObjectName(QStringLiteral("countPushButton"));
        countPushButton->setStyleSheet(QStringLiteral("background-color: rgba(175, 241, 254, 8);"));

        horizontalLayout->addWidget(countPushButton);

        loginPushButton = new QPushButton(horizontalLayoutWidget);
        loginPushButton->setObjectName(QStringLiteral("loginPushButton"));
        loginPushButton->setStyleSheet(QStringLiteral("background-color: rgba(175, 241, 254, 8);"));

        horizontalLayout->addWidget(loginPushButton);

        versionLabel = new QLabel(LogIon);
        versionLabel->setObjectName(QStringLiteral("versionLabel"));
        versionLabel->setGeometry(QRect(190, 0, 111, 20));
        QFont font;
        font.setItalic(true);
        versionLabel->setFont(font);
        loginbackgroundLabel = new QLabel(LogIon);
        loginbackgroundLabel->setObjectName(QStringLiteral("loginbackgroundLabel"));
        loginbackgroundLabel->setGeometry(QRect(0, 0, 300, 200));
        loginbackgroundLabel->setMinimumSize(QSize(300, 200));
        loginbackgroundLabel->setMaximumSize(QSize(300, 200));
        loginbackgroundLabel->setAutoFillBackground(true);
        loginbackgroundLabel->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/csky01.jpg")));
        loginbackgroundLabel->setScaledContents(true);
        loginbackgroundLabel->raise();
        verticalLayoutWidget->raise();
        horizontalLayoutWidget->raise();
        versionLabel->raise();

        retranslateUi(LogIon);

        QMetaObject::connectSlotsByName(LogIon);
    } // setupUi

    void retranslateUi(QWidget *LogIon)
    {
        LogIon->setWindowTitle(QApplication::translate("LogIon", "LogIn", Q_NULLPTR));
        countLineEdit->setPlaceholderText(QApplication::translate("LogIon", "\345\270\220\345\217\267\357\274\232", Q_NULLPTR));
        passwdLineEdit->setPlaceholderText(QApplication::translate("LogIon", "\345\257\206\347\240\201\357\274\232", Q_NULLPTR));
        countPushButton->setText(QApplication::translate("LogIon", "\346\263\250\345\206\214", Q_NULLPTR));
        loginPushButton->setText(QApplication::translate("LogIon", "\347\231\273\345\275\225", Q_NULLPTR));
        versionLabel->setText(QApplication::translate("LogIon", "my nettalk 2017", Q_NULLPTR));
        loginbackgroundLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LogIon: public Ui_LogIon {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGION_H
