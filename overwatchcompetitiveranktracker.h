#ifndef OVERWATCHCOMPETITIVERANKTRACKER_H
#define OVERWATCHCOMPETITIVERANKTRACKER_H

#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include "Buttons.h"
#include "Plotter.h"
#include <qpalette.h>
#include "ui_overwatchcompetitiveranktracker.h"

class OverwatchCompetitiveRankTracker : public QMainWindow 
{
	Q_OBJECT
public:
	OverwatchCompetitiveRankTracker( QWidget *parent = 0 );
	~OverwatchCompetitiveRankTracker();

	public slots:
	void testingClick();

private:
	Ui::OverwatchCompetitiveRankTrackerClass ui;
	void OverwatchCompetitiveRankTracker::SetBackgroundColor( Ui::OverwatchCompetitiveRankTrackerClass *ui );

	Plotter *plotter_obj_ptr_;
	Plotter *plotter_;
	Buttons *button_;

	QWidget *plot_select_buttons_;
	QWidget *all_buttons_widget_;

	QPushButton *reset_button_;
	QHBoxLayout *buttons_layout_;
	QVBoxLayout *window_layout_;
 
};

#endif // OVERWATCHCOMPETITIVERANKTRACKER_H
