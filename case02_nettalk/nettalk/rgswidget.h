#ifndef RGSWIDGET_H
#define RGSWIDGET_H

#include <QWidget>
#include <QUdpSocket>

namespace Ui {
class RgsWidget;
}

class RgsWidget : public QWidget
{
	Q_OBJECT

public:
	explicit RgsWidget(QWidget *parent = 0);
	~RgsWidget();

private slots:
	void on_countPushButton_clicked();
	void socket_handler();

private:
	Ui::RgsWidget *ui;
	QUdpSocket *socket;

};

#endif // RGSWIDGET_H
