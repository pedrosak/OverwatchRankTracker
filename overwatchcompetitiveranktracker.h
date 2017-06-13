#ifndef OVERWATCHCOMPETITIVERANKTRACKER_H
#define OVERWATCHCOMPETITIVERANKTRACKER_H

#include <QtWidgets/QMainWindow>
#include <qpalette.h>
#include "ui_overwatchcompetitiveranktracker.h"

class OverwatchCompetitiveRankTracker : public QMainWindow
{
	Q_OBJECT

public:
	OverwatchCompetitiveRankTracker( QWidget *parent = 0 );
	~OverwatchCompetitiveRankTracker();

private:
	Ui::OverwatchCompetitiveRankTrackerClass ui;
	void OverwatchCompetitiveRankTracker::SetBackgroundColor( Ui::OverwatchCompetitiveRankTrackerClass *ui );
};

#endif // OVERWATCHCOMPETITIVERANKTRACKER_H
