#include "overwatchcompetitiveranktracker.h"
#include <QtWidgets/QApplication>
#include "DataBreakdown.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	OverwatchCompetitiveRankTracker w;
	w.show();
	return a.exec();
}