#include "D3DClass.h"


D3DClass::D3DClass()
{

}


D3DClass::~D3DClass()
{
}


void D3DClass::Initialise(HWND pHWND)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = pHWND;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.EnableAutoDepthStencil = TRUE;			// automatically run the z-buffer for us
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;		// 16-bit pixel format for the z-buffer

	// create a device class using this information and the info from the d3dpp stuct
	d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		pHWND,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	d3ddev->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(255, 255, 255));
	d3ddev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);				// turn off the 3D lighting
	d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);		// both sides of the triangles
	d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);				// turn on the z-buffer

	fieldOfView = 45 * DEG_TO_RAD;
	screenAspect = SCREEN_WIDTH / SCREEN_HEIGHT;
	nearView = 1.0f;
	farView = 500.0f;

	// Initialise and set the projection matrix
	D3DXMatrixPerspectiveFovLH(&mMatProjection, fieldOfView, screenAspect, nearView, farView);

	// Initialise world matrix
	D3DXMatrixIdentity(&mMatWorld);
}