#pragma once
#include <iostream>
#include <fstream>
#include <QVector>
#include <qwidget.h>
#include "FileReader.h"
#include "qcustomplot.h"
#include "ui_overwatchcompetitiveranktracker.h"
#include <qpalette.h>

using int16 = __int16;

class Plotter : public QWidget
{
public:
	Plotter();
	Plotter( Ui::OverwatchCompetitiveRankTrackerClass *ui );
	void Plotter::RenderPlot( std::vector<FileDataTuple>* data_ptr, Ui::OverwatchCompetitiveRankTrackerClass *ui );
	void Plotter::PreparePlotData(std::vector<FileDataTuple> *data );
	QCPGraph* Plotter::CreatePlot( QVector<double> x_data, QVector<double> y_data );
	void Plotter::ConfigurePlot( Ui::OverwatchCompetitiveRankTrackerClass *ui , QCPGraph *graph );
private:
	void Plotter::SetXValues( QVector<double> x_vector_data );
	void Plotter::SetYValues( QVector<double> y_vector_data );
	QVector<double> Plotter::GetXValues();
	QVector<double> Plotter::GetYValues();

	void Plotter::SetBackgroundColor( Ui::OverwatchCompetitiveRankTrackerClass *ui );
	double Plotter::FindMaxOfVector( QVector<double> input_vector );
	double Plotter::FindMinOfVector( QVector<double> input_vector );

	QVector<double> x_, y_;
};