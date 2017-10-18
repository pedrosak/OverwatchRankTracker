#include "Buttons.h"
#include <QMainWindow>

Buttons::Buttons()
{

}

QWidget* Buttons::CreateButtons()
{
	QWidget *buttons_widget = new QWidget;

	QPushButton *solo_plot_button = new QPushButton( "Solo Queue Plot" );
	QPushButton *duo_plot_button = new QPushButton( "Duo Queue Plot" );
	QPushButton *group_plot_button = new QPushButton( "Group Queue Plot" );

	QHBoxLayout *plot_button_layout = new QHBoxLayout;

	plot_button_layout->addStretch( 12 );
	plot_button_layout->addWidget( solo_plot_button );
	plot_button_layout->addWidget( duo_plot_button );
	plot_button_layout->addWidget( group_plot_button );
	buttons_widget->setFixedHeight( 50 );

	buttons_widget->setLayout( plot_button_layout );

	QButtonGroup *button_group = new QButtonGroup( plot_button_layout );
	button_group->addButton( solo_plot_button, 1 );
	button_group->addButton( duo_plot_button, 2 );
	button_group->addButton( group_plot_button, 3 );

	QObject::connect( button_group, SIGNAL( buttonClicked( QAbstractButton* )), SLOT( testSLOT( QAbstractButton*  ) ) ) ;

	QVBoxLayout *main_layout = new QVBoxLayout;

	return buttons_widget;
}

void Buttons::testSLOT( QAbstractButton*  button )
{
	qDebug() << "Clicked button number " + button->text();
}