#include "MyCameraController.h"


MyCameraController::MyCameraController()
{
	mPosition = t2GNew D3DXVECTOR3;
	mLookAt = t2GNew D3DXVECTOR3;
	mUp = t2GNew D3DXVECTOR3;
	mRotation = t2GNew D3DXVECTOR3;
}

MyCameraController::~MyCameraController()
{
}


bool MyCameraController::SetPosition(float pX, float pY, float pZ)
{
	mPosition = t2GNew D3DXVECTOR3;
	mPosition->x = pX;
	mPosition->y = pY;
	mPosition->z = pZ;
	return true;
}

bool MyCameraController::SetRotation(float pX, float pY, float pZ)
{
	mRotation = t2GNew D3DXVECTOR3;
	mRotation->x = pX;
	mRotation->y = pY;
	mRotation->z = pZ;
	return true;
}

bool MyCameraController::Render()
{
	D3DXVECTOR3 up;
	D3DXVECTOR3 position;
	D3DXVECTOR3 lookAt;
	float radians;

	mUp->x = 0.0f;
	mUp->y = 1.0f;
	mUp->z = 0.0f;

	position.x = mPosition->x;
	position.y = mPosition->y;
	position.z = mPosition->z;

	radians = D3DXToRadian(mRotation->y);

	lookAt.x = sinf(radians) + mPosition->x;
	lookAt.y = mPosition->y;
	lookAt.z = cosf(radians) + mPosition->z;

	// Create view matrix
	D3DXMatrixLookAtLH(&mMatView, &position, &lookAt, &up);

	return true;
}

void MyCameraController::GetViewMatrix(D3DXMATRIX &pViewMatrix)
{
	pViewMatrix = mMatView;
	return;
}