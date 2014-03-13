#pragma once
#include "MyMeshClass.h"

class CharacterClass
{
public:
	enum DIRECTIONS { 
		NONE, 
		FORWARD, 
		RIGHT, 
		BACK, 
		LEFT, 
		FORWARDLEFT, 
		FORWARDRIGHT, 
		BACKWARDLEFT, 
		BACKWARDRIGHT };		// Cardinal directions
	CharacterClass(MyMeshClass *pMyMesh);											// Default constructor
	~CharacterClass();											// Default destructor
	float speed;												// Current speed constant
	float rotationInRadians;									// Current rotation
	D3DXVECTOR3 location;										// Vector to hold current location
	int movement = NONE;										// Current direction of travel
	float friction = 1.0f;										// Current friction experienced on the ground
	void UpdateCharacter();										// Member function to update stats of character.
	void DrawCharacter();
	MyMeshClass *mMyMesh;										// My mesh class for the character.

private:
	bool mKeyUp;
	bool mKeyDown;
	bool mKeyRight;
	bool mKeyLeft;

	ID3DXMesh *characterMesh;									// Pointer to mesh object

	// Check whether there is movement required
	void UpdateInput();

	// Update location with translation information
	int UpdateLocation();
};

