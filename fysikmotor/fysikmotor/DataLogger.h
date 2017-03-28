//simple class to log data during runtime and then save it in a file
//Save data over some time and then save it all in one sweep for performance

//Erik Magnusson 11/3

#pragma once

#ifndef  _DATALOGGER_
#define _DATALOGGER_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sys/stat.h> //used to check if file already exists or not

class DataLogger
{
private:
	//functions

	//http://stackoverflow.com/questions/4316442/stdofstream-check-if-file-exists-before-writing 12/3 2017
	bool fileExists(const std::string& filename) const; //checks weather file already exists or not

public:
	//functions

	void addData(const std::string& inputDataAsString); //appends data to save
	void saveCurrentData(); //saves all lines to
	void clearData(); //clears all current data stored
	void setFilename(const std::string& inputFilename); //sets the name of the file to save to

	//constructors
	DataLogger();
	DataLogger(const std::string& fileName);
	DataLogger(const std::string& fileName, const bool overwritePrevDataInFile);

private:
	//members
	std::string path = "LoggedData/"; //default path to saves
	std::string format = ".txt"; //format of the file

	std::string filename; //name of file to save to
	std::vector<std::string> data; //all lines of data

	bool overwritePreviousData; //if file with the same name already exists, wheater to overwrite that data or not

};

#endif // ! _DATALOGGER_