#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "item.hpp"

#include <string>

// Weapons are also items
class Weapons : public Items
{
	public:

	// Weapon damage.
    unsigned dmg;

	// Modifier to hit chance
	double hRate;

	// Pass inherited qualities to constructor
	Weapons(std::string name, std::string description, int dmg, double hRate) :
		Items(name, description)
	{
		this->dmg = dmg;
		this->hRate = hRate;
	}

	Weapons()
	{
	}
};

#endif /* WEAPON_HPP */
