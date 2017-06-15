#pragma once
#include <QVector>
#include <QDebug>
#include "FileReader.h"
#include <vector>

class DataBreakdown
{
public:
	DataBreakdown();
	QVector<QVector<double>> DataBreakdown::GetFullPlotData();
	void DataBreakdown::GenerateGroupInfoPlot();
	void DataBreakdown::SeparateByDate();
	void DataBreakdown::CalculateFitLine();
	void DataBreakdown::PreparePlotData();
private:
	std::vector<FileDataTuple> data_from_fileReader_;
	QVector<double> x_, y_;
	QVector<double> solo_queue_x_value_, solo_queue_y_value_;
	QVector<double> duo_queue_x_value_, duo_queue_y_value_;
	QVector<double> group_queue_x_value_, group_queue_y_value_;
	QVector<double> fit_line_x_value_, fit_line_y_value_;

	void DataBreakdown::ResizeAllXYvalues( int solo_queue_ize, int duo_queue_size, int group_queue_size );
	int DataBreakdown::CountElementsInVector( QString element );

	int DataBreakdown::CalculateAverage( QVector<double> value );
};