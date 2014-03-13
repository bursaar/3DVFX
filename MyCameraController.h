#pragma once
#include "Screen Properties.h"
#include "RenderClass.h"

class MyCameraController
{
public:
	MyCameraController();
	~MyCameraController();

	int FOV = 45;										// The field of view, referenced by the projection transform.
	RenderClass *mRenderClass;							// A pointer to the render class

	D3DXMATRIX mMatView;								// A matrix for the view transform
	D3DXMATRIX mMatProjection;							// A matrix for the projection transform

	void SetRenderClass(RenderClass &pRenderClass);
	void SetViewTransform();							// Function to set the view transform
	void SetViewTransform(float pPosX, float pPosY, float pPosZ, float pLookX, float pLookY, float pLookZ);
	void SetProjectionTransform(int pFOV = 45, float pNear = 1.0, float pFar = 100.0);
};

