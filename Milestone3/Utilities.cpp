#include "Utilities.h"

std::ofstream Utilities::logFile;

// field delimiter character '|'
char Utilities::delimiter = '|';

//default contructor
Utilities::Utilities() { field_width = 1; }

//custom 'trim' function
std::string& Utilities::trim(std::string& s, const char* t)
{
	s.erase(0, s.find_first_not_of(t));
	s.erase(s.find_last_not_of(t) + 1);
	return s;
}

//returns the next token found and sets more to true if the record contains more tokens after the extracted token; false otherwise.  
//This function updates the current object's field_width data member if its current value is less than the size of the token 
//extracted.  This function reports an exception if there are two delimiters with no token between them.
const std::string Utilities::nextToken(const std::string& str, size_t& next_pos, bool& more)
{

	//declare token
	std::string token;

	//assign str to record
	std::string rec = str;

	// For malformed records //
	size_t del_pos = 0;

	while ((del_pos = rec.find("/")) != std::string::npos) {
		rec.replace(del_pos, 1, "|");
		token = trim(token);
	}


	for (int i = 0; (rec.size() > next_pos) && (rec[next_pos] != delimiter); ++next_pos) {
		token += rec[next_pos];
	}

	// trim //
	token = trim(token);

	if (field_width < token.size()) { field_width = token.size(); }

	if (next_pos < rec.size()) {
		more = true;
		++next_pos;
	}

	else {
		more = false;
	}

	return token;
}

void Utilities::setDelimiter(const char del) { delimiter = del; }

void Utilities::setLogFile(const char* logfile)
{
	logFile.open(logfile, std::ofstream::out | std::ofstream::app);
}

std::ofstream& Utilities::getLogFile() { return logFile; }