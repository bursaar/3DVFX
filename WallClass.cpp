#include "WallClass.h"


WallClass::WallClass()
{
}


void WallClass::Initialise(RenderClass * pRenderClass)
{
	// Creating a quad by pushing the vertices to the draw stack.
	vertices.push_back(CUSTOMVERTEX(-1.0f, 1.0f, 0.0f, 0xffffffff, 0.0f, 0.0f));
	vertices.push_back(CUSTOMVERTEX(1.0f, 1.0f, 0.0f, 0xffffffff, 1.0f, 0.0f));
	vertices.push_back(CUSTOMVERTEX(-1.0f, -1.0f, 0.0f, 0xffffffff, 0.0f, 1.0f));
	vertices.push_back(CUSTOMVERTEX(1.0f, -1.0f, 0.0f, 0xffffffff, 1.0f, 1.0f));

	mRenderThis = true;

	mPosition.y = -0.5f;
	mScale.x = 2.0f;
	mScale.y = 2.0f;
	mScale.z = 2.0f;

	RenderableObject::Initialise(pRenderClass);

	SetTexture(TEXT("floor.jpg"));	// Used TEXT macro according to example in Floor.cpp in LIT materials.
}

void WallClass::Update(double deltaTime, double totalTime)
{
	// Call our base class and tell it to update, triggering update on all derived objects
	RenderableObject::Update(deltaTime, totalTime);
}
