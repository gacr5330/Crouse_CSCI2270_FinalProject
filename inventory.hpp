
#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "item.hpp"
#include "weapon.hpp"
#include "armour.hpp"

#include <list>
#include <utility>
#include <iostream>

using namespace std;
class Inventory
{
	public:

	list<pair<Items*, int>> items;
	list<pair<Weapons*, int>> weapons;
	list<pair<Armour*, int>> armour;

	Inventory()
	{
	}

	Inventory(list<pair<Items*, int>> items,
		list<pair<Weapons*, int>> weapons,
		list<pair<Armour*, int>> armour)
	{
		this->items = items;
		this->weapons = weapons;
		this->armour = armour;
	}

	// Remove all items from the inventory
	void clear()
	{
		this->items.clear();
		this->weapons.clear();
		this->armour.clear();
	}

	// Add an item to the inventory
	void add_item(Items* item, int count)
	{
		// Perform the same operation as merging, but for a single item
		for(auto& it : this->items)
		{
			if(it.first == item)
			{
				it.second += count;
				return;
			}
		}
		// If the item doesn't already exist in the inventory
		this->items.push_back(std::make_pair(item, count));
	}

	// Same as for items
	void add_weapon(Weapons* weapon, int count)
	{
		for(auto& it : this->weapons)
		{
			if(it.first == weapon)
			{
				it.second += count;
				return;
			}
		}
		this->weapons.push_back(std::make_pair(weapon, count));
	}

	// Same as for items
	void add_armour(Armour* armour, int count)
	{
		for(auto& it : this->armour)
		{
			if(it.first == armour)
			{
				it.second += count;
				return;
			}
		}
		this->armour.push_back(std::make_pair(armour, count));
	}

	// Remove the specified number of items from the inventory
	void remove_item(Items* item, int count)
	{
		// Iterate through the items
		for(auto& it : this->items)
		{
			if(it.first == item) it.second -= count;
		}
		// Iterate through the list again
		this->items.remove_if([](std::pair<Items*, int>& element)
		{
			return element.second < 1;
		});
	}

	// Same as for items
	void remove_weapon(Weapons* weapon, int count)
	{
		for(auto& it : this->weapons)
		{
			if(it.first == weapon) it.second -= count;
		}
		this->weapons.remove_if([](std::pair<Weapons*, int>& element)
		{
			return element.second < 1;
		});
	}

	// Same as for items
	void remove_armour(Armour* armour, int count)
	{
		for(auto& it : this->armour)
		{
			if(it.first == armour) it.second -= count;
		}
		this->armour.remove_if([](std::pair<Armour*, int>& element)
		{
			return element.second < 1;
		});
	}

	// Merge the specified inventory with the current one
	void merge(Inventory* inventory)
	{
		
		if(inventory == this) return;

		// Loop through the items to be added, and add them
        for(auto it : inventory->items)
		{
			this->add_item(it.first, it.second);
		}
		// Do the same for the weapons
		for(auto it : inventory->weapons)
		{
			this->add_weapon(it.first, it.second);
		}
		// Do the same for the armour
		for(auto it : inventory->armour)
		{
			this->add_armour(it.first, it.second);
		}

		return;
	}

	// Output a list of the items onto stdout
	int print_items(bool label = false)
	{
		unsigned int i = 1;

		for(auto it : this->items)
		{
			// Number the items if asked
			if(label) cout << i++ << ": ";
			// Output the item name, quantity and description, e.g.
			// Gold Piece (29) - Glimmering discs of wealth
			cout << it.first->itemName << " (" << it.second << ") - ";
			cout << it.first->description << std::endl;
		}

		// Return the number of items outputted, for convenience
		return this->items.size();
	}

	// Same as for items
	int print_weapons(bool label = false)
	{
		unsigned int i = 1;

		for(auto it : this->weapons)
		{
			if(label) std::cout << i++ << ": ";
			std::cout << it.first->itemName << " (" << it.second << ") - ";
			std::cout << it.first->description << std::endl;
		}

		return this->weapons.size();
	}

	// Same as for items
	int print_armour(bool label = false)
	{
		unsigned int i = 1;

		for(auto it : this->armour)
		{
			if(label) std::cout << i++ << ": ";
			std::cout << it.first->itemName << " (" << it.second << ") - ";
			std::cout << it.first->description << std::endl;
		}

		return this->armour.size();
	}

	// Print the entire inventory; items, then weapons, then armour,
	// but if the inventory is empty then output "Nothing"
	void print(bool label = false)
	{
		if(this->items.size() == 0 &&
			this->weapons.size() == 0 &&
			this->armour.size() == 0)
		{
			std::cout << "Nothing" << std::endl;
		}
		else
		{
			this->print_items(label);
			this->print_weapons(label);
			this->print_armour(label);
		}

		return;
	}
};

#endif /* INVENTORY_HPP */
