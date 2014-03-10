#include "SystemClass.h"


SystemClass::SystemClass(HINSTANCE hInstance, int nCmdShow)
{
	MyWindows MyWindow(hInstance, nCmdShow);
	m_MyWindow = MyWindow;

	// Initialise Direct3D
	RenderClass Renderer(MyWindow.hWnd);
	m_Renderer = Renderer;	
}

SystemClass::SystemClass()
{

}


SystemClass::~SystemClass()
{

}

int SystemClass::Run()
{
	while (TRUE)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
			break;

		// Rendering loop here
		m_Renderer.render_frame();
	}


	return 0;
}

int SystemClass::Shutdown()
{


	// return this part of the WM_QUIT message to Windows
	return msg.wParam;

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

	return 0;
}