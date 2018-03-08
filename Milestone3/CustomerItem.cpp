#include "CustomerItem.h"
#include "Item.h"
#include <iomanip>

//constructor
CustomerItem::CustomerItem(const std::string& strName) : code(0), filled(false) { name = strName; }

bool CustomerItem::asksFor(const Item& item) const { return true; }

//returns status of fill request
bool CustomerItem::isFilled() const { return filled; }

//sets the item code for the current object to the value received and switches the status of the current object to filled
void CustomerItem::fill(const unsigned int c)
{
	code = c;
	filled = true;
}

//resets object properties
void CustomerItem::clear()
{
	code = 0;
	filled = false;
}

//getter
const std::string& CustomerItem::getName() const { return name; }

//display
void CustomerItem::display(std::ostream& os) const
{
	//formatting
	if (!name.empty()) {
		os << " " << (filled ? '+' : '-') << " "
			<< "[" << std::right << std::setw(CODE_WIDTH) << std::setfill('0') << code << std::setfill(' ') << "] "
			<< name << std::endl;
	}
}