/********************************************************************************
** Form generated from reading UI file 'chatwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWIDGET_H
#define UI_CHATWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatWidget
{
public:
    QLabel *bgconfigLabel;
    QTreeWidget *treeWidget;
    QLabel *bgLabel;
    QLabel *userLabel;
    QLabel *bgtoolLabel;
    QTextEdit *logTextEdit;
    QTextEdit *inputTextEdit;
    QTextEdit *whoTextEdit;
    QPushButton *addfriPushButton;
    QPushButton *configPushButton;
    QPushButton *floderPushButton;
    QPushButton *callPushButton;
    QPushButton *emailPushButton;
    QPushButton *sendmsgPushButton;

    void setupUi(QWidget *ChatWidget)
    {
        if (ChatWidget->objectName().isEmpty())
            ChatWidget->setObjectName(QStringLiteral("ChatWidget"));
        ChatWidget->resize(650, 400);
        ChatWidget->setMinimumSize(QSize(650, 400));
        ChatWidget->setMaximumSize(QSize(650, 400));
        bgconfigLabel = new QLabel(ChatWidget);
        bgconfigLabel->setObjectName(QStringLiteral("bgconfigLabel"));
        bgconfigLabel->setGeometry(QRect(0, 0, 40, 400));
        bgconfigLabel->setMinimumSize(QSize(40, 400));
        bgconfigLabel->setMaximumSize(QSize(40, 400));
        bgconfigLabel->setStyleSheet(QLatin1String("\n"
"background-color: rgb(19, 186, 238);"));
        treeWidget = new QTreeWidget(ChatWidget);
        QFont font;
        font.setPointSize(11);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setFont(0, font);
        __qtreewidgetitem->setBackground(0, QColor(142, 222, 244));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setGeometry(QRect(40, 0, 180, 400));
        treeWidget->setMinimumSize(QSize(180, 400));
        treeWidget->setMaximumSize(QSize(180, 400));
        treeWidget->setStyleSheet(QStringLiteral("background-color: rgba(243, 249, 239, 230);"));
        bgLabel = new QLabel(ChatWidget);
        bgLabel->setObjectName(QStringLiteral("bgLabel"));
        bgLabel->setGeometry(QRect(0, 0, 650, 400));
        bgLabel->setMinimumSize(QSize(650, 400));
        bgLabel->setMaximumSize(QSize(650, 400));
        bgLabel->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/csky09.jpg")));
        userLabel = new QLabel(ChatWidget);
        userLabel->setObjectName(QStringLiteral("userLabel"));
        userLabel->setGeometry(QRect(6, 6, 32, 32));
        userLabel->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/dog02.png")));
        userLabel->setScaledContents(true);
        bgtoolLabel = new QLabel(ChatWidget);
        bgtoolLabel->setObjectName(QStringLiteral("bgtoolLabel"));
        bgtoolLabel->setGeometry(QRect(220, 260, 430, 30));
        bgtoolLabel->setStyleSheet(QStringLiteral("background-color: rgb(142, 222, 244,150);"));
        logTextEdit = new QTextEdit(ChatWidget);
        logTextEdit->setObjectName(QStringLiteral("logTextEdit"));
        logTextEdit->setGeometry(QRect(220, 28, 430, 232));
        logTextEdit->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255, 235);"));
        logTextEdit->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        inputTextEdit = new QTextEdit(ChatWidget);
        inputTextEdit->setObjectName(QStringLiteral("inputTextEdit"));
        inputTextEdit->setGeometry(QRect(220, 290, 430, 110));
        inputTextEdit->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255, 235);"));
        whoTextEdit = new QTextEdit(ChatWidget);
        whoTextEdit->setObjectName(QStringLiteral("whoTextEdit"));
        whoTextEdit->setGeometry(QRect(220, 0, 430, 28));
        whoTextEdit->setStyleSheet(QStringLiteral("background-color: rgba(253, 249, 239, 230);"));
        whoTextEdit->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        addfriPushButton = new QPushButton(ChatWidget);
        addfriPushButton->setObjectName(QStringLiteral("addfriPushButton"));
        addfriPushButton->setGeometry(QRect(6, 66, 30, 30));
        addfriPushButton->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/Add_group_96.png);"));
        addfriPushButton->setFlat(true);
        configPushButton = new QPushButton(ChatWidget);
        configPushButton->setObjectName(QStringLiteral("configPushButton"));
        configPushButton->setGeometry(QRect(6, 360, 30, 30));
        configPushButton->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/config_set_96.png);"));
        configPushButton->setFlat(true);
        floderPushButton = new QPushButton(ChatWidget);
        floderPushButton->setObjectName(QStringLiteral("floderPushButton"));
        floderPushButton->setGeometry(QRect(230, 260, 30, 30));
        floderPushButton->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/folder_96.png);"));
        floderPushButton->setFlat(true);
        callPushButton = new QPushButton(ChatWidget);
        callPushButton->setObjectName(QStringLiteral("callPushButton"));
        callPushButton->setGeometry(QRect(270, 260, 30, 30));
        callPushButton->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/microphone_96t.png);"));
        callPushButton->setFlat(true);
        emailPushButton = new QPushButton(ChatWidget);
        emailPushButton->setObjectName(QStringLiteral("emailPushButton"));
        emailPushButton->setGeometry(QRect(310, 260, 30, 30));
        emailPushButton->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/email_96.png);"));
        emailPushButton->setFlat(true);
        sendmsgPushButton = new QPushButton(ChatWidget);
        sendmsgPushButton->setObjectName(QStringLiteral("sendmsgPushButton"));
        sendmsgPushButton->setGeometry(QRect(610, 360, 30, 30));
        sendmsgPushButton->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/Send_96.png);"));
        sendmsgPushButton->setFlat(true);
        bgLabel->raise();
        bgconfigLabel->raise();
        treeWidget->raise();
        userLabel->raise();
        bgtoolLabel->raise();
        logTextEdit->raise();
        inputTextEdit->raise();
        whoTextEdit->raise();
        addfriPushButton->raise();
        configPushButton->raise();
        floderPushButton->raise();
        callPushButton->raise();
        emailPushButton->raise();
        sendmsgPushButton->raise();

        retranslateUi(ChatWidget);

        QMetaObject::connectSlotsByName(ChatWidget);
    } // setupUi

    void retranslateUi(QWidget *ChatWidget)
    {
        ChatWidget->setWindowTitle(QApplication::translate("ChatWidget", "chat", Q_NULLPTR));
        bgconfigLabel->setText(QString());
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("ChatWidget", "\346\210\221\347\232\204\345\245\275\345\217\213", Q_NULLPTR));
        bgLabel->setText(QString());
        userLabel->setText(QString());
        bgtoolLabel->setText(QString());
        addfriPushButton->setText(QString());
        configPushButton->setText(QString());
        floderPushButton->setText(QString());
        callPushButton->setText(QString());
        emailPushButton->setText(QString());
        sendmsgPushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ChatWidget: public Ui_ChatWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWIDGET_H
