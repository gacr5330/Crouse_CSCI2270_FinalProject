#ifndef CREATURE_HPP
#define CREATURE_HPP

#include "inventory.hpp"
#include "weapon.hpp"
#include "armour.hpp"

#include <string>
using namespace std;

class Monster
{
	public:

    string characterName;
	string className;

	// Monster statistics. Reasonable values are in parentheses
	int health;		// Current hit points (10-1000+
	int maxHealth;	// Maximum hit points (10-1000+)
	int str;		// Strength. Determines damage in battle (1-100)
	int end;		// Endurance. Determines maximum health (1-100)
	int dex;        // Dexterity. Determines speed in battle (1-100)
	int mana;       //determines concentration and ability to perform magic
	int maxMana;
	double hitRate;	// Modifier to hit chance. (1-150)

	// Current level of the creature.
	unsigned int level;

	// Current experience. 0-1M is reasonable, see the levelup() function
	// for a decent scale
	unsigned int exp;

	// Items that the creature possesses
	Inventory inventory;

	// Currently equipped weapon.
	Weapons* equippedWeapon;

	// Armour currently equipped into each slot
	Armour* equippedArmour[Armour::ArmourSlot::D];

	Monster(std::string name, int health, int str, int end, int dex, int mana, double hitRate,
		unsigned int level = 1, std::string className = "")
	{
		this->characterName = name;
		this->health = health;
		this->maxHealth = health;
		this->str = str;
		this->end = end;
		this->dex = dex;
		this->mana = mana;
		this->maxMana = mana;
		this->hitRate = hitRate;
		this->className = className;
		this->equippedArmour[Armour::ArmourSlot::HEAD] = nullptr;
		this->equippedArmour[Armour::ArmourSlot::TORSO] = nullptr;
		this->equippedArmour[Armour::ArmourSlot::LEGS] = nullptr;
		this->equippedWeapon = nullptr;
		this->level = level;
		this->exp = 0;


	}

	Monster()
	{
		this->equippedArmour[Armour::ArmourSlot::HEAD] = nullptr;
		this->equippedArmour[Armour::ArmourSlot::TORSO] = nullptr;
		this->equippedArmour[Armour::ArmourSlot::LEGS] = nullptr;
		this->equippedWeapon = nullptr;
		this->level = 1;
		this->exp = 0;
	}

	// Equip a weapon
	void equipWeapon(Weapons* weapon)
	{
		this->equippedWeapon = weapon;

		return;
	}

	// Equip the armour into it's correct slot. A slightly more useful
	// function!
	void equipArmour(Armour* armour)
	{
		this->equippedArmour[(int)armour->slot] = armour;

		return;
	}

	// Calculates the experience required to reach a certain level,
	// *in total*.
	unsigned int expToLevel(unsigned int level)
	{
		// Exp to level x = 128*x^2
		return 128 * level * level;
	}

	// Level the creature to the next level if it has enough experience
	bool levelUp()
	{
		// We want the experience to the next level, not the current level
		if(this->exp >= expToLevel(this->level+1))
		{
			// Advance to the next level
			++level;

			unsigned int healthBoost = 0;
			unsigned int strBoost = 0;
			unsigned int endBoost = 0;
			unsigned int dexBoost = 0;
			unsigned int manaBoost = 0;

			// Give a large boost to health every third level
			if(level % 3 == 0)
			{
				// Randomly increase health, but always give a sizeable
				// chunk proportional to the creature's endurance
				healthBoost = 10 + (rand() % 4) + this->end / 4;
			}
			else
			{
				// Just increase health by a small amount
				healthBoost = this->end / 4;
			}

			if(this->className == "Fighter")
			{
				strBoost = 1;
				endBoost = 1;
				if(rand() % 2 == 0) dexBoost = 1;
			}
			// Same as for fighter but favour dexterity and endurance
			// instead. Rogue's favour endurance too in order to keep
			// them at roughly the same capability
			else if(this->className == "Rogue")
			{
				endBoost = 1;
				dexBoost = 1;
				if(rand() % 2 == 0) strBoost = 1;
			}
			//ditto but favour mana and dexterity
			else if(this->className == "Mage")
            {
                dexBoost = 1;
                manaBoost = 1;
                if(rand() % 2 == 0) manaBoost = 1;
            }

			// Adjust all of the variables accordingly
			this->maxHealth += healthBoost;
			this->maxMana += manaBoost;
			this->str += strBoost;
			this->end += endBoost;
			this->dex += dexBoost;

			//balancing, reset current mana and health every level
			this->health = maxHealth;
			this->mana = maxMana;

			// Tell the user that they grew a level, what the boosts where
			// and what their stats are now
			std::cout << this->characterName << " grew to level " << level << "!\n";
			std::cout << "Health +" << healthBoost << " -> " << this->maxHealth << std::endl;
			std::cout << "Mana +" << manaBoost << " -> " << this->maxMana << std::endl;
			std::cout << "Str +" << strBoost << " -> " << this->str << std::endl;
			std::cout << "End +" << endBoost << " -> " << this->end << std::endl;
			std::cout << "Dex +" << dexBoost << " -> " << this->dex<< std::endl;
			std::cout << "----------------\n";

			return true;
		}
		return false;
	}
};

#endif /* CREATURE_HPP */
