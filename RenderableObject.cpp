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