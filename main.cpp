#include <iostream>
#include <string>
#include <utility>
#include <cstdlib>
#include <vector>
#include <list>
#include <ctime>

#include "inventory.hpp"
#include "creature.hpp"
#include "item.hpp"
#include "atlas.hpp"
#include "armour.hpp"
#include "dialogue.hpp"
#include "weapon.hpp"
#include "area.hpp"
#include "battle.hpp"

using namespace std;
// menu
Monster dialogue_newchar();

Monster dialogue_menu(Monster& player);

int main(void)
{
	vector<Monster> creatureAtlas;
	vector<Items> itemAtlas;
	vector<Weapons> weaponAtlas;
	vector<Armour> armourAtlas;
	vector<Area> areaAtlas;

	Monster player;

	// Build the atlases
	buildatlas_creature(creatureAtlas);
	buildatlas_item(itemAtlas);
	buildatlas_weapon(weaponAtlas);
	buildatlas_armour(armourAtlas);
	buildatlas_area(areaAtlas, itemAtlas, weaponAtlas, armourAtlas, creatureAtlas);

    srand(time(NULL));

	// Main game menu dialogue
	int result = Conversations(
		"Welcome Adventurer!",
		{"Start a New Game"}).startConversation();

	switch(result)
	{
		case 1: player = dialogue_newchar();break;
		default: return 0; break;
	}

    Area* currentArea = &(areaAtlas[0]);

	// Play the game until a function breaks the loop and closes it
	while(1)
	{
		// If the player has died
		if(player.health <= 0)
		{
			cout << "\t----YOU DIED----\n    Game Over\n";
			return 0;
		}

		// If the area the player is in has any creatures inside it, Battle!
				if(currentArea->creatures.size() > 0)
		{
			Battle(&player, currentArea->creatures[0]).run();
			// two versions of each area)
			currentArea->creatures.pop_back();
		}

		// Activate current area's conversation
		result = currentArea->dialogue.startConversation();

		if(currentArea == &(areaAtlas[0]))
		{
			switch(result)
			{
				// Open the menu
				case 1:
					dialogue_menu(player);
					break;
				case 2:
				// Move to area 1
					currentArea = &(areaAtlas[1]);
					break;
				case 3:
				// Search the area
					currentArea->search(player);
					break;
				default:
					break;
			}
		}
		else if(currentArea == &(areaAtlas[1]))
		{
			switch(result)
			{
				// Open the menu
				case 0:
					dialogue_menu(player);
					break;
				// Move to area 0
				case 1:
					currentArea = &(areaAtlas[0]);
					break;
				// Search the area
				case 2:
					currentArea->search(player);
					break;
				default:
					break;
			}
		}
	}

	return 0;
}

// Create a new character
Monster dialogue_newchar()
{
	cout << "Choose your name" << std::endl;
	string name;
	cin >> name;

	int result = Conversations(
		"Choose your class",
		{"Fighter", "Rogue"}).startConversation();

	switch(result)
	{
		// Fighter class favours health and strength
		case 1:
			return Monster(name, 35, 20, 10, 5, 10.0, 1, "Fighter");
			break;

		// Rogue class favours dexterity and hit rate
		case 2:
			return Monster(name, 30, 5, 10, 20, 15.0, 1, "Fighter");
			break;

		// Default case that should never happen, but it's good to be safe
		default:
			return Monster(name, 30, 10, 10, 10, 10.0, 1, "Adventurer");
		break;
	}
}

Monster dialogue_menu(Monster& player)
{
	// Output the menu
	int result = Conversations(
		"Menu\n====",
		{"Items", "Equipment", "Character"}).startConversation();

	switch(result)
	{
		// Print the items that the player owns
		case 1:
			cout << "Items\n=====\n";
			player.inventory.print();
			cout << "----------------\n";
			break;
		// Print the equipment that the player is wearing and ask to equip anything from inventory
		case 2:
		{
			cout << "Equipment\n=========\n";
			cout << "Head: "
				<< (player.equippedArmour[Armour::ArmourSlot::HEAD] != nullptr ?
					player.equippedArmour[Armour::ArmourSlot::HEAD]->itemName: "Nothing")
				<< endl;
			cout << "Torso: "
				<< (player.equippedArmour[Armour::ArmourSlot::TORSO] != nullptr ?
					player.equippedArmour[Armour::ArmourSlot::TORSO]->itemName : "Nothing")
				<< endl;
			cout << "Legs: "
				<< (player.equippedArmour[Armour::ArmourSlot::LEGS] != nullptr ?
					player.equippedArmour[Armour::ArmourSlot::LEGS]->itemName : "Nothing")
				<< endl;
			cout << "Weapon: "
				<< (player.equippedWeapon != nullptr ?
					player.equippedWeapon->itemName : "Nothing")
				<< endl;

			int result2 = Conversations(
				"",
				{"Equip Armour", "Equip Weapon", "Close"}).startConversation();
			// Equipping armour
			if(result2 == 1)
			{
				int userInput = 0;

				// Cannot equip armour if they do not have any

				int numItems = player.inventory.print_armour(true);
				if(numItems == 0) break;

				while(!userInput)
				{
					// Choose a piece of armour to equip
					cout << "Equip which item?" << endl;
					cin >> userInput;
					// Equipment is numbered but is stored in a list,
					// so the number must be converted into a list element
					if(userInput >= 1 && userInput <= numItems)
					{
						int i = 1;

						for(auto it : player.inventory.armour)
						{
							if(i++ == userInput)
							{
								// Equip the armour if it is found
								player.equipArmour(it.first);
								break;
							}
						}
					}
				}
			}
			// Equip a weapon, using the same algorithms as for armour
			else if(result2 == 2)
			{
				int userInput = 0;
				int numItems = player.inventory.print_weapons(true);

				if(numItems == 0) break;

				while(!userInput)
				{
					cout << "Equip which item?" << endl;
					cin >> userInput;
					if(userInput >= 1 && userInput <= numItems)
					{
						int i = 1;

						for(auto it : player.inventory.weapons)
						{
							if(i++ == userInput)
							{
								player.equipWeapon(it.first);
								break;
							}
						}
					}
				}
			}
			cout << "----------------\n";
			break;
		}
		// Output the character information, including name, class (if
		// they have one), stats, level, and experience
		case 3:
			cout << "Character\n=========\n";
			cout << player.characterName;
			if(player.className != "") cout << " the " << player.className;
			cout << endl;

			cout << "HP: " << player.health << " / " << player.maxHealth << endl;
			cout << "Str: " << player.str << endl;
			cout << "End: " << player.end << endl;
			cout << "Dex: " << player.dex << endl;
			cout << "Lvl: " << player.level << " (" << player.exp;
			cout <<  " / " << player.expToLevel(player.level+1) << ")" << endl;
			cout << "----------------\n";
			break;
		default:
			break;
	}

	return player;
}
