#include "InputClass.h"


InputClass::InputClass()
{
}


InputClass::~InputClass()
{
}

int InputClass::UpdateKeyboard()
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

	return 1;
}

int InputClass::Frame()
{
	UpdateKeyboard();
	UpdateDirection();
	return 0;
}

int InputClass::UpdateDirection()
{
	if (mKeyUp && mKeyLeft)
	{
		m_direction = FORWARDLEFT;
		return FORWARDLEFT;
	}
	if (mKeyUp && mKeyRight)
	{
		m_direction = FORWARDRIGHT;
		return FORWARDRIGHT;
	}
	if (mKeyDown && mKeyLeft)
	{
		m_direction = BACKWARDLEFT;
		return BACKWARDLEFT;
	}
	if (mKeyDown && mKeyRight)
	{
		m_direction = BACKWARDRIGHT;
		return BACKWARDRIGHT;
	}
	if (mKeyUp)
	{
		m_direction = FORWARD;
		return FORWARD;
	}
	if (mKeyRight)
	{
		m_direction = RIGHT;
		return RIGHT;
	}
	if (mKeyDown)
	{
		m_direction = BACK;
		return BACK;
	}
	if (mKeyLeft)
	{
		m_direction = LEFT;
		return LEFT;
	}
	m_direction = NONE;
	return NONE;
}