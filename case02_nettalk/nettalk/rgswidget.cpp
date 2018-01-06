#include "rgswidget.h"
#include "ui_rgswidget.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>
#include <QUdpSocket>
#include "protocol.h"
#include <QCryptographicHash>

RgsWidget::RgsWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::RgsWidget)
{
	//使当前对象this与其对应的ui文件建立联系
	ui->setupUi(this);

	//设置窗口的显示位置
	QDesktopWidget *desktop = QApplication::desktop();
	this->move((desktop->width() - this->width()) / 2,\
			   (desktop->height() - this->height()) / 2);

	//构建套接字
	socket = new QUdpSocket(this);

	//连接信号与槽
	connect(this->socket, SIGNAL(readyRead()),\
			this, SLOT(socket_handler()));
}

RgsWidget::~RgsWidget()
{
	delete ui;
}

void RgsWidget::socket_handler()
{
	struct rgs_st buf;

	socket->readDatagram((char *)&buf, sizeof(buf));

	switch (buf.status) {
	case RGS_STATUS_OK:
		if (QMessageBox::information(this, QString("注册"),
									 QString("注册成功,立即登录"),\
									 QMessageBox::Yes) == QMessageBox::Yes) {
			close();
		}
		break;
	case RGS_STATUS_FAIL:
		if (QMessageBox::question(this, QString("注册"),\
							  QString("账号已被注册，是否重新注册"),\
							  QMessageBox::Yes, QMessageBox::No) \
				== QMessageBox::No)
			close();
		break;
	default:
		break;
	}

}

void RgsWidget::on_countPushButton_clicked()
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
						  QHostAddress(QString(RGS_SERVER_IP)), \
						  RGS_SERVER_PORT);
	qDebug()<<"rgs server ip:"<<RGS_SERVER_IP;
}
