#pragma once
#include <iostream>
#include <fstream>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

using int16 = __int16;

struct RankeData {
	QString date;
	int16 rank;
	QString group_symbol;
};

typedef std::tuple< int, RankeData > FileDataTuple;

class FileReader : public QWidget
{
public:
	FileReader();
	QString FileReader::ChooseFile();
	std::vector<FileDataTuple>* FileReader::ParseFile(QString file_name);

private:
	std::vector<FileDataTuple> data_vector_;

	void FileReader::PrintVector(std::vector<FileDataTuple> data_vector);
	std::vector<FileDataTuple>* FileReader::GetDataVector();

};