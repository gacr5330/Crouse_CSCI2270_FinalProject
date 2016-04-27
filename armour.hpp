
#ifndef ARMOUR_HPP
#define ARMOUR_HPP

#include "item.hpp"

#include <string>

using namespace std;
// Armour should also inherit item
class Armour : public Items
{
	public:

	enum ArmourSlot { TORSO, HEAD, LEGS, D };

	ArmourSlot slot;

	int def;

	// constructor
	Armour(string name, string description, int def, Armour::ArmourSlot slot) :
		Items(name, description)
	{
		this->def = def;
		this->slot = slot;
	}

	Armour()
	{
	}
};

#endif /* ARMOUR_HPP */
