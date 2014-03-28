#pragma once
#include "Screen Properties.h"
#include "InputClass.h"
#include "RenderClass.h"
#include "T2G\Library\Timer.h"

#define WIN32_LEAN_AND_MEAN

class SystemClass
{
public:
	// the handle for the window, filled by a function
	HWND m_hWnd;
	// this struct holds information for the window class
	WNDCLASSEX m_wc;

	HINSTANCE m_hInstance;

	int m_nCmdShow;

	int Run();
	int Initialise(HINSTANCE pHInstance, int nCmdShow);
	int Shutdown();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

	SystemClass();
	~SystemClass();

private:
	int InitialiseWindows();
	int ShutdownWindow();
	RenderClass *m_renderer;
	InputClass *m_input;
};


// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam);

// Global
static SystemClass *ApplicationHandle = 0;