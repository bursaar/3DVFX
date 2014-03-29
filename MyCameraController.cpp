#include "MyCameraController.h"
#include "RenderableObject.h"


MyCameraController::MyCameraController()
{

	// Set where the camera begins
	mPosition.x = 0.0f;
	mPosition.y = 0.0f;
	mPosition.z = -5.0f;

	// Set where the camera is pointed
	mLookAt.x = 0.0f;
	mLookAt.y = 0.0f;
	mLookAt.z = 1.0f;

	// Set the camera's up direction
	mUp.x = 0.0f;
	mUp.y = 1.0f;
	mUp.z = 0.0f;
}

void MyCameraController::Follow(void *player)
{
	followTarget = player;
}

MyCameraController::~MyCameraController()
{
}


bool MyCameraController::SetPosition(float pX, float pY, float pZ)
{
	mPosition.x = pX;
	mPosition.y = pY;
	mPosition.z = pZ;
	return true;
}

bool MyCameraController::SetRotation(float pX, float pY, float pZ)
{
	mRotation.x = pX;
	mRotation.y = pY;
	mRotation.z = pZ;
	return true;
}

void MyCameraController::GetViewMatrix(D3DXMATRIX &pViewMatrix)
{
	pViewMatrix = viewMatrix;
	return;
}

void MyCameraController::GetProjectionMatrix(D3DXMATRIX &pProjMatrix)
{
	pProjMatrix = mMatProj;
	return;
}

// This implementation is based on the Train2Game LIT material
void MyCameraController::SetViewTransform(IDirect3DDevice9 * pDevice)
{
	// Create matrices for...
	D3DXMATRIX
		matRotateY,		//...rotation in the Y axis
		matTranslate,	//...translation
		imatRotateY;	//...inverse rotation in the Y axis

	if (followTarget != nullptr)
	{
		D3DXMatrixLookAtLH(&viewMatrix, &mPosition, &mLookAt, &mUp);

		// Apply object position as a transform
		D3DXMATRIX followTranslate;
		RenderableObject * target = (RenderableObject *)followTarget;

		double tx, ty, tz;

		target->GetPosition(tx, ty, tz);

		D3DXMatrixTranslation(&followTranslate, 0.0f - float(tx), 0.0f - (float)ty, 0.0f - (float)tz);
		D3DXMATRIX transformedCamera = viewMatrix * followTranslate;

		double tr = target->GetRotateY();
		D3DXMatrixRotationY(&matRotateY, (0.0f - (float)tr) * DEG_TO_RAD);
		D3DXMatrixRotationY(&imatRotateY, ((float)tr) * DEG_TO_RAD);

		D3DXVECTOR3 offset(0.0f, 1.0f, -5.0f);

		// Calculate camera offset from target
		D3DXVec3TransformCoord(&offset, &offset, &matRotateY);

		D3DXMATRIX offsetTranslate;
		D3DXMatrixTranslation(&offsetTranslate, 0 - offset.x, 0 - offset.y, 0 - offset.z);

		D3DXMATRIX relativeOffset = offsetTranslate * imatRotateY;
		D3DXMATRIX position = transformedCamera * relativeOffset;

		pDevice->SetTransform(D3DTS_VIEW, &position);
	}
	else
	{
		D3DXMatrixRotationY(&matRotateY, rotateYaw * DEG_TO_RAD);
		D3DXMATRIX transformedCamera = matTranslate * matRotateY * viewMatrix;
		pDevice->SetTransform(D3DTS_VIEW, &transformedCamera);
	}
}

void MyCameraController::Move(float px, float py, float pz)
{
	//Translate the movement coordinates to match camera direction
	D3DXVECTOR3 translationVector(px, py, pz);
	D3DXMATRIX matRotateY;
	D3DXMatrixRotationY(&matRotateY, (0 - rotateYaw) * DEG_TO_RAD);
	D3DXVec3TransformCoord(&translationVector, &translationVector, &matRotateY);

	x += translationVector.x;
	y += translationVector.y;
	z += translationVector.z;
}

void MyCameraController::Rotate(float angle)
{
	rotateYaw += angle;
}