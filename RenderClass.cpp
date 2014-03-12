#include "RenderClass.h"


RenderClass::RenderClass(HWND *pHWND)
{
	mHWND = pHWND;
	RenderClass::initD3D();

}

RenderClass::RenderClass()
{

}

RenderClass::~RenderClass()
{
}

void RenderClass::initD3D()					// sets up and initializes Direct3D
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	m_FOV = 45;

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = *mHWND;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.EnableAutoDepthStencil = TRUE;    // automatically run the z-buffer for us
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;    // 16-bit pixel format for the z-buffer

	// create a device class using this information and the info from the d3dpp stuct
	d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		*mHWND,
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
	DWORD timer = 0;

	timer = GetTickCount();

	static float diff = 0.0f;
	static float index = 0.0f; index += diff;						// an ever-increasing float value
	static float spin = 0.0f;
	static float drive = 2.0f;

	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);		// Clear the buffer
	d3ddev->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);		// Clear the depth buffer

	d3ddev->BeginScene();

	// select which vertex format we are using
	d3ddev->SetFVF(CUSTOMFVF);

	// select the vertex and index buffers to use
	// d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));
	// d3ddev->SetIndices(i_buffer);

	D3DXMATRIX matScale;
	D3DXMATRIX matTranslate;
	D3DXMATRIX matRotateZ;
	D3DXMATRIX matRotateY;											// a matrix to store the rotation for each object
	D3DXMATRIX matRotateX;

	if (GetAsyncKeyState(VK_UP))
	{
		spin -= 0.01f;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		spin += 0.01f;
	}


	D3DXMatrixScaling(&matScale, 2.5f, 2.5f, 2.5f);								// Scale object
	D3DXMatrixRotationY(&matRotateY, D3DXToRadian(270));						// Rotate object left and right
	D3DXMatrixRotationX(&matRotateX, spin);										// Rotate object clockwise / counter clock
	D3DXMatrixRotationZ(&matRotateZ, 0.0f);
	D3DXMatrixTranslation(&matTranslate, 0.0f, 0.0f, drive += spin);			// Move object
	
	init_graphics();


	// Pipeline:
	d3ddev->SetTransform(D3DTS_WORLD, &(matScale * matRotateY * matRotateX * matTranslate));

	SetViewTransform();

	SetProjectionTransform(m_FOV, 1.0f, 100.0f);

	d3ddev->EndScene();

	d3ddev->Present(NULL, NULL, NULL, NULL);
}


void RenderClass::cleanD3D(void)						// closes Direct3D and releases memory
{
	v_buffer->Release();    // close and release the vertex buffer
	i_buffer->Release();	// close and release the index buffer
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
	
		ID3DXMesh *sphereMesh;
		LPD3DXBUFFER vRemap;
		LPD3DXBUFFER adjacencyBuffer;
		D3DXATTRIBUTERANGE sphereAttribs;


		D3DXCreateSphere(d3ddev, fl_radius, slices, stacks, &sphereMesh, &adjacencyBuffer);

		DWORD arraySize = sphereMesh->GetNumFaces() * 3;

		DWORD * adaj = new DWORD[arraySize];											// Taken from http://ngemu.com/threads/c-setting-the-size-of-array-during-runtime.42522/
		DWORD * optAdaj = new DWORD[arraySize];
		DWORD * fRemap = new DWORD[arraySize];
		
		sphereMesh->GenerateAdjacency(0.1f, adaj);

		sphereMesh->OptimizeInplace(
			D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_IGNOREVERTS,
			adaj,
			optAdaj,
			fRemap,
			&vRemap);

// 		VOID* pVoid;    // a void pointer

		D3DXComputeNormals(sphereMesh, optAdaj);

		sphereMesh->LockVertexBuffer(D3DLOCK_DISCARD, (LPVOID*) &v_buffer);
		sphereMesh->GetVertexBuffer(&v_buffer);
		sphereMesh->LockIndexBuffer(D3DLOCK_DISCARD, (LPVOID*) &i_buffer);
		sphereMesh->GetIndexBuffer(&i_buffer);

		d3ddev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

		for (DWORD i = 0; i < sphereMesh->GetNumFaces(); i++)
		{
			sphereMesh->DrawSubset(0);
		}
		
		// memcpy(&pVoid, &v_buffer, sizeof(sphereMesh->GetNumBytesPerVertex()));
		sphereMesh->UnlockVertexBuffer();
		sphereMesh->UnlockIndexBuffer();
		v_buffer->Unlock();
		i_buffer->Unlock();

		sphereMesh->Release();
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

