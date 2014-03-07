// Basic window construction code taken from http://www.directxtutorial.com/Lesson.aspx?lessonid=9-1-3
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Screen Properties.h"

// include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

// global declarations
LPDIRECT3D9 d3d;							// the pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;					// the pointer to the device class
LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;    // the pointer to the vertex buffer

// function prototypes
void initD3D(HWND hWnd);    // sets up and initializes Direct3D
void render_frame(void);    // renders a single frame
void cleanD3D(void);		// closes Direct3D and releases memory
void init_graphics(void);    // 3D declarations


// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam);

DWORD backgroundColour = D3DCOLOR_XRGB(backgroundRed, backgroundGreen, backgroundBlue);

struct CUSTOMVERTEX
{
	FLOAT x, y, z;    // from the D3DFVF_XYZRHW flag
	DWORD color;    // from the D3DFVF_DIFFUSE flag
};

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
		WS_EX_TOPMOST | WS_POPUP,    // window style
		0,    // x-position of the window
		0,    // y-position of the window
		SCREEN_WIDTH,    // width of the window
		SCREEN_HEIGHT,    // height of the window
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		hInstance,    // application handle
		NULL);    // used with multiple windows, NULL

	// display the window on the screen
	ShowWindow(hWnd, nCmdShow);

	// set up and initialize Direct3D
	initD3D(hWnd);

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

		render_frame();
	}

	// clean up DirectX and COM
	cleanD3D();

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

// this function initializes and prepares Direct3D for use
void initD3D(HWND hWnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);    // create the Direct3D interface

	D3DPRESENT_PARAMETERS d3dpp;    // create a struct to hold various device information

	ZeroMemory(&d3dpp, sizeof(d3dpp));						// clear out the struct for use
	d3dpp.Windowed = TRUE;									// program windowed, not fullscreen
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;				// discard old frames
	d3dpp.hDeviceWindow = hWnd;								// set the window to be used by Direct3D
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;				// set the back buffer format to 32-bit
	d3dpp.BackBufferWidth = SCREEN_WIDTH;					// set the width of the buffer
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;					// set the height of the buffer

	// create a device class using this information and information from the d3dpp stuct
	d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);			// Disable 3D lighting
}

// this is the function used to render a single frame
void render_frame(void)
{
	// clear the window
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, NULL, 1.0f, 0);

	d3ddev->BeginScene();    // begins the 3D scene

	// do 3D rendering on the back buffer here
	init_graphics();    // call the function to initialize the triangle

	// select which vertex format we are using
	d3ddev->SetFVF(CUSTOMFVF);

	// PIPELINE
	D3DXMATRIX matRotateY;

	static float index = 0.0f; index += 0.05f;

	// Build matrix to roate the model based on the increasing float value
	D3DXMatrixRotationY(&matRotateY, index);

	// Tell DirectX about the matrix
	d3ddev->SetTransform(D3DTS_WORLD, &matRotateY);

	D3DXMATRIX matView;	// View transformation matrix

	D3DXMatrixLookAtLH(&matView,
		&D3DXVECTOR3(0.0f, 0.0f, 10.0f),	// Camera position
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// Look at or target position
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)		// The direction of up
		);

	d3ddev->SetTransform(D3DTS_VIEW, &matView);		// Put the view transform in matView

	D3DXMATRIX matProjection;				// projection transform matrix

	D3DXMatrixPerspectiveFovLH(&matProjection,
		D3DXToRadian(45),								// Field of View
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,		// Aspect ratio
		1.0f,											// Near plane
		100.0f);										// Far plane

	d3ddev->SetTransform(D3DTS_PROJECTION, &matProjection);

	// select the vertex buffer to display
	d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));

	// copy the vertex buffer to the back buffer
	d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

	d3ddev->EndScene();    // ends the 3D scene

	d3ddev->Present(NULL, NULL, NULL, NULL);   // displays the created frame on the screen
}


// this is the function that cleans up Direct3D and COM
void cleanD3D(void)
{
	v_buffer->Release();    // close and release the vertex buffer
	d3ddev->Release();		// close and release the 3D device
	d3d->Release();			// close and release Direct3D
}

// this is the function that puts the 3D models into video RAM
void init_graphics(void)
{

	
	// create the vertices using the CUSTOMVERTEX struct
	CUSTOMVERTEX vertices[] =
	{
		{ 2.5f, -3.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 255), },
		{ 0.0f, 3.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0), },
		{ -2.5f, -3.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0), },
	};

	// create a vertex buffer interface called v_buffer
	d3ddev->CreateVertexBuffer(3 * sizeof(CUSTOMVERTEX),
		0,
		CUSTOMFVF,
		D3DPOOL_MANAGED,
		&v_buffer,
		NULL);

	VOID* pVoid;    // a void pointer

	// lock v_buffer and load the vertices into it
	v_buffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, vertices, sizeof(vertices));
	v_buffer->Unlock();
}