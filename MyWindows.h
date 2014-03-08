#pragma once

#include <windows.h>
#include <windowsx.h>
#include "Screen Properties.h"

#define WIN32_LEAN_AND_MEAN

using namespace std;

class MyWindows
{
public:
	// the WindowProc function prototype
	static LRESULT CALLBACK WindowProc(HWND hWnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam);

	// the handle for the window, filled by a function
	HWND hWnd;
	// this struct holds information for the window class
	WNDCLASSEX wc;


	MyWindows(HINSTANCE hInstance, int nCmdShow);
	MyWindows::MyWindows();
	~MyWindows();
};

