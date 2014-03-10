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

	InputClass m_Input;
	MyWindows m_MyWindow;
	RenderClass m_Renderer;
	MSG msg;



	
	int Run();
	int Shutdown();
};

