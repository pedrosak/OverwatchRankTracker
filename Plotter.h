#pragma once
#include <iostream>
#include <fstream>
#include <QVector>
#include <QWidget>
#include "DataBreakdown.h"
#include "qcustomplot.h"
#include "ui_overwatchcompetitiveranktracker.h"
#include <QPalette>


class Plotter : public QMainWindow
{	
public:
	Plotter();
	Plotter( Ui::OverwatchCompetitiveRankTrackerClass *ui );
	void Plotter::RenderPlot( QVector<double> x_vector, QVector<double> y_vector, Ui::OverwatchCompetitiveRankTrackerClass *ui, QCPScatterStyle::ScatterShape symbol, Qt::GlobalColor symbol_color, QColor brush_color, QColor pen_color );
	void Plotter::ConfigurePlot( Ui::OverwatchCompetitiveRankTrackerClass *ui, QCPGraph *graph, QVector<double> x_vector, QVector<double> y_vector );
	Plotter* Plotter::GetObjectPointer();


private:
	void Plotter::SetBackgroundColor( Ui::OverwatchCompetitiveRankTrackerClass *ui );
	double Plotter::FindMaxOfVector( QVector<double> input_vector );
	double Plotter::FindMinOfVector( QVector<double> input_vector );

	Ui::OverwatchCompetitiveRankTrackerClass *ui;
	QVector<QVector<double>> multiple_plot_data;
};