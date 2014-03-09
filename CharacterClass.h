#pragma once

#include "ItemClass.h"
#include <vector>

using namespace std;

class CharacterClass
{
public:
	CharacterClass();
	~CharacterClass();
	enum powers { POWER_NONE, POWER_BURNING, POWER_FREEZING, POWER_SPEEDY }; // Special powers that give the character the ability to create a trail of fire, a trail of ice or super speed. Set by default to 0.
	enum damage { DAMAGE_BUMP = 2, DAMAGE_FIRE = 5, DAMAGE_ARROW = 15, DAMAGE_WALL = 16, DAMAGE_MELEE = 20 };
	enum types { PLAYER, NPC };
	float health;
	vector<ItemClass> inventory;
	int lives;
	const int whatAmI = PLAYER;
	// An AABB collision check for melee, collisions and projectiles. It will affect the health member variable. It takes a single boolean argument set by default to false. If it is passed as true, the function will automatically skip the AABB checks, check the type of item and either add an ability (e.g. Increased speed, armour etc) or add health.
	bool AmIHit(bool pNotify);
	// This function will add an item to the character instance’s inventory member vector, if it’s a weapon or trap. If it’s a health object or a power up, it will affect the character’s member variables appropriately.
	void PickUp(ItemClass pItem);
	// Intended to be used mostly by the NPCs, this function is made to take any items from the inventory and drop them on the ground to be picked up by the player.
	void Drop(ItemClass pItem);
private:
	float speed;
public:
	int currentPower;
	float slipperiness;
private:
	// This will take damage, depending on the type of damage being received. This will be passed with a value from enum damage, e.g. DAMAGE_FIRE or DAMAGE_WALL etc.
	void TakeDamage(int pDamage);
	// Leaves a trail of fire behind the character as they move.
	void Burn();
	// Leaves a trail of ice behind the character as they move.
	void Freeze();
	// Checks the ground for fire or ice. If it’s fire, it will apply the TakeDamage() member function with the value DAMAGE_FIRE. If it’s ice, it will take the original speed variable, add or subtract the slipperiness member variable to the speed member variable once a second. As soon as it detects that the character is no longer on ice, it will return the speed value to its default.
	int CheckFireOrIce();
};

