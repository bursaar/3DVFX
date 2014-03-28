#pragma once
#include "RenderableObject.h"
class QuadClass :
	public RenderableObject
{
public:
	QuadClass();
	~QuadClass();
	void Initialise(RenderClass * pRenderClass);
};

