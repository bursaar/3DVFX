#pragma once

#include "MyWindows.h"
#include "RenderClass.h"
#include "Control\inputclass.h"

class SystemClass
{
public:
	SystemClass(HINSTANCE hInstance, int nCmdShow);
	SystemClass();
	~SystemClass();

	MyWindows m_MyWindow;
	RenderClass m_Renderer;
	InputClass m_Input;

	
	int Run();
};

