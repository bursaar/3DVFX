#include "Scene.h"


Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::Initialise(RenderClass *pRenderClass)
{
	floor = new FloorClass();
	mChildren.push_back(floor);

	RenderableObject::Initialise(pRenderClass);
}