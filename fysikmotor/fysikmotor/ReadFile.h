//simple class to read a textfile

#pragma once
#ifndef  _READFILE_
#define _READFILE_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

class ReadFile
{
private:
	//functions
	bool fileExists(const std::string& filename);

public:
	//functions

	float getFloat(const std::string& inputKeyword); //returns anything after " : " and turns it into a float
	bool getBool(const std::string& inputKeyword); //returns anything after " : " and turns it into a bool
	std::string getString(const std::string& inputKeyword); //returns anything after " : " and turns it into a string
	void setFilename(const std::string& inputFilename);
	void loadData();
	void loadData(const std::string& inputFilename);
	std::vector<std::string> getAllData() const;
	ReadFile();
	ReadFile(const std::string& inputFilename);
	
private:
	//members
	
	std::string filename;
	std::vector<std::string> data;
};

#endif // ! _READFILE_
