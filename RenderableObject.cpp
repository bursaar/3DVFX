#include "RenderableObject.h"


RenderableObject::RenderableObject()
{
	// NOTES: I didn't see why the vertex struct was so useful, and I wanted to demonstrate
	// my own understanding of the system, hence my more manual implementation.

	// Initialise and zero out:
	// Position
	mPosition.x = 0.0f;
	mPosition.y = 0.0f;
	mPosition.z = 0.0f;
	// Velocity
	mVelocity.x = 0.0f;
	mVelocity.y = 0.0f;
	mVelocity.z = 0.0f;
	// Scale
	mScale.x = 1.0f;
	mScale.y = 1.0f;
	mScale.z = 1.0f;
	// Rotation
	mRotation.x = 0.0f;
	mRotation.y = 0.0f;
	mRotation.z = 0.0f;
	// Radius
	radius = 0.0f;

	// Set the flags to false
	mRenderThis = false;
	initialised = false;
	collidable = false;
	
	// Zero out the facecount
	facecount = 0;

	// Set the pointers to vertex and index buffers and the texture all to null pointers.
	mVertexBuffer = nullptr;
	mIndexBuffer = nullptr;
	mTexture = nullptr;

	// Clear out the mChildren vector.
	mChildren.clear();
}


RenderableObject::~RenderableObject()
{
}


void RenderableObject::Release()
{
	if (mVertexBuffer != nullptr)
	{
		mVertexBuffer->Release();
		mVertexBuffer = nullptr;
	}

	if (mTexture != nullptr)
	{
		mTexture->Release();
		mTexture = nullptr;
	}

	if (mIndexBuffer != nullptr)
	{
		mIndexBuffer->Release();
		mIndexBuffer = nullptr;
	}

	// Iterate through stack of children and release their resources
	for (
		vector<RenderableObject *>::iterator iter = mChildren.begin();	// Create an iterator 
		iter != mChildren.end();										// While that iterator is not one after the last element
		iter++															// Increment the iterator
		)
	{
		RenderableObject * object = *iter;			// Create a pointer to a renderable object called object and pass it the contents at the current position of the iterator
		object->Release();							// Release that object
	}
}

void RenderableObject::Initialise(RenderClass * pRenderClass)
{
	// Store render locally
	mRenderer = pRenderClass;

	// If it needs to be rendered...
	if (mRenderThis)
	{
		// Create the vertex buffer
		mVertexBuffer = pRenderClass->CreateVertexBuffer(vertices);
	}

	// If the children should be initialised, then initialise them
	for (
		vector<RenderableObject *>::iterator iter = mChildren.begin();
		iter != mChildren.end();
		iter++
		)
	{
		RenderableObject * object = *iter;
		object->Initialise(pRenderClass);
	}

		// Make sure we're not initialised again
		initialised = true;

}

void RenderableObject::Update(double deltaTime, double totalTime)
{
	// Check that we've been initialised
	if (!initialised)
	{
		OutputDebugStringA("Renderable object is being updated without being initialised!\n");
		return;
	}

	// Update all active children
	for (
		vector<RenderableObject *> ::iterator iter = mChildren.begin();
		iter != mChildren.end();
		iter++
		)
	{
		RenderableObject * object = *iter;
		object->Update(deltaTime, totalTime);
	}
}

void RenderableObject::Render(const D3DXMATRIXA16 & baseMatrix)
{
	//If not yet initialised
	if (!initialised)
	{
		OutputDebugStringA("RenderableObject::Render tried to render an object that was not yet initialised\n");
		return;
	}

	// If the object is flagged to be drawn
	if (mRenderThis)
	{
		// Get renderer to draw object
		mRenderer->Draw(mVertexBuffer, mTexture, mPosition, mScale, mRotation, baseMatrix, vertices.size(), mIndexBuffer, facecount);
	}
}

void RenderableObject::GetPosition(double &px, double &py, double &pz)
{
	px = mPosition.x;
	py = mPosition.y;
	pz = mPosition.z;
}

double RenderableObject::GetRotateY()
{
	return (double)mRotation.y;
}

void RenderableObject::SetTexture(LPCWSTR fileName)
{
	// Load the texture
	mTexture = mRenderer->LoadTexture(fileName);

	// Store name of texture
	mTextureName = wstring(fileName);
}

void RenderableObject::Resume()
{
	// If there is rendering to be done, recreate the vertex buffer
	if (mRenderThis)
	{
		mVertexBuffer = mRenderer->CreateVertexBuffer(vertices);
	}

	// If there's a texture name set, reload texture
	if (!mTextureName.empty())
	{
		mTexture = mRenderer->LoadTexture(mTextureName.c_str());
	}

	// Iterate through the children and tell them to reload their resources as well
	for (
		vector<RenderableObject *>::iterator iter = mChildren.begin();
		iter != mChildren.end();
	iter++
		)
	{
		RenderableObject * object = *iter;
		object->Resume();
	}
}

void RenderableObject::Move(float pX, float pY, float pZ)
{
	// Translate the movement to match camera direction
	D3DXVECTOR3 translationVector(pX, pY, pZ);
	D3DXMATRIX matRotateY;
	D3DXMatrixRotationY(&matRotateY, (0 - (float)mRotation.y) * DEG_TO_RAD);
	D3DXVec3TransformCoord(&translationVector, &translationVector, &matRotateY);

	mPosition.x += translationVector.x;
	mPosition.y += translationVector.y;
	mPosition.z += translationVector.z;
}