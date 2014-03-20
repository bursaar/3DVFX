#pragma once
#include "Screen Properties.h"
#include "RenderClass.h"

class MyCameraController
{
public:
	MyCameraController(RenderClass pRenderClass);
	~MyCameraController();

	int FOV = 45;										// The field of view, referenced by the projection transform.
	RenderClass *mRenderClass;							// A pointer to the render class

	D3DXMATRIX mMatView;								// A matrix for the view transform
	D3DXMATRIX mMatProjection;							// A matrix for the projection transform
		
	void SetViewTransform();							// Function to set the view transform
	void SetViewTransform(float pPosX, float pPosY, float pPosZ, float pLookX, float pLookY, float pLookZ);
	void SetProjectionTransform();						// Set the Field of View
};

