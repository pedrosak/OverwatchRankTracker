#pragma once
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QSignalMapper>

class Buttons : public QWidget
{
	Q_OBJECT
public:
	Buttons();
	QWidget* Buttons::CreateButtons();

	public slots:
	void testSLOT( QAbstractButton*  button );

};