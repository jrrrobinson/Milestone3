#include "ItemManager.h"
#include "Item.h"

// inserts into os descriptions of each item stored in the base class container.
// The bool parameter specifies whether a full description of the item should be inserted.
void ItemManager::display(std::ostream& os, bool isFull) const
{
	//use iterators
	std::vector<Item>::const_iterator iter = this->cbegin();
	for (; iter != this->cend(); iter++) {
		iter->display(os, isFull);
	}
}