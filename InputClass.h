#pragma once
#include <Windows.h>

class InputClass
{
public:
	InputClass();
	~InputClass();

	enum DIRECTIONS {
		NONE,
		FORWARD,
		RIGHT,
		BACK,
		LEFT,
		FORWARDLEFT,
		FORWARDRIGHT,
		BACKWARDLEFT,
		BACKWARDRIGHT
	};		// Cardinal directions

	int m_direction;

	int Frame();
	

private:
	int UpdateKeyboard();
	int UpdateDirection();

	bool mKeyUp;
	bool mKeyRight;
	bool mKeyDown;
	bool mKeyLeft;
};

