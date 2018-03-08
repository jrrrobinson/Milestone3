#include <algorithm>
#include "TaskManager.h"
#include "Task.h"
#include "ItemManager.h"
#include "Item.h"

// validates each task against all of the other tasks in the base class container.
// This function inserts a message into os if not all tasks have been validated.
void TaskManager::validate(std::ostream& os)
{
	// inheritated from vector //	
	size_t num = this->size();  
		
	// flag
	bool valid = true;

	// loop
	for (auto i = 0u; i < num && valid; i++) {
		valid = false;
		for (auto j = 0u; j < num && valid; j++) {
			if (this->at(i).validate(this->at(j))) {
				valid = true;
			}
		}
	}

	if (!valid) {
		std::cerr << "***Not all Tasks have been validated***\n";
	}
}

//checks that the tasks assigned to handle each item managed by itemManager are tasks in the base class container.
//If a task is not in the container, then this function inserts a message into os that that task is not available.
//Hint : use std::find_if() with a lambda expression
void TaskManager::validate(const ItemManager& iManager, std::ostream& os)
{
	// use iterators
	std::vector<Item>::const_iterator iter = iManager.cbegin();
	for (; iter != iManager.cend(); ++iter) {

		// lambda functions
		auto lambdaValidate1 = [&](const Task& task) {
			return !task.getName().compare(iter->getRemover());
		};
		auto lambdaValidate2 = [&](const Task& task) {
			return !task.getName().compare(iter->getFiller());
		};

		// validate 
		if (std::find_if(this->cbegin(), this->cend(), lambdaValidate1) == this->cend()) {
			os << iter->getRemover() << " is unavailable\n";
		}

		if (std::find_if(this->cbegin(), this->cend(), lambdaValidate1) == this->cend()) {
			os << iter->getFiller() << " is unavailable\n";
		}
	}
}

// inserts into the referenced ostream object descriptions of the tasks stored in tasks
void TaskManager::display(std::ostream& os) const
{
	std::vector<Task>::const_iterator iter = this->cbegin();
	for (; iter != this->cend(); ++iter) {
		iter->display(os);
	}
}