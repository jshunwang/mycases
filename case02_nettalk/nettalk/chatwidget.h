#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include <QUdpSocket>

namespace Ui {
class ChatWidget;
}

class ChatWidget : public QWidget
{
	Q_OBJECT

public:
	explicit ChatWidget(QWidget *parent = 0);
	~ChatWidget();

private slots:
	void on_addfriPushButton_clicked();
	int socket_handler();

private:
	Ui::ChatWidget *ui;
	QUdpSocket *socket;
};

#endif // CHATWIDGET_H
