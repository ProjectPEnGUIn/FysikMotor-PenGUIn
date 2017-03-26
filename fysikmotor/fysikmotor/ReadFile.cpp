#include "ReadFile.h"

bool ReadFile::fileExists(const std::string& filename)  
{
	//http://stackoverflow.com/questions/4316442/stdofstream-check-if-file-exists-before-writing 12/3 2017

	struct stat buf;
	if (stat(filename.c_str(), &buf) != -1)
		return true;

	return false;
}

float ReadFile::getFloat(const std::string& inputKeyword) //returns anything after " : " and turns it into a float
{
	for (const std::string& s : data)
	{
		if (s.find(inputKeyword) != std::string::npos)
		{
			std::string line = s;

			line = line.substr(line.find(":") + 1, line.length());

		//	std::cout << line << std::endl;
		//	std::cin.get();

			return std::stof(line);
		}
	}

	return FLT_MAX;
}
bool ReadFile::getBool(const std::string& inputKeyword) //returns anything after " : " and turns it into a bool
{
	for (const std::string& s : data)
	{
		if (s.find(inputKeyword) != std::string::npos)
		{
			std::string line = s;

			line = line.substr(line.find(":") + 1, line.length());

			return std::stoi(line);
		}
	}

	return false;
}
std::string ReadFile::getString(const std::string& inputKeyword) //returns anything after " : " and turns it into a string
{
	for (const std::string& s : data)
	{
		if (s.find(inputKeyword) != std::string::npos)
		{
			std::string line = s;

			line = line.substr(line.find(":") + 1, line.length());

			return line;
		}
	}

	return std::string("");
}
void ReadFile::setFilename(const std::string& inputFilename) 
{
	filename = inputFilename;
}
void ReadFile::loadData()
{
	if (filename != "_NOFILENAMESET_" && fileExists(filename))
	{
		std::ifstream inputFromFile;
		inputFromFile.open(filename);

		if (inputFromFile.is_open())
		{
			std::string temp;
			while (std::getline(inputFromFile, temp))
			{
				temp.erase(std::remove(temp.begin(), temp.end(), ' '), temp.end()); //removes all spaces from the string, removes some user error

				//make all characters to lowercase http://stackoverflow.com/questions/313970/how-to-convert-stdstring-to-lower-caseb 25/3 2017
				std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

				data.push_back(temp);
			}

			inputFromFile.close();
		}
		else
			std::cout << "ERROR: something went wrong and readfile could not open the file, >" << filename << "<\n";
		
	}
	else
		std::cout << "ERROR: ReadFile tried to load data from a file that does NOT exists, >" << filename << "<\n";
}
void ReadFile::loadData(const std::string& inputFilename) 
{
	filename = inputFilename;
	loadData();
}
std::vector<std::string> ReadFile::getAllData() const
{
	return data;
}
ReadFile::ReadFile()
	:
	filename("_NOFILENAMESET_"),
	data()
{
}
ReadFile::ReadFile(const std::string& inputFilename) 
	:
	filename(inputFilename),
	data()
{
	loadData();
}
