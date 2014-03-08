#include "SystemClass.h"


SystemClass::SystemClass(HINSTANCE hInstance, int nCmdShow)
{
	MyWindows MyWindow(hInstance, nCmdShow);
	m_MyWindow = MyWindow;

	// Initialise Direct3D
	m_Renderer(MyWindow.hWnd);


	// Initialise the input class
	m_Input.Initialize(hInstance, MyWindow.hWnd, SCREEN_WIDTH, SCREEN_HEIGHT);
	
}

SystemClass::SystemClass()
{

}


SystemClass::~SystemClass()
{

}

int SystemClass::Run()
{
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

		m_Input.Frame();
		m_Renderer.render_frame(m_Input);

		if (m_Input.IsEscapePressed()) break;
	}

	// clean up DirectX and COM
	m_Renderer.cleanD3D();

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