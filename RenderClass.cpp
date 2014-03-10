#include "RenderClass.h"


RenderClass::RenderClass(HWND pHWND)
{
	RenderClass::initD3D(pHWND);
}

RenderClass::RenderClass()
{

}

RenderClass::~RenderClass()
{
}

void RenderClass::initD3D(HWND hWnd)					// sets up and initializes Direct3D
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	m_FOV = 45;

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.EnableAutoDepthStencil = TRUE;    // automatically run the z-buffer for us
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;    // 16-bit pixel format for the z-buffer

	// create a device class using this information and the info from the d3dpp stuct
	d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	init_graphics();    // call the function to initialize the triangle

	d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);    // turn off the 3D lighting
	// d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);    // both sides of the triangles
	d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);    // turn on the z-buffer
}

void RenderClass::render_frame()		// renders a single frame
{

	float diff = 0.0f;
	
	if (GetAsyncKeyState(VK_LEFT))
	{
		diff += 0.1f;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		diff -= 0.1f;
	}

	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);		// Clear the buffer
	d3ddev->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);		// Clear the depth buffer

	d3ddev->BeginScene();

		// select which vertex format we are using
		d3ddev->SetFVF(CUSTOMFVF);

		SetViewTransform();

		if (GetAsyncKeyState(VK_UP))
		{
			m_FOV += 1;
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			m_FOV -= 1;
		}

		SetProjectionTransform(m_FOV, 1.0f, 100.0f);

		D3DXMATRIX matScale;
		D3DXMATRIX matTranslate;
		D3DXMATRIX matRotateY;											// a matrix to store the rotation for each object
		static float index = 0.0f; index += diff;						// an ever-increasing float value

		D3DXMatrixScaling(&matScale, 0.5f, 0.5f, 0.5f);
		D3DXMatrixTranslation(&matTranslate, 0.0f, 0.0f, 2.0f);
		D3DXMatrixRotationY(&matRotateY, index);						// Rotate object

		

	d3ddev->EndScene();

	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void RenderClass::cleanD3D(void)						// closes Direct3D and releases memory
{
	v_buffer->Release();    // close and release the vertex buffer
	d3ddev->Release();		// close and release the 3D device
	d3d->Release();			// close and release Direct3D
}

void RenderClass::init_graphics(void)					// 3D declarations
{

	// Create a sphere
	CUSTOMVERTEX sphereOrigin = { 0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(0, 0, 255) };
	float fl_radius = 1.0f;
	int slices = 15;
	int stacks = 15;
	LPD3DXMESH sphereMesh;

	D3DXCreateSphere(d3ddev, fl_radius, slices, stacks, &sphereMesh, NULL);

	D3DXATTRIBUTERANGE sphereAttribs;
	DWORD sphereAttribTableSize;

	DWORD sphereVertexCount = sphereMesh->GetNumVertices();
	sphereMesh->GetAttributeTable(&sphereAttribs, &sphereAttribTableSize);

	DWORD sphereVertexStartLoc = sphereAttribs.VertexStart;
	CUSTOMVERTEX sphereVertexStart = { sphereVertexStartLoc };

	sphereMesh->GetVertexBuffer(&v_buffer);

	int sphereFaceCount = sphereMesh->GetNumFaces();
	const int arraySize = sphereFaceCount * 3;

	DWORD * adaj = new DWORD[arraySize];											// Taken from http://ngemu.com/threads/c-setting-the-size-of-array-during-runtime.42522/

	sphereMesh->GenerateAdjacency(0.5f, adaj);
	sphereMesh->OptimizeInplace(
		D3DXMESHOPT_COMPACT |
		D3DXMESH_MANAGED |
		D3DXMESHOPT_ATTRSORT,adaj ,NULL, NULL, NULL);


	VOID* pVoid = NULL;    // a void pointer

	// lock v_buffer and load the vertices into it
	// v_buffer->Lock(0, 0, (void**)&pVoid, 0);
	
	int numSubSets = sphereMesh->GetAttributeTable(&sphereAttribs, &sphereAttribTableSize);
	
	for (DWORD i = 0; i < numSubSets; i++)
	{
		sphereMesh->DrawSubset(i);
	}
	memcpy(pVoid, v_buffer, sizeof(sphereVertexCount));
	v_buffer->Unlock();

}

void RenderClass::SetViewTransform()
{
	// set the view transform
	D3DXMATRIX matView;    // the view transform matrix
	D3DXMatrixLookAtLH(&matView,
		&D3DXVECTOR3(0.0f, 8.0f, 25.0f),   // the camera position
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),    // the look-at position
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));    // the up direction
	d3ddev->SetTransform(D3DTS_VIEW, &matView);    // set the view transform to matView
}

void RenderClass::SetViewTransform(D3DXVECTOR3 pCameraPosition, D3DXVECTOR3 pLookAtPosition, D3DXVECTOR3 UpDirection)
{// set the view transform
	D3DXMATRIX matView;    // the view transform matrix
	D3DXMatrixLookAtLH(&matView,
		&pCameraPosition,   // the camera position
		&pLookAtPosition,    // the look-at position
		&UpDirection);    // the up direction
	d3ddev->SetTransform(D3DTS_VIEW, &matView);    // set the view transform to matView
}

void RenderClass::SetProjectionTransform()
{
	// set the projection transform
	D3DXMATRIX matProjection;										// the projection transform matrix
	D3DXMatrixPerspectiveFovLH(&matProjection,
		D3DXToRadian(45),											// the horizontal field of view
		(FLOAT)SCREEN_WIDTH / (FLOAT)SCREEN_HEIGHT,					// aspect ratio
		1.0f,														// the near view-plane
		100.0f);													// the far view-plane
	d3ddev->SetTransform(D3DTS_PROJECTION, &matProjection);			// set the projection
}

void RenderClass::SetProjectionTransform(int pFOV, float pNearView = 1.0f, float pFarView = 100.0f)
{
	// set the projection transform
	D3DXMATRIX matProjection;										// the projection transform matrix
	D3DXMatrixPerspectiveFovLH(&matProjection,
		D3DXToRadian(pFOV),											// the horizontal field of view
		(FLOAT)SCREEN_WIDTH / (FLOAT)SCREEN_HEIGHT,					// aspect ratio
		pNearView,													// the near view-plane
		pFarView);													// the far view-plane
	d3ddev->SetTransform(D3DTS_PROJECTION, &matProjection);			// set the projection
}

