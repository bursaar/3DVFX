#include "CharacterClass.h"


CharacterClass::CharacterClass()
{
	speed = 0.0f;
}


CharacterClass::~CharacterClass()
{
}

void CharacterClass::DrawCharacter()
{
	characterMesh->DrawSubset(0);
}

void CharacterClass::UpdateCharacter(int pMovement)
{
	UpdateInput(pMovement);
	UpdateLocation();
}

// Check whether there is movement required
void CharacterClass::UpdateInput(int pMovement)
{
	// Player attributes first - NPC attributes will be derived from this model
	if (speed > 0)
	{
		speed -= friction;		// Trend towards zero with friction variable.
	}
	if (speed < 0)
	{
		speed += friction;		// Trend towards zero with friction variable.
	}

	switch (pMovement)
	{
	case InputClass::BACKWARDRIGHT:
	{
									  speed += acceleration;
									  rotationInRadians -= rotationInRadians;
									  break;
	}
	case InputClass::BACKWARDLEFT:
	{
									 speed += acceleration;
									 rotationInRadians -= rotationInRadians;
									 break;
	}
	case InputClass::FORWARDRIGHT:
	{
									 speed -= acceleration;
									 rotationInRadians += rotationInRadians;
									 break;
	}
	case InputClass::FORWARDLEFT:
	{
									speed -= acceleration;
									rotationInRadians -= rotationInRadians;
									break;
	}
	case InputClass::BACK:
	{
									 speed += acceleration;
									 break;
	}
	case InputClass::FORWARD:
	{
									speed -= acceleration;
									break;
	}
	case InputClass::LEFT:
	{
							 rotationInRadians -= rotationInRadians;
							 break;
	}
	case InputClass::RIGHT:
	{
							  rotationInRadians += rotationInRadians;
							  break;
	}
	}

	// Send data somewhere
}

int CharacterClass::UpdateLocation()
{
	return 0;
}