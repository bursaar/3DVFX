#pragma once
#include "RenderableObject.h"
class FloorClass :
	public RenderableObject
{
public:
	FloorClass();
	void Initialise(RenderClass *pRenderClass);
	// void Update(double deltaTime, double totalTime);
};

