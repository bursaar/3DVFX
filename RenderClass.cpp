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
	HRESULT result = m_D3D->d3ddev->CreateVertexBuffer(sizeof(CUSTOMVERTEX)* vertices.size(), D3DUSAGE_WRITEONLY, CUSTOMVERTEX::FORMAT, D3DPOOL_DEFAULT, &vertexBuffer, NULL);
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
	m_D3D = new D3DClass;
	m_D3D->Initialise(phWND);

	m_camera = new MyCameraController;
	m_camera->SetPosition(0.0f, 3.0f, 10.0f);
	m_camera->Render();
	m_camera->GetViewMatrix(m_viewMatrix);

	uvPan = 0;

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
	m_camera->SetViewTransform(m_D3D->d3ddev);

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
	
	m_D3D->d3ddev->GetTransform(D3DTS_WORLD, &neutral);

	worldMatrix = neutral * matRotate * *D3DXMatrixScaling(&scaleMatrix, (float)scale.x, (float)scale.y, (float)scale.z) *m;

	// Apply transformation to the world
	m_D3D->d3ddev->SetTransform(D3DTS_WORLD, &neutral);

	// Draw to screen
	// Tell DX that we want to use the built-in vertex buffer
	m_D3D->d3ddev->SetStreamSource(0, vertexBuffer, 0, CUSTOMVERTEX::STRIDE_SIZE);

	// Tell DX which texture to use for this draw operation
	m_D3D->d3ddev->SetTexture(0, texture);

	uvPan += 0.0001f;		// NOTE not sure what this is for

	// Creating a perspective projection
	D3DXMATRIXA16 projectionMatrix;
	D3DXMatrixPerspectiveFovLH(
		&projectionMatrix,						// Pass in projection matrix by reference to be filled in
		45 * DEG_TO_RAD,						// Height of the field of view
		SCREEN_HEIGHT / SCREEN_WIDTH,			// Aspect ratio is height divided by width
		0.5f,									// The distance to the near-view plane
		100.0f									// The distance to the far-view plane
		);

	m_D3D->d3ddev->SetTransform(D3DTS_PROJECTION, &projectionMatrix);

	// Disable lighting (for now)
	m_D3D->d3ddev->SetRenderState(D3DRS_LIGHTING, false);

	// Set our vertex format
	m_D3D->d3ddev->SetFVF(CUSTOMVERTEX::FORMAT);

	// Set culling mode
	m_D3D->d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);		// Show both sides of each polygon.
	// m_D3D->d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);		// Cull any polygons drawn with their backs to us.
}

IDirect3DTexture9 * RenderClass::LoadTexture(LPCWSTR fileName)
{
	wstring path = wstring(fileName);

	// Check to see if the texture has been used before
	if (textureCache.count(fileName) == 0)
	{
		// Load the texture into memory
		IDirect3DTexture9 * texture;
		HRESULT result = D3DXCreateTextureFromFile(m_D3D->d3ddev, fileName, &texture);
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
	m_D3D->d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);

	// Tell device to start drawing
	m_D3D->d3ddev->BeginScene();

}

//Implementation taken from LIT
bool RenderClass::Reset()
{
	HRESULT g = m_D3D->d3ddev->Reset(&m_D3D->d3dpp);

	// If it worked, return true
	return (g == S_OK);
}

bool RenderClass::EndFrame()
{
	// Call end scene on the device
	m_D3D->d3ddev->EndScene();

	// Present back buffer
	HRESULT result = m_D3D->d3ddev->Present(NULL, NULL, NULL, NULL);
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
		}
		// If it all went ok, return true
		return true;

	}

}