#ifndef LOGION_H
#define LOGION_H

#include <QWidget>
#include <QUdpSocket>
#include "chatwidget.h"

namespace Ui {
class LogIon;
}

class LogIon : public QWidget
{
	Q_OBJECT

public:
	explicit LogIon(QWidget *parent = 0);
	~LogIon();

private slots:
	void on_countPushButton_clicked();

	void on_loginPushButton_clicked();
	void socket_handler();

private:
	Ui::LogIon *ui;
	QUdpSocket *socket;
	ChatWidget *chat;
};

#endif // LOGION_H
