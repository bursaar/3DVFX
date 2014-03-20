#pragma once
#include "Screen Properties.h"
#include <Windows.h>

class InputClass
{
public:
	InputClass();
	~InputClass();

	enum DIRECTIONS { DIRNONE = 2, FORWARD = 4, BACK = 6 };
	enum ROTATIONS { ROTNONE = 3, COUNTER = 5, CLOCK = 7 };
	enum KEYINPUT { KEYNONE, UP, RIGHT, DOWN, LEFT, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT};

	int direction; // NONE = 2, FORWARD = 4, BACK = 6
	int rotation;  // NONE = 3, COUNTER = 5, CLOCK = 7

	// This function runs the GetKeyboardState() member function and then returns a single int that is a unique
	// combination of the direction and rotation member variables.
	// 6  = NONE
	// 10 = COUNTERCLOCKWISE
	// 12 = FORWARD
	// 14 = CLOCKWISE
	// 18 = BACKWARD
	// 20 = FORWARD & COUNTERCLOCKWISE
	// 28 = FORWARD & CLOCKWISE
	// 30 = BACKWARD & COUNTERCLOCKWISE
	// 42 = BACKWARD & CLOCKWISE
	int Frame();

private:
	int keyinput;
	void GetKeyboardState();
};

