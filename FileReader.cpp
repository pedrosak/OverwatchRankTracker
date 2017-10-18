#include "FileReader.h"

FileReader::FileReader()
{
	qDebug() << "FileReader Constructor Called!";
	// Constructor
	//file_name = ChooseFile();
	//ParseFile();
}

void FileReader::StartReadingFile()
{
	file_name_ = ChooseFile();
	ParseFile();
}

QString FileReader::ChooseFile()
{
	// Prompt user for a file
	QString file_name = QFileDialog::getOpenFileName( this, "Choose which file to upload", QDir::currentPath(), "Document Files (*.txt)" );

	// Make sure file name is valid
	if( !file_name.isNull() )
	{
		std::cout << "Invalid file. Check your file." << std::endl;
	}

	return file_name;
}

void FileReader::ParseFile()
{	

	QFile file( file_name_ );

	if( !file.open( QIODevice::ReadWrite ) )
	{
		QMessageBox::information( 0, "File is Read-Only", file.errorString() );
	}

	QTextStream in( &file );

	int index = 0;
	while (!in.atEnd())
	{
		index += 1;
		QString current_line = in.readLine();
		QStringList current_line_split = current_line.split("	");
		RankeData current_rank_data;
		
		current_rank_data.date = current_line_split.at( 0 );
		current_rank_data.rank = current_line_split.at(1).toInt();
		current_rank_data.group_symbol = current_line_split.at( 2 );

		data_vector_.push_back( FileDataTuple( index, current_rank_data ) );
	}

	file.close();
}


void FileReader::PrintVector(std::vector<FileDataTuple> data_vector)
{
	std::cout << "Printing vector elements ( Testing Only )." << std::endl;

	for (const auto& i : data_vector)
	{
		qDebug() << std::get<0>(i);
		qDebug() << std::get<1>(i).date;
		qDebug() << std::get<1>(i).rank;
		qDebug() << std::get<1>(i).group_symbol;

	}
}

std::vector<FileDataTuple> FileReader::GetDataVector() 
{ 
	//int test_size = std::get<0>( data_vector_.back() );
	//qDebug() << test_size;
	return data_vector_; 
}