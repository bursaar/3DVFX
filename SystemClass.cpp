#include "SystemClass.h"
#include "T2G\Code\Scene.h"
#include "PlayerClass.h"

bool keys[256];

SystemClass::SystemClass()
{
	m_nCmdShow = 0;
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

	return 0;
}

int SystemClass::Initialise(HINSTANCE pHInstance, int pNCmdShow)
{

	m_hInstance = pHInstance;
	m_nCmdShow = pNCmdShow;

	m_input = new InputClass;
	m_renderer = new RenderClass;

	m_renderer->Initialise(m_hWnd);

	InitialiseWindows();

	return 0;
}

int SystemClass::Run()
{
	ZeroMemory(&keys, 256);

	// this struct holds Windows event messages
	MSG msg;

	// display the window on the screen
	ShowWindow(m_hWnd, m_nCmdShow);


	Train2Game::Scene * scene = new Train2Game::Scene;
	PlayerClass * player = new PlayerClass;

	// Initialise Direct3D
	m_renderer->Initialise(m_hWnd);

	scene->Initialise(m_renderer);
	player->Initialise(m_renderer);

	// Create new timer
	Train2Game::Timer * timer = new Train2Game::Timer;
	
	MyCameraController * camera = m_renderer->GetCameraController();
	camera->Follow(player);
	player->Move(0.0f, 0.0f, -5.0f);

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

		double x, y, z;

		player->GetPosition(x, y, z);

		scene->CheckCollisions(player);

		double updTime = timer->Update();
		double totTime = timer->Total();
		scene->Update(updTime, totTime);
		player->Update(updTime, totTime);

		m_renderer->BeginFrame();

		if (keys[0x57])
		{
			player->Move(0.0f, 0.0f, 0.05f);
		}
		if (keys[0x41])
		{
			player->Move(-0.05f, 0.0f, 0.0f);
		}
		if (keys[0x53])
		{
			player->Move(0.0f, 0.0f, -0.05f);
		}
		if (keys[0x44])
		{
			player->Move(0.05f, 0.0f, 0.0f);
		}
		if (keys[VK_LEFT])
		{
			player->RotateY(1.0f);
		}
		if (keys[VK_RIGHT])
		{
			player->RotateY(-1.0f);
		}

		D3DXMATRIXA16 baseMatrix;
		m_renderer->d3ddev->GetTransform(D3DTS_WORLD, &baseMatrix);

		scene->Render(baseMatrix);
		player->Render(baseMatrix);

		// I took the below if statement's structure from the LIT material
		if (!m_renderer->EndFrame())
		{
			// Release all buffers
			scene->Release();
			player->Release();

			// Loop until successful reset or closure
			while (!m_renderer->Reset() && msg.message != WM_QUIT)
			{
				// Keep the message queue going so the window remains responsive
				if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					DispatchMessage(&msg);
				}

				// Limit the speed of the loop to roughly 60Hz
				Sleep(16);
			}

			// If the user quits, we break to avoid initialising anything.
			if (msg.message == WM_QUIT)
			{
				break;
			}

			// At this point, the device is back and the user hasn't quit
			m_renderer->Initialise(m_hWnd);

			// Recreate vertex buffers and reload textures in use
			scene->Resume();
			player->Resume();

			// Update to keep the timer correct
			timer->Update();
		}
	}

	return msg.wParam;

	// wait for the next message in the queue, store the result in 'msg'
	while (GetMessage(&msg, NULL, 0, 0))
	{
		// translate keystroke messages into the right format
		TranslateMessage(&msg);

		// send the message to the WindowProc function
		DispatchMessage(&msg);
	}

	// Release the objects in the scene
	player->Release();
	scene->Release();
	
	delete scene;
	delete player;
	delete m_renderer;

	// return this part of the WM_QUIT message to Windows
	return msg.wParam;
}

int SystemClass::Shutdown()
{
	int result = ShutdownWindow();

	return result;
}

int SystemClass::ShutdownWindow()
{
	BOOL result = false;
	result = DestroyWindow(m_hWnd);

	UnregisterClass(m_wc.lpszClassName, m_hInstance);

	if (result)
	{
		return 0;
	}
	
	return 1;
}

LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	return DefWindowProc(hwnd, umsg, wparam, lparam);
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	// sort through and find what code to run for the message given
	switch (umessage)
	{
		// this message is read when the window is closed
	case WM_DESTROY:
	{
					   // close the application entirely
					   PostQuitMessage(0);
					   return 0;
	} break;
	case WM_KEYDOWN:
		keys[wparam] = true;
		break;
	case WM_KEYUP:
		keys[wparam] = false;
		break;
	}

	// Handle any messages the switch statement didn't get
	return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
}



