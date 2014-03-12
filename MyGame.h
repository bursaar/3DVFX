#pragma once

#include "CharacterClass.h"
#include "MeshManager.h"
#include "MyCameraController.h"


class MyGame
{
public:
	MyGame(HWND pHWND, RenderClass pRenderClass);
	~MyGame();

private:
	RenderClass *mRenderClass;
	HWND mHWND;
	void SetupGame();
};

