#include "overwatchcompetitiveranktracker.h"

OverwatchCompetitiveRankTracker::OverwatchCompetitiveRankTracker(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	plotter_ = new  Plotter( &ui );
	plotter_obj_ptr_ = plotter_->GetObjectPointer();

	button_ = new Buttons();
	plot_select_buttons_= button_->CreateButtons();
	reset_button_ = new QPushButton( "Reload Plot" );

	buttons_layout_ = new QHBoxLayout;
	buttons_layout_->addWidget( reset_button_ );
	buttons_layout_->addWidget( plot_select_buttons_);

	all_buttons_widget_ = new QWidget();
	all_buttons_widget_->setFixedHeight( 50 );
	all_buttons_widget_->setLayout( buttons_layout_ );

	window_layout_ = new QVBoxLayout;
	window_layout_->addWidget( all_buttons_widget_ );
	window_layout_->addWidget( ui.plotWidget );
	ui.centralWidget->setLayout( window_layout_ );

	SetBackgroundColor( &ui );

	QObject::connect( reset_button_, SIGNAL( clicked() ), SLOT( testingClick() ) );
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

void OverwatchCompetitiveRankTracker::testingClick()
{
	qDebug() << "This is crazy";
}

