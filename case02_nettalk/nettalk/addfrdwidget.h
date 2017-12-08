#ifndef ADDFRDWIDGET_H
#define ADDFRDWIDGET_H

#include <QWidget>

namespace Ui {
class AddfrdWidget;
}

class AddfrdWidget : public QWidget
{
	Q_OBJECT

public:
	explicit AddfrdWidget(QWidget *parent = 0);
	~AddfrdWidget();

private:
	Ui::AddfrdWidget *ui;
};

#endif // ADDFRDWIDGET_H
