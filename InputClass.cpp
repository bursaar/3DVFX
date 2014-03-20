#include "InputClass.h"


InputClass::InputClass()
{
	keyinput = 0;
}


InputClass::~InputClass()
{
}


void InputClass::GetKeyboardState()
{
	if (GetAsyncKeyState(VK_UP)
		|| GetAsyncKeyState(0x57))
	{
		keyinput = LEFT;

		if (GetAsyncKeyState(VK_LEFT)
			|| GetAsyncKeyState(0x41))
		{
			keyinput = UPLEFT;
			return;
		}
		if (GetAsyncKeyState(VK_RIGHT)
			|| GetAsyncKeyState(0x44))
		{
			keyinput = UPRIGHT;
			return;
		}
		return;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		keyinput = DOWN;

		if (GetAsyncKeyState(VK_LEFT)
			|| GetAsyncKeyState(0x41))
		{
			keyinput = DOWNLEFT;
			return;
		}
		if (GetAsyncKeyState(VK_RIGHT)
			|| GetAsyncKeyState(0x44))
		{
			keyinput = DOWNRIGHT;
			return;
		}
		return;
	}

	if (GetAsyncKeyState(VK_LEFT)
		|| GetAsyncKeyState(0x41))
	{
		keyinput = LEFT;
		return;
	}

	if (GetAsyncKeyState(VK_RIGHT)
		|| GetAsyncKeyState(0x44))
	{
		keyinput = RIGHT;
		return;
	}

	keyinput = KEYNONE;
	return;
}

int InputClass::Frame()
{
	GetKeyboardState();
	switch (keyinput)
	{
	case KEYNONE:
		direction = DIRECTIONS::DIRNONE;
		rotation = ROTATIONS::ROTNONE;
		break;
	case UPLEFT:
		direction = DIRECTIONS::FORWARD;
		rotation = ROTATIONS::COUNTER;
		break;
	case UPRIGHT:
		direction = DIRECTIONS::FORWARD;
		rotation = ROTATIONS::CLOCK;
		break;
	case DOWNLEFT:
		direction = DIRECTIONS::BACK;
		rotation = ROTATIONS::COUNTER;
		break;
	case DOWNRIGHT:
		direction = DIRECTIONS::BACK;
		rotation = ROTATIONS::CLOCK;
	case UP:
		direction = DIRECTIONS::FORWARD;
		rotation = ROTATIONS::ROTNONE;
		break;
	case RIGHT:
		direction = DIRECTIONS::DIRNONE;
		rotation = ROTATIONS::CLOCK;
		break;
	case LEFT:
		direction = DIRECTIONS::DIRNONE;
		rotation = ROTATIONS::COUNTER;
		break;
	case DOWN:
		direction = DIRECTIONS::BACK;
		rotation = ROTATIONS::ROTNONE;
		break;
	}

	return direction * rotation;

}