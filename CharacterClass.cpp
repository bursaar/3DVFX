#include "CharacterClass.h"


CharacterClass::CharacterClass(MyMeshClass *pMyMesh)
{
	speed = 0.0f;
	mMyMesh = new MyMeshClass (*pMyMesh);
	characterMesh = mMyMesh->mesh;
}


CharacterClass::~CharacterClass()
{
}

void CharacterClass::DrawCharacter()
{
	characterMesh->DrawSubset(0);
}

void CharacterClass::UpdateCharacter()
{
	UpdateInput();
	UpdateLocation();
}

// Check whether there is movement required
void CharacterClass::UpdateInput()
{
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState(0x57))
	{
		mKeyUp = true;
	}
	else
	{
		mKeyUp = false;
	}

	if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(0x44))
	{
		mKeyRight = true;
	}
	else
	{
		mKeyRight = false;
	}

	if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(0x53))
	{
		mKeyDown = true;
	}
	else
	{
		mKeyDown = false;
	}

	if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(0x41))
	{
		mKeyLeft = true;
	}
	else
	{
		mKeyLeft = false;
	}
}

int CharacterClass::UpdateLocation()
{
	if (mKeyUp && mKeyLeft)
	{
		movement = FORWARDLEFT;
		return FORWARDLEFT;
	}
	if (mKeyUp && mKeyRight)
	{
		movement = FORWARDRIGHT;
		return FORWARDRIGHT;
	}
	if (mKeyDown && mKeyLeft)
	{
		movement = BACKWARDLEFT;
		return BACKWARDLEFT;
	}
	if (mKeyDown && mKeyRight)
	{
		movement = BACKWARDRIGHT;
		return BACKWARDRIGHT;
	}
	if (mKeyUp)
	{
		movement = FORWARD;
		return FORWARD;
	}
	if (mKeyRight)
	{
		movement = RIGHT;
		return RIGHT;
	}
	if (mKeyDown)
	{
		movement = BACK;
		return BACK;
	}
	if (mKeyLeft)
	{
		movement = LEFT;
		return LEFT;
	}
	movement = NONE;
	return NONE;
}