#include "CustomerOrder.h"
#include "Utilities.h"
#include "CustomerItem.h"
#include "Item.h"
#include <iomanip>
#include <vector>

//initialize field width
size_t CustomerOrder::field_width = 0;

//constructor
CustomerOrder::CustomerOrder(const std::string& strRecord) : nOrders(0), order(nullptr)
{
	//initialize variables
	Utilities u;
	u.setFieldWidth(field_width);
	size_t pos = 0;
	bool more = true;
	std::vector<std::string> tokens;

	name = u.nextToken(strRecord, pos, more);

	if (!name.empty()) {
		if (more) {
			product = u.nextToken(strRecord, pos, more);
		}

		//extract remaining tokens 
		while (more) tokens.push_back(u.nextToken(strRecord, pos, more));

		//create ItemOrders for each remaining token 
		nOrders = tokens.size();
		order = new CustomerItem[nOrders];
		for (std::vector<int>::size_type i = 0; i < nOrders; i++) {
			order[i] = CustomerItem(tokens[i]);
		}

		//update fieldwidth
		field_width = u.getFieldWidth();
	}
}


//move constructor
CustomerOrder::CustomerOrder(CustomerOrder&& cus) : nOrders(0), order(nullptr)
{
	*this = std::move(cus);
}

//move assignment operator
CustomerOrder&& CustomerOrder::operator=(CustomerOrder&& cus)
{
	//self assignment
	if (this != &cus) {
		//manage memory properly
		if (order) {
			delete[] order;
		}

		name = cus.name;
		product = cus.product;
		nOrders = cus.nOrders;
		order = cus.order;

		cus.name.clear();
		cus.product.clear();
		cus.nOrders = 0;
		cus.order = nullptr;
	}
	return std::move(*this);
}

//destructor
CustomerOrder::~CustomerOrder()
{
	if (order) {
		delete[] order;
		order = nullptr;
	}
}

//returns true if the current object is in a safe empty state
bool CustomerOrder::empty() const { return name.empty(); }

//returns number of CustomerItems in current object
unsigned int CustomerOrder::noOrders() const { return nOrders; }

//returns a reference to the name of customer item i; reports an exception if the index is out of bounds
const std::string& CustomerOrder::operator[](unsigned int i) const {
	if (i >= nOrders) {
		std::string errmsg = "The index is out of bounds!";
		throw errmsg;
	}
	return order[i].getName();
}

//searches through the customer items and fills those order for the customer items identified by item if any have not been filled.
//increments item code for each customer item filled, which keeps the item code unique for each order.
void CustomerOrder::fill(Item& item) {
	for (unsigned int i = 0; i<nOrders; i++) {
		if (order[i].getName() == item.getName()) {
			order[i].fill(item.getCode());
			item++;
		}
	}
}

//searches through the customer items and removes those items identified by the name of item if the corresponding part of the order has been filled. 
//does not alter the item's code.
void CustomerOrder::remove(Item& item) {
	for (unsigned int i = 0; i < nOrders; i++) {
		if (order[i].getName() == item.getName()) {
			order[i].clear();
		}
	}
}

//inserts description into os as follows:
//the name of the customer left-justified in a field of width field_width
//the name of the product left-justified in a field of width field_width
//each customer item on a separate line
void CustomerOrder::display(std::ostream& os) const {
	os << std::left << std::setw(field_width) << name << " : " << std::setw(field_width) << product << std::endl;
	for (unsigned int i = 0; i < nOrders; i++) {
		order[i].display(os);
	}
}