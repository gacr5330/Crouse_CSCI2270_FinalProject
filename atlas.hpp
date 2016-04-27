#ifndef ATLAS_HPP
#define ATLAS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <utility>
#include <cstdlib>
#include <ctime>

#include "item.hpp"
#include "weapon.hpp"
#include "armour.hpp"
#include "inventory.hpp"
#include "creature.hpp"
#include "dialogue.hpp"
#include "area.hpp"
#include "battle.hpp"
void buildatlas_creature(std::vector<Monster>& atlas)
{
	// Fill the atlas
	// Creature(Name, Health, Str, End, Dex, Hit Rate, Level)
	atlas.push_back(Monster("Rat", 20, 8, 8, 12, 2.0, 1));

	return;
}

void buildatlas_item(std::vector<Items>& atlas)
{
	// Item(Name, Description)
	atlas.push_back(Items("Gold Coin", "A small disc made of lustrous metal"));
	atlas.push_back(Items("Iron Key", "A heavy iron key with a simple cut"));

	return;
}

void buildatlas_weapon(std::vector<Weapons>& atlas)
{
	// Weapon(Name, Description, Damage, Hit Rate)
	atlas.push_back(Weapons("Iron Dagger", "A short blade made of iron with a leather-bound hilt", 5, 10.0));
	atlas.push_back(Weapons("Excalibur", "The legendary blade, bestowed upon you by the Lady of the Lake", 35, 35.0));

	return;
}

void buildatlas_armour(std::vector<Armour>& atlas)
{
	// Armour(Name, Description, Defense, Slot)
	atlas.push_back(Armour("Leather Cuirass", "Torso armour made of tanned hide", 4, Armour::ArmourSlot::TORSO));

	return;
}

void buildatlas_area(std::vector<Area>& atlas,
	std::vector<Items>& items, std::vector<Weapons>& weapons,
	std::vector<Armour>& armour, std::vector<Monster>& creatures)
{
	// Area definitions are somewhat more complicated:
	atlas.push_back(Area(Conversations(			// Standard dialogue definiton
		"You are at the Guild Hall!",				// Description
		{"Character Menu","Go to the Dungeon", "Search Area"}),		// Choices
		Inventory(							// Area inventory
		{
			std::make_pair(&items[0], 5)	// Pair of item and quantity

		},
		{
			std::make_pair(&weapons[0], 1)	// Pair of weapon and quantity
		},
		{
			std::make_pair(&armour[0], 1)	// Pair of armour and quantity
		}),
		{									// Creatures
		}));

	atlas.push_back(Area(Conversations(
		"You are in the Dungeon!",
		{"Character Menu","Go to room 1", "Search"}),
		Inventory(
		{
			std::make_pair(&items[0], 10),
			std::make_pair(&items[1], 1)
		},
		{
		},
		{
		}),
		{
			&creatures[0]
		}));

	return;
}
#endif /* WEAPON_HPP */
