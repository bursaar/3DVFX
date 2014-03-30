#include "FloorClass.h"


FloorClass::FloorClass()
{
	// Creating a quad by pushing the vertices to the draw stack.
	vertices.push_back(CUSTOMVERTEX(-1.0f, 1.0f, 0.0f, 0xffffffff, 0.0f, 0.0f));
	vertices.push_back(CUSTOMVERTEX(1.0f, 1.0f, 0.0f, 0xffffffff, 1.0f, 0.0f));
	vertices.push_back(CUSTOMVERTEX(-1.0f, -1.0f, 0.0f, 0xffffffff, 0.0f, 1.0f));
	vertices.push_back(CUSTOMVERTEX(1.0f, -1.0f, 0.0f, 0xffffffff, 1.0f, 1.0f));

	mRotation.x = 90.0f;
	mPosition.y = -0.5f;
	mPosition.x = 1.0f;		// Need a non-zero value for the multiplication part of tiling.
	mPosition.z = 1.0f;		// Need a non-zero value for the multiplication part of tiling.
	mScale.x = 20.0f;
	mScale.y = 20.0f;
	mScale.z = 20.0f;
}

void FloorClass::Initialise(RenderClass * pRenderClass)
{
	mRenderThis = true;

	RenderableObject::Initialise(pRenderClass);

	SetTexture(TEXT("floor.jpg"));	// Used TEXT macro according to example in Floor.cpp in LIT materials.
}


void FloorClass::Update(double deltaTime, double totalTime)
{
	// Call our base class and tell it to update, triggering update on all derived objects
	RenderableObject::Update(deltaTime, totalTime);
}
