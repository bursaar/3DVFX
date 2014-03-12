#pragma once

#include "CharacterClass.h"
#include "MeshManager.h"
#include "MyCameraController.h"


class MyGame
{
public:
	MyGame(HWND &pHWND);				// Pass a pointer to the handle of the window
	~MyGame();
	RenderClass mRenderer;
	MeshManager mMeshManager;

	// Pointers to characters
	CharacterClass *mPlayerCharacter;
	CharacterClass *mNPC1;
	CharacterClass *mNPC2;


	void Update();
private:
	// Tunable values for speeds of characters
	// PLAYER
		float accelerationPlayer = 0.01f;
		float rotationPlayer = 0.06f;

	HWND *mHWND;
	void SetupGame();
};

