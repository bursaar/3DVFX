#pragma once
#include "MyMeshClass.h"

class CharacterClass
{
public:
	enum DIRECTIONS { NONE, FORWARD, RIGHT, BACK, LEFT };
	CharacterClass();
	~CharacterClass();
	float speed;
	D3DXVECTOR3 location;
	ID3DXMesh *characterMesh;
	int movement = NONE;
	float friction = 1.0f;
	void UpdateCharacter();
	
private:
	bool mKeyUp;
	bool mKeyDown;
	bool mKeyRight;
	bool mKeyLeft;

	// Check whether there is movement required
	void UpdateInput();

	// Update location with translation information
	int UpdateLocation();
};

