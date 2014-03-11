#include "MyCameraController.h"


MyCameraController::MyCameraController(RenderClass pRenderClass)
{
	mD3ddev = &pRenderClass.d3ddev;
}


MyCameraController::~MyCameraController()
{
}

void MyCameraController::SetProjectionTransform()
{
	// set the projection transform
	D3DXMATRIX matProjection;										// the projection transform matrix
	D3DXMatrixPerspectiveFovLH(&matProjection,
		D3DXToRadian(45),											// the horizontal field of view
		(FLOAT)SCREEN_WIDTH / (FLOAT)SCREEN_HEIGHT,					// aspect ratio
		1.0f,														// the near view-plane
		100.0f);													// the far view-plane
	(*mD3ddev)->SetTransform(D3DTS_PROJECTION, &matProjection);			// set the projection
}