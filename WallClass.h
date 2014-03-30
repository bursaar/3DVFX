#pragma once
#include "RenderableObject.h"
class WallClass :
	public RenderableObject
{
public:
	void Initialise(RenderClass *pRenderClass);
	void Update(double deltaTime, double totalTime);
	WallClass();
};

