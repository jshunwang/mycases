#include "logion.h"
#include "ui_logion.h"

#include "rgswidget.h"
#include "chatwidget.h"
#include "protocol.h"
#include <QMessageBox>
#include <QCryptographicHash>
#include <QDebug>

LogIon::LogIon(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::LogIon)
{
	ui->setupUi(this);

	//构建套接字
	socket = new QUdpSocket(this);
	//连接信号与槽
	connect(this->socket, SIGNAL(readyRead()),\
			this, SLOT(socket_handler()));
}

LogIon::~LogIon()
{
	delete ui;
}

void LogIon::socket_handler()
{
	struct login_st buf;

	socket->readDatagram((char *)&buf, sizeof(buf));

	switch (buf.status) {
	case LOGIN_STATUS_OK:
		//登陆成功后创建聊天chat对象
		chat = new ChatWidget();
		chat->show();
		close();
		break;
	case LOGIN_STATUS_NOCNT:
		if (QMessageBox::question(this, QString("登录"),\
							  QString("用户名不存在，是否重新登录"),\
							  QMessageBox::Yes, QMessageBox::No) \
				== QMessageBox::No)
			close();
		break;
	case LOGIN_STATUS_ERRPWD:
		if (QMessageBox::question(this, QString("登录"),\
							  QString("密码错误，是否重新登录"),\
							  QMessageBox::Yes, QMessageBox::No) \
				== QMessageBox::No)
			close();
		break;
	default:
		break;
	}

}

//如过点击注册按键
void LogIon::on_countPushButton_clicked()
{
	//创建注册界面对象
	RgsWidget *rgs = new RgsWidget();
	//界面关闭时，销毁对象
	rgs->setAttribute(Qt::WA_DeleteOnClose);

	//show
	rgs->show();
}

//如果点击登陆按键
void LogIon::on_loginPushButton_clicked()
{
	struct rgs_st buf;

	//sndbuf.count
	QString cntStr = ui->countLineEdit->text();
	//QString--->c string
	QByteArray arr = cntStr.toLatin1();
	strncpy(buf.count, arr.data(), BUFSIZE);

	QString pwdStr = ui->passwdLineEdit->text();
	QByteArray pwdarr = pwdStr.toLatin1();
	pwdarr = QCryptographicHash::hash(pwdarr, QCryptographicHash::Md5);
	pwdarr = pwdarr.toHex();
	strncpy(buf.passwd, pwdarr.data(), BUFSIZE);

   // qDebug() << buf.count << buf.passwd;
	socket->writeDatagram((const char *)&buf, sizeof(buf), \
						  QHostAddress(QString(LOGIN_SERVER_IP)), \
						  LOGIN_SERVER_PORT);

	qDebug()<<"login server ip:"<<RGS_SERVER_IP;
}

