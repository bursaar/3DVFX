#pragma once
#include "InputClass.h"
#include <d3dx9.h>

class CharacterClass
{
public:
	
	CharacterClass();											// Default constructor
	~CharacterClass();											// Default destructor
	float speed;												// Current speed constant
	float rotationInRadians;									// Current rotation
	float acceleration;
	D3DXVECTOR3 location;										// Vector to hold current location
	float friction = 1.0f;										// Current friction experienced on the ground
	void UpdateCharacter(int pMovement);										// Member function to update stats of character.
	void DrawCharacter();
	ID3DXMesh *mMyMesh;										// My mesh class for the character.

private:
	bool mKeyUp;
	bool mKeyDown;
	bool mKeyRight;
	bool mKeyLeft;

	ID3DXMesh *characterMesh;									// Pointer to mesh object

	// Check whether there is movement required
	void UpdateInput(int pMovement);

	// Update location with translation information
	int UpdateLocation();
};

