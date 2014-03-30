#pragma once
#include "SphereClass.h"
class PlayerClass :
	public SphereClass
{
public:
	PlayerClass() : SphereClass(0xFF55FF55)		// Starting sphere as seen in LIT material
	{

	};
	void OnCollide(RenderableObject *pObject) override
	{
		OutputDebugStringA("Player registered a collision!\n");
		switch (travel)
		{
		case FORWARD:
			Move(0.0f, 0.0f, -speed);
			break;
		case BACK:
			Move(0.0f, 0.0f, speed);
			break;
		}
		switch (strafe)
		{
		case LEFT:
			Move(speed, 0.0f, 0.0f);
			break;
		case RIGHT:
			Move(-speed, 0.0f, 0.0f);
		}
	}

	enum DIRECTIONS {NONE, FORWARD, RIGHT, BACK, LEFT};
	int travel;
	int strafe;
};

