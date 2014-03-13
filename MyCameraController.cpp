#include "MyCameraController.h"


MyCameraController::MyCameraController()
{
}

void MyCameraController::SetRenderClass(RenderClass &pRenderClass)
{
	mRenderClass = &pRenderClass;	// Pass in the render class to a pointer.
}


MyCameraController::~MyCameraController()
{
}

void MyCameraController::SetViewTransform()
{
	// set the view transform
	D3DXMatrixLookAtLH(&mMatView,
		&D3DXVECTOR3(0.0f, 8.0f, 25.0f),						// the camera position
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),							// the look-at position
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));						// the up direction
	mRenderClass->d3ddev->SetTransform(D3DTS_VIEW, &mMatView);  // set the view transform to matView
}

void MyCameraController::SetViewTransform(float pPosX, float pPosY, float pPosZ, float pLookX, float pLookY, float pLookZ)
{
	// set the view transform
	D3DXMatrixLookAtLH(&mMatView,
		&D3DXVECTOR3(pPosX, pPosY, pPosZ),							// the camera position
		&D3DXVECTOR3(pLookX, pLookY, pLookZ),						// the look-at position
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));							// the up direction
	mRenderClass->d3ddev->SetTransform(D3DTS_VIEW, &mMatView);		// set the view transform to matView
}

void MyCameraController::SetProjectionTransform(int pFOV, float pNear, float pFar)
{
	// set the projection transform
	D3DXMatrixPerspectiveFovLH(&mMatProjection,
		D3DXToRadian(FOV),															// the horizontal field of view
		(FLOAT)SCREEN_WIDTH / (FLOAT)SCREEN_HEIGHT,									// aspect ratio
		pNear,																		// the near view-plane
		pFar);																	// the far view-plane
	mRenderClass->d3ddev->SetTransform(D3DTS_PROJECTION, &mMatProjection);			// set the projection
}