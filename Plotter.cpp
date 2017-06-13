#include "Plotter.h"

Plotter::Plotter()
{
}

Plotter::Plotter( Ui::OverwatchCompetitiveRankTrackerClass *ui )
{
	FileReader fileReader;
	QString file_name = fileReader.ChooseFile();
	std::vector<FileDataTuple> *data = fileReader.ParseFile( file_name );

	RenderPlot( data, ui );
}

void Plotter::RenderPlot( std::vector<FileDataTuple>* data_ptr, Ui::OverwatchCompetitiveRankTrackerClass *ui )
{
	// Prepare Data
	PreparePlotData( data_ptr );
	// Create and Configure plottable
	QCPGraph *graph = ui->plotWidget->addGraph();
	graph->addData( x_, y_ );
	graph->setScatterStyle( QCPScatterStyle( QCPScatterStyle::ssCircle, QPen( Qt::white, 0.25 ), QBrush( QColor(250, 160, 46, 255)  ), 4.5 ) );
	graph->setPen( QPen( QColor( 250, 160, 46, 80 ), 2.5 ) );
	ConfigurePlot( ui, graph );
}

void Plotter::PreparePlotData( std::vector<FileDataTuple> *data )
{
	x_.resize( std::get<0>( data->back() ));
	y_.resize( std::get<0>( data->back() ));

	// Populate the vector with data
	// Both x and y must be the same size
	for( int count_i = 0; count_i < x_.size(); ++count_i )
	{
		x_[ count_i ] = std::get<0>( data->at( count_i ) );
		y_[ count_i ] = std::get<1>( data->at( count_i ) ).rank;
	}

	SetXValues( x_ );
	SetYValues( y_ );
}

QCPGraph * Plotter::CreatePlot( QVector<double> x_data, QVector<double> y_data )
{
	
	return nullptr;
}

void Plotter::ConfigurePlot( Ui::OverwatchCompetitiveRankTrackerClass *ui, QCPGraph *graph )
{
	SetBackgroundColor( ui );

	QFont lable_font = font();
	lable_font.setFamily( "Helvetica" );
	lable_font.setPointSize( 10.5 );

	QFont axis_lable_font = font();
	axis_lable_font.setFamily( "Helvetica" );
	axis_lable_font.setPointSize( 13.5 );

	ui->plotWidget->addLayer( "abovemain", ui->plotWidget->layer("main"), QCustomPlot::limAbove );
	graph->setLayer( "abovemain" );

	ui->plotWidget->xAxis->setBasePen( QPen( QColor( 64, 82, 117, 90 ), 2 ) );
	ui->plotWidget->yAxis->setBasePen( QPen( QColor( 64, 82, 117, 90 ), 2 ) ); // Axis line
	ui->plotWidget->xAxis->setTickPen( QPen( QColor( 64, 82, 117, 90 ), 2 ) ); // Main Tick poitns
	ui->plotWidget->yAxis->setTickPen( QPen( QColor( 64, 82, 117, 90 ), 2 ) );
	ui->plotWidget->xAxis->setSubTickPen( QPen( QColor( 64, 82, 117, 210 ), 1 ) ); // Secondary Ticks
	ui->plotWidget->yAxis->setSubTickPen( QPen( QColor( 64, 82, 117, 210 ), 1 ) );
	ui->plotWidget->xAxis->setTickLabelColor( QColor( 64, 82, 117, 255 ) );
	ui->plotWidget->yAxis->setTickLabelColor( QColor( 64, 82, 117, 225 ) ); // Labels
	ui->plotWidget->xAxis->setTickLabelFont( lable_font );
	ui->plotWidget->yAxis->setTickLabelFont( lable_font );

	ui->plotWidget->xAxis->setLabel( "Play Count" );
	ui->plotWidget->yAxis->setLabel( "Skill Rating" );
	ui->plotWidget->xAxis->setLabelFont( axis_lable_font );
	ui->plotWidget->yAxis->setLabelFont( axis_lable_font );
	ui->plotWidget->xAxis->setLabelColor( QColor( 33, 143, 180, 255 ) );
	ui->plotWidget->yAxis->setLabelColor( QColor( 33, 143, 180, 255 ) );

	ui->plotWidget->xAxis->grid()->setPen( QPen( QColor( 64, 82, 117, 80 ), 1, Qt::DashDotDotLine ) );
	ui->plotWidget->yAxis->grid()->setPen( QPen( QColor( 64, 82, 117, 80 ), 1, Qt::DashDotDotLine ) );
	ui->plotWidget->xAxis->grid()->setSubGridPen( QPen( QColor( 64, 82, 117, 45 ), 1, Qt::DashDotDotLine ) );
	ui->plotWidget->yAxis->grid()->setSubGridPen( QPen( QColor( 64, 82, 117, 45 ), 1, Qt::DashDotDotLine ) );
	ui->plotWidget->xAxis->grid()->setSubGridVisible( true );
	ui->plotWidget->yAxis->grid()->setSubGridVisible( true );

	ui->plotWidget->rescaleAxes();
	ui->plotWidget->xAxis->setRange( 0, FindMaxOfVector( x_ ) + 5 );
	ui->plotWidget->yAxis->setRange( FindMinOfVector(y_) - 50 , FindMaxOfVector( y_ ) + 50 );

}

inline void Plotter::SetXValues( QVector<double> x_vector_data ) { x_ = x_vector_data; }

inline void Plotter::SetYValues( QVector<double> y_vector_data ) { y_ = y_vector_data; }

inline QVector<double> Plotter::GetXValues() { return x_; }

inline QVector<double> Plotter::GetYValues() { return y_; }

void Plotter::SetBackgroundColor( Ui::OverwatchCompetitiveRankTrackerClass *ui )
{
	QLinearGradient plotGradient;
	plotGradient.setStart( 0, 0 );
	plotGradient.setFinalStop( 0, 350 );
	plotGradient.setColorAt( 1, QColor( 6, 6, 6, 255 ) );
	plotGradient.setColorAt( 0, QColor( 6, 6, 6, 255 ) );
	ui->plotWidget->setBackground( plotGradient );
}

double Plotter::FindMaxOfVector( QVector<double> input_vector )
{
	double vector_max = *std::max_element( input_vector.begin(), input_vector.end() );

	return vector_max;
}

double Plotter::FindMinOfVector( QVector<double> input_vector )
{
	double vector_min = *std::min_element( input_vector.begin(), input_vector.end() );

	return vector_min;
}