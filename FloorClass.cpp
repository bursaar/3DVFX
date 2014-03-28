#include "FloorClass.h"


FloorClass::FloorClass()
{

}

void FloorClass::Initialise(RenderClass * pRenderClass)
{
	// Creating a quad by pushing the vertices to the draw stack.
	vertices.push_back(CUSTOMVERTEX(-1.0f, 1.0f, 0.0f, 0xffff00ff, 0.0f, 0.0f));
	vertices.push_back(CUSTOMVERTEX(1.0f, 1.0f, 0.0f, 0xffffff00, 1.0f, 0.0f));
	vertices.push_back(CUSTOMVERTEX(-1.0f, -1.0f, 0.0f, 0xff00ffff, 0.0f, 1.0f));
	vertices.push_back(CUSTOMVERTEX(1.0f, -1.0f, 0.0f, 0xfffff00f, 1.0f, 1.0f));

	mRenderThis = true;

	mRotation.x = 90.0f;
	mPosition.y = -0.5f;
	mScale.x = 20.0f;
	mScale.y = 20.0f;
	mScale.z = 20.0f;

	RenderableObject::Initialise(pRenderClass);

	SetTexture(TEXT("../floor.jpg"));	// Used TEXT macro according to example in Floor.cpp in LIT materials.


}