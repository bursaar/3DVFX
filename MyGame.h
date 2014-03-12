#pragma once

#include "CharacterClass.h"
#include "MeshManager.h"
#include "MyCameraController.h"


class MyGame
{
public:
	MyGame(HWND *pHWND);				// Pass a pointer to the handle of the window
	~MyGame();
	RenderClass mRenderer;
	MeshManager mMeshManager;

private:

	HWND *mHWND;
	void SetupGame();
};

