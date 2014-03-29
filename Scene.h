#pragma once
#include "RenderableObject.h"
#include "FloorClass.h"
class Scene :
	public RenderableObject
{
public:
	void Initialise(RenderClass* pRenderClass) override;
	Scene();
	~Scene();

private:
	FloorClass *floor;
};

