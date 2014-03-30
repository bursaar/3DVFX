#include "RenderClass.h"

RenderClass::RenderClass()
{

}

RenderClass::~RenderClass()
{
}

IDirect3DVertexBuffer9 * RenderClass::CreateVertexBuffer(vector<CUSTOMVERTEX> vertices)
{
	IDirect3DVertexBuffer9 * vertexBuffer;

	// Set parameters for the buffer to keep all uses consistent.
	HRESULT result = d3ddev->CreateVertexBuffer(sizeof(CUSTOMVERTEX)* vertices.size(), D3DUSAGE_WRITEONLY, CUSTOMVERTEX::FORMAT, D3DPOOL_DEFAULT, &vertexBuffer, NULL);
	if (result != S_OK)
	{
		OutputDebugStringA("The RenderClass::CreateVertexBuffer method failed at creating a vertex buffer.\n");
	}

	void* bufferMemory;
	vertexBuffer->Lock(0, sizeof(CUSTOMVERTEX)* vertices.size(), &bufferMemory, NULL);
	memcpy(bufferMemory, &vertices[0], sizeof(CUSTOMVERTEX)* vertices.size());
	vertexBuffer->Unlock();

	return vertexBuffer;
}

bool RenderClass::Initialise(HWND phWND)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = phWND;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;		// Changed to match LIT
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.EnableAutoDepthStencil = TRUE;			// automatically run the z-buffer for us
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;		// 16-bit pixel format for the z-buffer


	// create a device class using this information and the info from the d3dpp stuct
	d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		phWND,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,			// Changed from software to match LIT
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

	m_camera = new MyCameraController;
	m_camera->SetViewTransform(d3ddev);
	m_camera->SetPosition(0.0f, 3.0f, 10.0f);


	uvPan = 0;

	D3DXMATRIXA16 projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, fieldOfView, (float)d3dpp.BackBufferWidth / (float)d3dpp.BackBufferHeight, nearView, farView);		//Taken from LIT
	d3ddev->SetTransform(D3DTS_PROJECTION, &projectionMatrix);

	d3ddev->SetFVF(CUSTOMVERTEX::FORMAT);

	return true;
}

void RenderClass::Draw(IDirect3DVertexBuffer9 * vertexBuffer, IDirect3DTexture9 * texture, D3DXVECTOR3 &position, D3DXVECTOR3 &scale, D3DXVECTOR3 &rotation, const D3DXMATRIXA16 & baseMatrix, int verticeCount, IDirect3DIndexBuffer9 * indexbuff, int primCount)
{
	// Check that the minimum number of vertices is enough to make a polygon
	if (verticeCount < 3)
	{
		OutputDebugStringA("Not enough vertices to make a polygon in the Draw method of the renderer.\n");
		return;
	}

	// Create the matrices for the operations to be performed on the vertices
	D3DXMATRIXA16	worldMatrix,
					scaleMatrix,
					translateMatrix,
					rotateMatrixX,
					rotateMatrixY,
					rotateMatrixZ;

	// Update camera position
	m_camera->SetViewTransform(d3ddev);

	// Rotate -> Scale -> Move
	
	// Prepare rotation matrix
	D3DXMatrixRotationX(&rotateMatrixX, (float)rotation.x * DEG_TO_RAD);
	D3DXMatrixRotationY(&rotateMatrixY, (float)rotation.y * DEG_TO_RAD);
	D3DXMatrixRotationZ(&rotateMatrixZ, (float)rotation.z * DEG_TO_RAD);
	D3DXMATRIX matRotate = rotateMatrixX * rotateMatrixY * rotateMatrixZ;

	D3DXVECTOR3 pOutScale;
	D3DXQUATERNION pOutRotation;
	D3DXVECTOR3 pOutTranslation;

	D3DXMatrixTranslation(&translateMatrix, (float)position.x, (float)position.y, (float)position.z);

	D3DXMATRIX m = translateMatrix * baseMatrix;
	m._11 = 1.0;
	m._13 = 0.0;
	m._21 = 0.0;
	m._23 = 0.0;
	m._31 = 0.0;
	m._33 = 1.0;
	D3DXMATRIXA16 neutral;
	
	d3ddev->GetTransform(D3DTS_WORLD, &neutral);

	worldMatrix = neutral * matRotate * *D3DXMatrixScaling(&scaleMatrix, (float)scale.x, (float)scale.y, (float)scale.z) *m;

	// Apply transformation to the world
	d3ddev->SetTransform(D3DTS_WORLD, &worldMatrix);

	// Draw to screen
	// Tell DX that we want to use the built-in vertex buffer
	d3ddev->SetStreamSource(0, vertexBuffer, 0, CUSTOMVERTEX::STRIDE_SIZE);

	// Tell DX which texture to use for this draw operation
	d3ddev->SetTexture(0, texture);
	
	uvPan += 0.0001f;		// NOTE not sure what this is for

	d3ddev->SetVertexShader(NULL);
	d3ddev->SetPixelShader(NULL);

	if (indexbuff == 0)
	{
		// Draw the quad
		d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, verticeCount - 2);
	}
	else
	{
		d3ddev->SetIndices(indexbuff);
		HRESULT result = d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, verticeCount, 0, primCount);	
		if (result != S_OK)
		{
			OutputDebugStringA("Problem with the DrawIndexedPrimitive function in RenderClass::Draw.\n");
		}
	}

	// Reset world translation back to default
	d3ddev->SetTransform(D3DTS_WORLD, &neutral);

}

IDirect3DTexture9 * RenderClass::LoadTexture(LPCWSTR fileName)
{
	wstring path = wstring(fileName);

	// Check to see if the texture has been used before
	if (textureCache.count(fileName) == 0)
	{
		// Load the texture into memory
		IDirect3DTexture9 * texture;
		HRESULT result = D3DXCreateTextureFromFile(d3ddev, fileName, &texture);
		if (result != S_OK)
		{
			OutputDebugStringA("The LoadTexture function in the RenderClass failed to create a texture from a loaded file.\n");
			return nullptr;
		}
		// Put texture into cache so it isn't repeatedly loaded
		textureCache[fileName] = texture;

		// Since this is the first time the texture has been seen, we set the reference count to 1
		textureUsageCount[fileName] = 1;
		return texture;
	}
	else
	{
		// This texture has been loaded before
		// Increase reference count to keep track of how many renderable objects are using this texture
		textureUsageCount[fileName]++;

		// Return previously-loaded texture from cache
		return textureCache[fileName];
	}
}

void RenderClass::BeginFrame()

{
	// Clear the scene
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);

	// Tell device to start drawing
	d3ddev->BeginScene();

}

//Implementation taken from LIT
bool RenderClass::Reset()
{
	HRESULT g = d3ddev->Reset(&d3dpp);

	// If it worked, return true
	return (g == S_OK);
}

bool RenderClass::EndFrame()
{
	// Call end scene on the device
	d3ddev->EndScene();

	// Present back buffer
	HRESULT result = d3ddev->Present(NULL, NULL, NULL, NULL);
	if (result != S_OK)
	{
		if (result == D3DERR_DEVICELOST)
		{
			// Device is lost
			OutputDebugStringA("The render device was lost on the End Frame function of the render class.\n");
			return false;
		}
		else
		{
			// Unhandled error
			OutputDebugStringA("The render device was lost on the End Frame function of the render class and has generated an unhandled error.\n");
			return false;
		}
		// If it all went ok, return true
		return true;

	}

	return true;
}

MyCameraController* RenderClass::GetCameraController()
{
	return m_camera;
}