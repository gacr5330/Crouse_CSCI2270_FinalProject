
#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

using namespace std;

class Items
{
	public:

	//of items
	string itemName;
	string description;

	Items(string itemName, string description)
	{
		this->itemName = itemName;
		this->description = description;
	}

	Items()
	{
	}
};

#endif /* ITEM_HPP */
