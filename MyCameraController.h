#pragma once
#include "Screen Properties.h"
#include "RenderClass.h"

class MyCameraController
{
public:
	MyCameraController(RenderClass pRenderClass);
	~MyCameraController();

	int FOV = 45;
	LPDIRECT3DDEVICE9 *d3ddev;						// Pointer to Direct3D Device

	void SetWorldTransform();
	void SetViewTransform();
	void SetProjectionTransform();
};

