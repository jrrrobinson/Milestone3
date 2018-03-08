#pragma once
// Utilities.h
// Chris Szalwinski
// v1.0 - 24/10/2015
// v2.0 - 23/02/2016
#include <string>
#include <fstream>

class Utilities {
	size_t field_width;           // maximum field width needed 
	static char delimiter;        // field delimiter character
	static std::ofstream logFile; // log file
public:
	Utilities();
	void setFieldWidth(size_t fw) { field_width = fw; }
	size_t getFieldWidth() const { return field_width; }
	const std::string nextToken(const std::string& str, size_t& next_pos, bool& more);
	static void setDelimiter(const char del);
	static void setLogFile(const char* logfile);
	static std::ofstream& getLogFile();

	// add trim function //
	std::string& trim(std::string& s, const char* t = " \t\n\r");
};