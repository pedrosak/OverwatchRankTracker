#include "DataBreakdown.h"

DataBreakdown::DataBreakdown()
{
	// Constructor
	//FileReader fileReader;
	//data_from_fileReader_ = fileReader.GetDataVector();
	//PreparePlotData();
	//GenerateGroupInfoPlot();
	//CalculateFitLine();
}

void DataBreakdown::StartBreakingDownData()
{
	FileReader fileReader;
	fileReader.StartReadingFile();
	data_from_fileReader_ = fileReader.GetDataVector();
	PreparePlotData();
	GenerateGroupInfoPlot();
	CalculateFitLine();
}


void DataBreakdown::GenerateGroupInfoPlot()
{
	// Create graph data for three case
	//		1: Solo Games ( - )
	//		2: Dual Game ( + )
	//		3: Three or more Games ( * )
	//		4: Lost of SR due to leaving ( ^ )
	int solo_index = 0;
	int duo_index = 0;
	int group_index = 0;
	int sr_loss_index = 0;

	int number_of_solo_queues = CountElementsInVector( "-" );
	int number_of_duo_queues = CountElementsInVector( "+" );
	int number_of_group_queues = CountElementsInVector( "*" );
	int number_of_sr_losses = CountElementsInVector( "^" );

	ResizeAllXYvalues( number_of_solo_queues, number_of_duo_queues, number_of_group_queues, number_of_sr_losses );

	for( auto const &iter_count : data_from_fileReader_ )
	{
		QString current_group_symbol = std::get<1>( iter_count ).group_symbol;

		if( current_group_symbol == "-" )
		{
			solo_queue_x_value_[ solo_index ] = std::get<0>( iter_count ); // This is a test to see if this graph will overlway on top of original graph
			solo_queue_y_value_[ solo_index ] = std::get<1>( iter_count ).rank;
			solo_index += 1;
		}
		else if( current_group_symbol == "+" )
		{
			duo_queue_x_value_[ duo_index ] = std::get<0>( iter_count ); // This is a test to see if this graph will overlway on top of original graph
			duo_queue_y_value_[ duo_index ] = std::get<1>( iter_count ).rank;
			duo_index += 1;
		}
		else if( current_group_symbol == "*" )
		{
			group_queue_x_value_[ group_index ] = std::get<0>( iter_count ); // This is a test to see if this graph will overlway on top of original graph
			group_queue_y_value_[ group_index ] = std::get<1>( iter_count ).rank;
			group_index += 1;
		}
		else if( current_group_symbol == "^" )
		{
			loss_sr_x_value_[ sr_loss_index ] = std::get<0>( iter_count );
			loss_sr_y_value_[ sr_loss_index ] = std::get<1>( iter_count ).rank;
			sr_loss_index += 1;
		}
		else
		{
			qDebug() << "Group symbol is invalid. Check the .txt file.";
			throw;
		}
	}

}

void DataBreakdown::SeparateByDate()
{
}

void DataBreakdown::CalculateFitLine()
{
	int size_of_x = x_.size();
	double x_y_mult_sum = 0;
	double x_squared_sum = 0;
	double average_of_x = CalculateAverage( x_ );
	double average_of_y = CalculateAverage( y_ );
	double temp_x_diff = 0;
	double temp_y_diff = 0;
	double slope = 0;
	double y_itercept = 0;

	for( int iterate_i = 0; iterate_i < size_of_x; iterate_i++ )
	{
		temp_x_diff += x_.at( iterate_i ) - average_of_x;
		temp_y_diff += y_.at( iterate_i ) - average_of_y;
		x_y_mult_sum += temp_x_diff * temp_y_diff;
		x_squared_sum += pow(temp_x_diff, 2);
	}

	slope = x_y_mult_sum / x_squared_sum;
	y_itercept = average_of_y - ( slope * average_of_x );

	fit_line_x_value_.resize( size_of_x );
	fit_line_y_value_.resize( size_of_x );
	for( int count_to_populate = 0; count_to_populate < size_of_x; count_to_populate++ )
	{
		fit_line_y_value_[count_to_populate] = slope * x_.at( count_to_populate ) + y_itercept;
		fit_line_x_value_[count_to_populate]= x_.at( count_to_populate );
	}
}

void DataBreakdown::PreparePlotData()
{
	x_.resize( std::get<0>( data_from_fileReader_.back() ) );
	y_.resize( std::get<0>( data_from_fileReader_.back() ) );

	// Populate the vector with data
	// Both x and y must be the same size
	for( int count_i = 0; count_i < x_.size(); ++count_i )
	{
		x_[ count_i ] = std::get<0>( data_from_fileReader_.at( count_i ) );
		y_[ count_i ] = std::get<1>( data_from_fileReader_.at( count_i ) ).rank;
	}
}

void DataBreakdown::ResizeAllXYvalues( int solo_queue_ize, int duo_queue_size, int group_queue_size, int number_of_sr_losses )
{
	solo_queue_x_value_.resize( solo_queue_ize );
	solo_queue_y_value_.resize( solo_queue_ize );
	duo_queue_x_value_.resize( duo_queue_size );
	duo_queue_y_value_.resize( duo_queue_size );
	group_queue_x_value_.resize( group_queue_size );
	group_queue_y_value_.resize( group_queue_size );
	loss_sr_x_value_.resize( number_of_sr_losses );
	loss_sr_y_value_.resize( number_of_sr_losses );
}

int DataBreakdown::CountElementsInVector( QString element )
{
	int number_of_elements = 0;
	for( auto const &iter_count : data_from_fileReader_ )
	{
		if( std::get<1>( iter_count ).group_symbol == element )
		{
			number_of_elements += 1;
		}
	}
	return number_of_elements;
}

int DataBreakdown::CalculateAverage( QVector<double> value )
{
	int sum_temp = 0;
	for( int count_the_value = 0; count_the_value < value.size(); count_the_value++ )
	{
		sum_temp = sum_temp + value.at( count_the_value );
	}
	return sum_temp/value.size();
}

QVector<QVector<double>> DataBreakdown::GetFullPlotData()
{
	QVector<QVector<double>> full_plot_data_vector;

	full_plot_data_vector.push_back( x_ );
	full_plot_data_vector.push_back( y_ );
	full_plot_data_vector.push_back( solo_queue_x_value_ );
	full_plot_data_vector.push_back( solo_queue_y_value_ );
	full_plot_data_vector.push_back( duo_queue_x_value_ );
	full_plot_data_vector.push_back( duo_queue_y_value_ );
	full_plot_data_vector.push_back( group_queue_x_value_ );
	full_plot_data_vector.push_back( group_queue_y_value_ );
	full_plot_data_vector.push_back( fit_line_x_value_ );
	full_plot_data_vector.push_back( fit_line_y_value_ );
	full_plot_data_vector.push_back( loss_sr_x_value_ );
	full_plot_data_vector.push_back( loss_sr_y_value_ );

	return full_plot_data_vector;
}