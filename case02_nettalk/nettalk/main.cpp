#include "logion.h"
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	LogIon w;

	//设置窗口的出现位置为屏幕中间
	QDesktopWidget *desktop = QApplication::desktop();
	w.move((desktop->width() - w.width()) / 2,\
		   (desktop->height() - w.height()) / 2);
	//显示w窗口
	w.show();

	return a.exec();
}
