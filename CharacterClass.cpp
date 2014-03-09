#include "CharacterClass.h"


CharacterClass::CharacterClass()
{

}


CharacterClass::~CharacterClass()
{
}


// An AABB collision check for melee, collisions and projectiles. It will affect the health member variable. It takes a single boolean argument set by default to false. If it is passed as true, the function will automatically skip the AABB checks, check the type of item and either add an ability (e.g. Increased speed, armour etc) or add health.
bool CharacterClass::AmIHit(bool pNotify)
{
	return false;
}


// This function will add an item to the character instance’s inventory member vector, if it’s a weapon or trap. If it’s a health object or a power up, it will affect the character’s member variables appropriately.
void CharacterClass::PickUp(ItemClass pItem)
{
}


// Intended to be used mostly by the NPCs, this function is made to take any items from the inventory and drop them on the ground to be picked up by the player.
void CharacterClass::Drop(ItemClass pItem)
{
}


// This will take damage, depending on the type of damage being received. This will be passed with a value from enum damage, e.g. DAMAGE_FIRE or DAMAGE_WALL etc.
void CharacterClass::TakeDamage(int pDamage)
{
}


// Leaves a trail of fire behind the character as they move.
void CharacterClass::Burn()
{
}


// Leaves a trail of ice behind the character as they move.
void CharacterClass::Freeze()
{
}


int CharacterClass::CheckFireOrIce()
{
	return 0;
}