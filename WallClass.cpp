#include "WallClass.h"


WallClass::WallClass()
{
	// Creating a quad by pushing the vertices to the draw stack.
	vertices.push_back(CUSTOMVERTEX(-1.0f, 1.0f, 0.0f, 0xffff00ff, 0.0f, 0.0f));
	vertices.push_back(CUSTOMVERTEX(1.0f, 1.0f, 0.0f, 0xffffff00, 0.0f, 0.0f));
	vertices.push_back(CUSTOMVERTEX(-1.0f, -1.0f, 0.0f, 0xff00ffff, 0.0f, 0.0f));
	vertices.push_back(CUSTOMVERTEX(1.0f, -1.0f, 0.0f, 0xff00ffff, 0.0f, 0.0f));

	mPosition.y = -0.5f;
	mPosition.x = 1.0f;		// Need a non-zero value for the multiplication part of tiling.
	mPosition.z = 1.0f;		// Need a non-zero value for the multiplication part of tiling.
	mPosition.y = -19.9f;
	mScale.x = 5.0f;
	mScale.y = 20.0f;
	mScale.z = 5.0f;
}

void WallClass::Block(RenderableObject *pObject)
{

}


void WallClass::Initialise(RenderClass * pRenderClass)
{

	mRenderThis = true;

	RenderableObject::Initialise(pRenderClass);

	// SetTexture(TEXT("floor.jpg"));	// Used TEXT macro according to example in Floor.cpp in LIT materials.
}

void WallClass::Update(double deltaTime, double totalTime)
{
	// Call our base class and tell it to update, triggering update on all derived objects
	RenderableObject::Update(deltaTime, totalTime);
}
