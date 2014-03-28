#include "FloorClass.h"


FloorClass::FloorClass()
{
	mRotation.x = 90.0f;
	mPosition.y = -0.5f;
	mScale.x = 20.0f;
	mScale.y = 20.0f;
	mScale.z = 20.0f;
}

void FloorClass::InitialiseFloor(RenderClass *pRenderClass)
{
	RenderableObject::Initialise(pRenderClass);

	// SetTexture(TEXT("../floor.jpg"));	// Used TEXT macro according to example in Floor.cpp in LIT materials.
}
