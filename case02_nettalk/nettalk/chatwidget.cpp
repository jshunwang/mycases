#include "chatwidget.h"
#include "ui_chatwidget.h"
#include <QDesktopWidget>
#include "addfrdwidget.h"
#include <QUdpSocket>

ChatWidget::ChatWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ChatWidget)
{
	ui->setupUi(this);
	//设置本窗口在桌面上的位置
	QDesktopWidget *desktop = QApplication::desktop();
	this->move((desktop->width() - this ->width()) / 2,\
			   (desktop->height() - this->height()) / 2);

	//构建套接字
	socket = new QUdpSocket(this);

	//连接信号与槽
	connect(this->socket, SIGNAL(readyRead()),\
			this, SLOT(socket_handler()));

}

ChatWidget::~ChatWidget()
{
	delete ui;
}

int ChatWidget::socket_handler()
{
	return 0;
}

void ChatWidget::on_addfriPushButton_clicked()
{
   //创建添加好友界面的对象
	AddfrdWidget *add = new AddfrdWidget();

	add->show();
}
