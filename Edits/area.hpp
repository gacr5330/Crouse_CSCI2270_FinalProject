#ifndef AREA_HPP
#define AREA_HPP

#include "inventory.hpp"
#include "creature.hpp"
#include "dialogue.hpp"

#include <vector>

// Movement is achieved through the use of areas, which are contained
// units of space consisting of an inventory, a list of creatures and
// a dialogue
class Area
{
	public:

	// Dialogue is run whenever the area is entered
	Conversations dialogue;

	// Items contained within the area. Not split into individual containers
	// for simplicity
	Inventory items;

	// Creatures contained within the area. Currently this is limited
	// to just one creature due to how the battle system works, but it
	// made sense to set it up as a vector from the start to simplify
	// things later
	std::vector<Monster*> creatures;

	Area(Conversations dialogue, Inventory items,
		std::vector<Monster*> creatures)
	{
		this->dialogue = dialogue;
		this->items = items;
		this->creatures = creatures;
	}

	Area()
	{
	}

	// Search the area for items and give them to the searcher, notifying
	// them of their rewards
	void search(Monster& player)
	{
		std::cout << "You find:" << std::endl;

		this->items.print();
		player.inventory.merge(&(this->items));
		this->items.clear();

		return;
	}
};

#endif /* AREA_HPP */
