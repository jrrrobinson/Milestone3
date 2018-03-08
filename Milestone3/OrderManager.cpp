#include "OrderManager.h"
#include "CustomerOrder.h"
#include <algorithm>
#include "ItemManager.h"
#include "Item.h"

// MOVES a customerOrder from the back of the base class container
CustomerOrder&& OrderManager::extract()
{
	return std::move(*this->end());
}

// checks that the items requested in the customer orders are available, 
// inserting a message into os for any item that is not available. 
// Hint: use std::find_if()
void OrderManager::validate(const ItemManager& iManager, std::ostream& os)
{
	// use iterators
	std::vector<CustomerOrder>::iterator iter = this->begin();

	for (; iter < this->end(); ++iter) {
		for (unsigned int i = 0; i < iter->noOrders(); ++i) {
			auto lambdaValidate = [&](const Item& item) {
				return !(item.getName() == (*iter)[i]);
			};

			if (std::find_if(iManager.cbegin(), iManager.cend(), lambdaValidate) == iManager.cend()) {
				os << (*iter)[i] << " is unavailable " << std::endl;
			}
		}
	}
}

// inserts into os descriptions of each customer order in the base class container
void OrderManager::display(std::ostream& os) const
{
	std::vector<CustomerOrder>::const_iterator iter = this->cbegin();
	for (; iter < this->cend(); ++iter) {
		iter->display(os);
	}

}