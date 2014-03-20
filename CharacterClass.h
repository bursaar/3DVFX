#pragma once
#include "InputClass.h"
#include "MyMeshClass.h"


class CharacterClass
{
public:
	CharacterClass();											// Default constructor
	~CharacterClass();											// Default destructor
	float speed;												// Current speed constant
	D3DXVECTOR3 location;										// Vector to hold current location
	MyMeshClass *characterMesh;									// Pointer to mesh object
	float friction = 1.0f;										// Current friction experienced on the ground
	void UpdateCharacter();										// Member function to update stats of character.
	InputClass Input;
	void Frame();

private:
	bool mKeyUp;
	bool mKeyDown;
	bool mKeyRight;
	bool mKeyLeft;

	// Check whether there is movement required
	void UpdateInput();

	void DrawCharacter();

	D3DXVECTOR3 translation;										// Vector to hold current translation
	D3DXVECTOR3 rotation;										// Vector to hold current rotation
	D3DXVECTOR3 scale;										// Vector to hold current scale


};

