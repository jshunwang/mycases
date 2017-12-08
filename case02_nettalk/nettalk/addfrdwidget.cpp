#include "addfrdwidget.h"
#include "ui_addfrdwidget.h"
#include <QDesktopWidget>

AddfrdWidget::AddfrdWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::AddfrdWidget)
{
	ui->setupUi(this);

	//设置本窗口在桌面上的位置
	QDesktopWidget *desktop = QApplication::desktop();
	this->move((desktop->width() - this ->width()) / 2,\
			   (desktop->height() - this->height()) / 2);
}

AddfrdWidget::~AddfrdWidget()
{
	delete ui;
}
