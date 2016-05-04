
#ifndef BATTLE_HPP
#define BATTLE_HPP

#include "dialogue.hpp"
#include "creature.hpp"
#include "armour.hpp"
#include "weapon.hpp"

#include <iostream>

class Battle
{
	public:

	// Dialogue used to ask the player battle choices
	Conversations dialogue;

	// Creatures in combat. creatures[0] is the player
	Monster* creatures[2];

	Battle()
	{
	}

	Battle(Monster* player, Monster* b)
	{
		// Start a battle with the player and another creature
		this->creatures[0] = player;
		this->creatures[1] = b;

		// Set up the dialogue. Defending offers no tactical advangtages
		// in this battle system
		this->dialogue = Conversations("What will you do?",
		{
			"Attack",
			"Defend"
		});
	}

	// Creature a attacks creature b, and b takes damage accordingly
	void attack(Monster* a, Monster* b)
	{
		std::cout << a->characterName << " attacks!\n";

		// Damage that a will inflict on b
		int damage = 0;

		// Cumulative modifier to hitRate
		double hitRate = a->hitRate;

		// If a has equipped a weapon, then add the weapon damage on
		// to the current damage and add the hit rate of the weapon on to
		// the current hit rate
		//add mage exception
		if (a->mana == 0 || a->className != "Mage")
        {
            if(a->equippedWeapon != nullptr)
            {
                damage += a->equippedWeapon->dmg;
                hitRate += a->equippedWeapon->hRate;
            }

            // Increase the damage by half the attacker's strength
            damage += a->str / 2;

            // Damage that b will block
            int defense = 0;

            // Sum the defense values of the armour that b has equipped, and
            // increase the defense by the summed value
            for(int i = 0; i < Armour::ArmourSlot::D; ++i)
            {
                if(b->equippedArmour[i] != nullptr)
				defense += b->equippedArmour[i]->def;
            }

            // Decrease the damage by the damage blocked, then ensure that
            // damage is always inflicted
            damage -= defense;
            if(damage < 1) damage = 1;

            // hit rate values
            if(rand() % 201 <= 170 + hitRate - b->dex)
            {
                // The attack hit, so subtract the damage
                std::cout << b->characterName << " takes " << damage << " damage!\n";
                b->health -= damage;
            }
            else
            {
                // The attack missed
                std::cout << a->characterName << " missed!\n";
            }
        }
        else
        {
            damage = (a->maxMana+a->level)/2;
            hitRate = a->hitRate*a->mana/a->maxMana;

            // Damage that b will block
            int defense = 0;

            // Sum the defense values of the armour that b has equipped, and
            // increase the defense by the summed value
            for(int i = 0; i < Armour::ArmourSlot::D; ++i)
            {
                if(b->equippedArmour[i] != nullptr)
				defense += b->equippedArmour[i]->def;
            }

            // Decrease the damage by the damage blocked, then ensure that
            // damage is always inflicted
            damage -= defense;
            if(damage < 1) damage = 1;

            // hit rate values
            if(rand() % 201 <= 170 + hitRate - b->dex)
            {
                // The attack hit, so subtract the damage
                std::cout << b->characterName << " takes " << damage << " damage!\n";
                b->health -= damage;
            }
            else
            {
                // The attack missed
                std::cout << a->characterName << " missed!\n";
            }
            a->mana -= 5;
            if (a->mana < 0)
            {
                a->mana = 0;
                std::cout << "Mana Depleted" << std::endl;
            }
        }

		return;
	}

	//defense (only for mages)
	void defend(Monster* a)
	{
	    if (a->className == "Mage")
        {
            a->mana += 5;
            if (a->mana >= a->maxMana)
            {
                a->mana = a->maxMana;
                std::cout << "Mana Fully Recharged" << std::endl;
            }
        }
	}

	// Allow the player to act
	void playerTurn()
	{
		// Activate the dialogue and allow the player to choose their
		// battle option
		int result = this->dialogue.startConversation();

		switch(result)
		{
			// Attack the enemy
			case 1:
				attack(creatures[0], creatures[1]);
				break;
			// Defend, skipping to the enemy's turn
			case 2:
			    defend(creatures[0]);
				std::cout << creatures[0]->characterName << " defends!\n";
				break;
			default:
				break;
		}

		return;
	}

	// Allow the enemy to attack
	void enemyTurn()
	{
		// Battle system does not currently allow for any kind of
		// tactics, so make the enemy attack blindly
		attack(creatures[1], creatures[0]);

		return;
	}

	// Return true if the creature is dead.
	bool isdead(Monster* creature)
	{
		if(creature->health <= 0)
		{
			return true;
		}
		return false;
	}

	// Run a round of the battle
	bool activate()
	{
		// The creature with the highest dexterity attacks first, with
		// preference to the player
		if(creatures[0]->dex >= creatures[1]->dex)
		{
			// Run each turn and check if the foe is dead at the end of
			// each
			this->playerTurn();
			if(isdead(creatures[1]))
			{
				std::cout << creatures[1]->characterName << " was vanquished!\n";
				return true;
			}

			this->enemyTurn();
			if(isdead(creatures[0]))
			{
				std::cout << creatures[0]->characterName << " was vanquished!\n";
				return true;
			}
		}
		else
		{
			this->enemyTurn();
			if(isdead(creatures[0]))
			{
				std::cout << creatures[0]->characterName << " was vanquished!\n";
				return true;
			}

			this->playerTurn();
			if(isdead(creatures[1]))
			{
				std::cout << creatures[1]->characterName << " was vanquished!\n";
				return true;
			}
		}

		return false;
	}

	// Begin the battle
	void run()
	{
		std::cout << creatures[1]->characterName << " appears!" << std::endl;

		// Run the battle until one creature dies
		while(!this->activate());

		// If the enemy is dead, then allocate experience to the player
		if(isdead(creatures[1]))
		{
			// Give experience to the player equal to one eighth of the
			// experience the enemy gained to reach it's next level
			unsigned int expGain = creatures[1]->expToLevel(creatures[1]->level+1) / 8;
			std::cout << "Gained " << expGain << " exp!\n";
			creatures[0]->exp += expGain;

			while(creatures[0]->levelUp());
		}

		return;
	}
};

#endif /* BATTLE_HPP */
