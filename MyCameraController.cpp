#include "MyCameraController.h"
#include "RenderableObject.h"


MyCameraController::MyCameraController()
{
	mPosition = new D3DXVECTOR3;
	mLookAt = new D3DXVECTOR3;
	mUp = new D3DXVECTOR3;
	mRotation = new D3DXVECTOR3;

	// Set where the camera begins
	mPosition->x = 0.0f;
	mPosition->y = 0.0f;
	mPosition->z = -5.0f;

	// Set where the camera is pointed
	mLookAt->x = 0.0f;
	mLookAt->y = 0.0f;
	mLookAt->z = 1.0f;

	// Set the camera's up direction
	mUp->x = 0.0f;
	mUp->y = 1.0f;
	mUp->z = 0.0f;
}

void MyCameraController::Follow(void *player)
{
	followTarget = new RenderableObject;
	followTarget = player;
}

MyCameraController::~MyCameraController()
{
}


bool MyCameraController::SetPosition(float pX, float pY, float pZ)
{
	mPosition = new D3DXVECTOR3;
	mPosition->x = pX;
	mPosition->y = pY;
	mPosition->z = pZ;
	return true;
}

bool MyCameraController::SetRotation(float pX, float pY, float pZ)
{
	mRotation = new D3DXVECTOR3;
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

	// Create projection matrix
	D3DXMatrixPerspectiveFovLH(&mMatProj, D3DXToRadian(45), SCREEN_HEIGHT / SCREEN_WIDTH, 1.0f, 500.0f);

	return true;
}

void MyCameraController::GetViewMatrix(D3DXMATRIX &pViewMatrix)
{
	pViewMatrix = mMatView;
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
		D3DXMatrixLookAtLH(&viewMatrix, mPosition, mLookAt, mUp);

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