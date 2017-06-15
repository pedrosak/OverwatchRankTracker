#include "overwatchcompetitiveranktracker.h"
#include "Plotter.h"
OverwatchCompetitiveRankTracker::OverwatchCompetitiveRankTracker(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QWidget *buttons = new QWidget;

	QPushButton *solo_plot_button = new QPushButton( "Solo Queue Plot" );
	QPushButton *duo_plot_button = new QPushButton( "Duo Queue Plot" );
	QPushButton *group_plot_button = new QPushButton( "Group Queue Plot" );

	QPalette buttons_palette = solo_plot_button->palette();
	buttons_palette.setColor( QPalette::Button, QColor( 250, 160, 46, 255 ) );
	buttons_palette.setColor( QPalette::ButtonText, QColor( 88, 79, 74, 255 ) );
	solo_plot_button->setAutoFillBackground( true );
	solo_plot_button->setPalette( buttons_palette );
	solo_plot_button->update();

	QHBoxLayout *plot_button_layout = new QHBoxLayout;

	plot_button_layout->setSpacing( 1 );
	plot_button_layout->addStretch( 10 );
	plot_button_layout->addWidget( solo_plot_button );
	plot_button_layout->addWidget( duo_plot_button );
	plot_button_layout->addWidget( group_plot_button );
	plot_button_layout->addStretch( 1 );
	buttons->setFixedHeight( 50 );

	buttons->setLayout( plot_button_layout );

	QVBoxLayout *main_layout = new QVBoxLayout;
	main_layout->addWidget( buttons );

	main_layout->addWidget( ui.plotWidget );

	ui.centralWidget->setLayout( main_layout );

	SetBackgroundColor( &ui );
	Plotter plotter( &ui );
}

OverwatchCompetitiveRankTracker::~OverwatchCompetitiveRankTracker()
{

}


void OverwatchCompetitiveRankTracker::SetBackgroundColor( Ui::OverwatchCompetitiveRankTrackerClass *ui )
{
	QPalette pal = palette();
	pal.setColor( QPalette::Window, RGB( 6, 6, 6 ) );
	ui->centralWidget->setAutoFillBackground( true );
	ui->centralWidget->setPalette( pal );
	
}