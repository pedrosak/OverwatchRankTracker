#include "overwatchcompetitiveranktracker.h"
#include "Plotter.h"
OverwatchCompetitiveRankTracker::OverwatchCompetitiveRankTracker(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
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