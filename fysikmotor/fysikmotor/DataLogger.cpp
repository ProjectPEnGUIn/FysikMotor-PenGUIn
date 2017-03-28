#include "DataLogger.h"
bool DataLogger::fileExists(const std::string& filename) const //checks weather file already exists or not
{
//http://stackoverflow.com/questions/4316442/stdofstream-check-if-file-exists-before-writing 12/3 2017

	struct stat buf;
	if (stat(filename.c_str(), &buf) != -1)
		return true;

	return false;
}
void DataLogger::addData(const std::string& inputDataAsString) //appends data to save
{
	if (filename == "_NOFILENAMESET_")
		std::cout << "WARNING: DATALOGGER has no filename set\n";

	data.push_back(inputDataAsString);
}
void DataLogger::saveCurrentData() //saves all lines to
{
	if (filename != "_NOFILENAMESET_")
	{
		//filename has been set

		
		if (overwritePreviousData == true) //allowed to overwrite data in that file
		{
			std::ofstream outputToFile;
			outputToFile.open(path + filename + format , std::ios::trunc);
		
			//check if the filestream is open
			if (outputToFile.is_open() != true)
			{
				std::cout << "ERROR: outputfile >" << filename << "< is not open\n";
				return;
			}
				
			//goes through string(line) by string(line) and writes data 
			for (std::string& s : data)
			{
				outputToFile << s;
			}

			outputToFile.close();
		}
		else
		{
			if (fileExists(path + filename + format) == false)
			{
				//there is no file with this name

				std::ofstream outputToFile;
				outputToFile.open(path + filename + format);

				//check if the filestream is open
				if (outputToFile.is_open() != true)
				{
					std::cout << "ERROR: outputfile >" << filename << "< is not open\n";
					return;
				}
				//goes through string(line) by string(line) and writes data 
				for (std::string& s : data)
				{
					outputToFile << s;
				}

				outputToFile.close();
			}
			else
				std::cout << "ERROR: filename >" << filename << "< already exists and is NOT allowed to be overwritten\n";

		}
	}
	else
		std::cout << "ERROR: filename in datalogger has NOT been set, did not save data\n";
}
void DataLogger::clearData() //clears all current data stored
{
	data.clear();
}
void DataLogger::setFilename(const std::string& inputFilename) //sets the name of the file to save to
{
	filename = inputFilename;
}

DataLogger::DataLogger()
	:
	filename("_NOFILENAMESET_"),
	data(),
	overwritePreviousData(false)
{
}
DataLogger::DataLogger(const std::string& fileName)
	:
	filename(filename),
	data(),
	overwritePreviousData(false)
{
}
DataLogger::DataLogger(const std::string& fileName, const bool overwritePrevDataInFile)
	:
	filename(fileName),
	data(),
	overwritePreviousData(overwritePrevDataInFile)
{


}