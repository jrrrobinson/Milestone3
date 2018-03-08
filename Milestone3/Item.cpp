#include "Item.h"
#include "Utilities.h"
#include <iomanip>

size_t Item::field_width = 0;

//constructor
Item::Item(const std::string& strRecord) :code(1), description{ "no detailed description" }
{
	//initialize variables
	Utilities u;
	u.setFieldWidth(field_width);
	size_t pos = 0;
	bool more = true;

	name = u.nextToken(strRecord, pos, more);
	if (!name.empty()) {
		if (more) filler = u.nextToken(strRecord, pos, more);
		if (more) remover = u.nextToken(strRecord, pos, more);
		if (more) code = std::stoi(u.nextToken(strRecord, pos, more));
		if (more) description = u.nextToken(strRecord, pos, more);
	}

	if (description.empty()) description = "no detailed description";
	if (name.size() > field_width) field_width = name.size();
}

//returns true if the current object is in a safe empty state
bool Item::empty() const { return name.empty(); }

//increments the code to be printed on the next insertion and returns the value before incrementation
Item& Item::operator++(int)
{
	code++;
	return *this;
}

//GETTERS
const std::string& Item::getName() const { return name; }
const std::string& Item::getFiller() const { return filler; }
const std::string& Item::getRemover() const { return remover; }
unsigned int Item::getCode() const { return code; }


void Item::display(std::ostream& os, bool full) const
{
	os << std::left << std::setw(field_width) << name
		<< " [" << std::right << std::setw(CODE_WIDTH) << std::setfill('0') << code << "]"
		<< std::left << std::setfill(' ');

	if (full) {
		os << " From " << std::setw(field_width) << filler;
		os << " To " << std::setw(field_width) << remover << std::endl;
		os << std::right << std::setw(field_width + CODE_WIDTH + 4) << " : " << description;
	}

	os << std::left << std::endl;
}
