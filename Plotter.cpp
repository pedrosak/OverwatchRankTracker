#include "Plotter.h"

Plotter::Plotter()
{
	qDebug() << "Plotter constructor was called.";
}

Plotter::Plotter( Ui::OverwatchCompetitiveRankTrackerClass *ui )
{
	ui = ui;
	DataBreakdown dataBreakdown;
	dataBreakdown.StartBreakingDownData();
	multiple_plot_data = dataBreakdown.GetFullPlotData();
	RenderPlot( multiple_plot_data[ 8 ], multiple_plot_data[ 9 ], ui, QCPScatterStyle::ssCircle, Qt::white, QColor( 249, 158, 26, 255 ), QColor( 249, 158, 26, 255 ) );
	//RenderPlot( multiple_plot_data[ 2 ], multiple_plot_data[ 3 ], ui, QCPScatterStyle::ssCross, Qt::yellow, QColor( 250, 190, 34, 255 ), QColor( 0, 130, 250, 255 ) );
	//RenderPlot( multiple_plot_data[ 4 ], multiple_plot_data[ 5 ], ui, QCPScatterStyle::ssSquare, Qt::blue, QColor( 250, 99, 130, 255 ), QColor( 0, 0, 250, 255 ) );
	RenderPlot( multiple_plot_data[ 0 ], multiple_plot_data[ 1 ], ui, QCPScatterStyle::ssPlus, Qt::green, QColor( 250, 67, 180, 255 ), QColor( 140, 40, 250, 255 ) );
}

void Plotter::RenderPlot( 
	QVector<double> x_vector, 
	QVector<double> y_vector, 
	Ui::OverwatchCompetitiveRankTrackerClass *ui,
	QCPScatterStyle::ScatterShape symbol,
	Qt::GlobalColor symbol_color,
	QColor brush_color,
	QColor pen_color )
{
	// Create and Configure plottable
	QCPGraph *graph = ui->plotWidget->addGraph();
	graph->setData( x_vector, y_vector );
	graph->setScatterStyle( QCPScatterStyle( symbol, QPen( symbol_color, 0.45 ), QBrush( brush_color  ), 4.5 ) );
	graph->setPen( QPen( pen_color, 1.25 ) );
	ConfigurePlot( ui, graph, x_vector, y_vector );
}


void Plotter::ConfigurePlot( Ui::OverwatchCompetitiveRankTrackerClass *ui, QCPGraph *graph, QVector<double> x_vector, QVector<double> y_vector )
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
	ui->plotWidget->xAxis->setRange( 0, FindMaxOfVector( x_vector ) + 5 );
	ui->plotWidget->yAxis->setRange( FindMinOfVector( y_vector ) - 50, FindMaxOfVector( y_vector ) + 50 );
}


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

Plotter* Plotter::GetObjectPointer()
{
	return this;
}