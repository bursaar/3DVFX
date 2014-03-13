#include "SystemClass.h"


SystemClass::SystemClass()
{
}


SystemClass::~SystemClass()
{
}

int SystemClass::InitialiseWindows()
{

	// clear out the window class for use
	ZeroMemory(&m_wc, sizeof(WNDCLASSEX));

	// fill in the struct with the needed information
	m_wc.cbSize = sizeof(WNDCLASSEX);
	m_wc.style = CS_HREDRAW | CS_VREDRAW;
	m_wc.lpfnWndProc = WindowProc;
	m_wc.hInstance = m_hInstance;
	m_wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	// wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	m_wc.lpszClassName = L"WindowClass1";

	// register the window class
	RegisterClassEx(&m_wc);

	// create the window and use the result as the handle
	m_hWnd = CreateWindowEx(NULL,
		L"WindowClass1",			// name of the window class
		L"Ben Keenan (CD900002O) - Portfolio 2 Assignment 1",   // title of the window
		WS_BORDER | WS_MINIMIZE,    // window style
		90,					 // x-position of the window
		50,					// y-position of the window
		SCREEN_WIDTH,    // width of the window
		SCREEN_HEIGHT,    // height of the window
		NULL,				// we have no parent window, NULL
		NULL,			 // we aren't using menus, NULL
		m_hInstance,    // application handle
		NULL);			// used with multiple windows, NULL
}

int SystemClass::Initialise(HINSTANCE pHInstance, int pNCmdShow)
{

	m_hInstance = pHInstance;
	m_nCmdShow = pNCmdShow;

	InitialiseWindows();
}

int SystemClass::Run()
{
	// this struct holds Windows event messages
	MSG msg;

	// display the window on the screen
	ShowWindow(m_hWnd, m_nCmdShow);

	// Initialise Direct3D
	// RenderClass Renderer(hWnd);

	// Create game
	MyGame Game(m_hWnd);

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

int SystemClass::Shutdown()
{
	



}

int SystemClass::ShutdownWindow()
{
	DestroyWindow(m_hWnd);

	UnregisterClass(m_wc.lpszClassName, m_hInstance);
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