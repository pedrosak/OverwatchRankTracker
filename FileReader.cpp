#include "FileReader.h"

FileReader::FileReader()
{
	// Constructor
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

std::vector<FileDataTuple>* FileReader::ParseFile(QString file_name)
{	
	QFile file( file_name );

	if( !file.open( QIODevice::ReadOnly ) )
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

	return &data_vector_;
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

std::vector<FileDataTuple>* FileReader::GetDataVector() 
{ 
	return &data_vector_; 
}
