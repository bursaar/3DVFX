// ================================================================================================ //
//																									//
//						Level 7 3D Graphics for Computer Games (4241-504)							//
//																									//
//											 3DVFX													//
//											   by													//
//									       Ben Keenan												//
//																									//
//									  Student No. CD900002O											//
//																									//
//								   ben@ben.ie | +353 87 935 0483									//
//																									//
// ================================================================================================	//

// ACKNOWLEDGEMENTS
// Basic window construction code taken from http://www.directxtutorial.com/Lesson.aspx?lessonid=9-1-3
// Method of input taken from http://www.rastertek.com/dx11tut13.html

#include <windows.h>
#include <windowsx.h>
#include "RenderClass.h"
#include "T2G\Code\Leak Detector.h"
#include "MyGame.h"

#define WIN32_LEAN_AND_MEAN

// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam);

DWORD backgroundColour = D3DCOLOR_XRGB(0, 0, 0);

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	// the handle for the window, filled by a function
	HWND hWnd;
	// this struct holds information for the window class
	WNDCLASSEX wc;

	// clear out the window class for use
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// fill in the struct with the needed information
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	// wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"WindowClass1";

	// register the window class
	RegisterClassEx(&wc);

	// create the window and use the result as the handle
	hWnd = CreateWindowEx(NULL,
		L"WindowClass1",    // name of the window class
		L"Ben Keenan (CD900002O) - Portfolio 2 Assignment 1",   // title of the window
		WS_BORDER | WS_MINIMIZE,    // window style
		90,    // x-position of the window
		50,    // y-position of the window
		SCREEN_WIDTH,    // width of the window
		SCREEN_HEIGHT,    // height of the window
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		hInstance,    // application handle
		NULL);    // used with multiple windows, NULL

	// display the window on the screen
	ShowWindow(hWnd, nCmdShow);

	// Initialise Direct3D
	// RenderClass Renderer(hWnd);

	// Create game
	MyGame Game(hWnd);

	// enter the main loop:

	// this struct holds Windows event messages
	MSG msg;

	while (TRUE)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
			break;
		if (GetAsyncKeyState(VK_ESCAPE))
			break;
		Game.Update();
		// Game.mRenderer.render_frame();
	}

	// clean up DirectX and COM
	Game.mRenderer.cleanD3D();

	return msg.wParam;

	// wait for the next message in the queue, store the result in 'msg'
	while (GetMessage(&msg, NULL, 0, 0))
	{
		// translate keystroke messages into the right format
		TranslateMessage(&msg);

		// send the message to the WindowProc function
		DispatchMessage(&msg);
	}

	// return this part of the WM_QUIT message to Windows
	return msg.wParam;
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// sort through and find what code to run for the message given
	switch (message)
	{
		// this message is read when the window is closed
	case WM_DESTROY:
	{
					   // close the application entirely
					   PostQuitMessage(0);
					   return 0;
	} break;
	}

	// Handle any messages the switch statement didn't
	return DefWindowProc(hWnd, message, wParam, lParam);
}