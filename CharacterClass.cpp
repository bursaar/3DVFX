#include "CharacterClass.h"


CharacterClass::CharacterClass()
{
	speed = 0.0f;
	rotationInRadians = 0.0f;
	acceleration = 0.0f;
	location.x = 0.0f;
	location.y = 0.0f;
	location.z = 0.0f;
	friction = 1.0f;
	mKeyUp = false;
	mKeyDown = false;
	mKeyRight = false;
	mKeyLeft = false;

}


CharacterClass::~CharacterClass()
{
}

void CharacterClass::DrawCharacter(IDirect3DVertexBuffer9 *pVbuff, IDirect3DIndexBuffer9 *pIbuff)
{
	characterMesh->LockVertexBuffer(D3DLOCK_DISCARD, (void**)&pVbuff);								// Ref: http://www.gamedev.net/topic/309185-id3dxmeshlockvertexbuffer-method-question/
}

void CharacterClass::UpdateCharacter(int pMovement)
{
	UpdateInput(pMovement);
	UpdateLocation();
}

// Check whether there is movement required
void CharacterClass::UpdateInput(int pMovement)
{
	// Player attributes first - NPC attributes will be derived from this model
	if (speed > 0)
	{
		speed -= friction;		// Trend towards zero with friction variable.
	}
	if (speed < 0)
	{
		speed += friction;		// Trend towards zero with friction variable.
	}

	switch (pMovement)
	{
	case InputClass::BACKWARDRIGHT:
	{
									  speed += acceleration;
									  rotationInRadians -= rotationInRadians;
									  break;
	}
	case InputClass::BACKWARDLEFT:
	{
									 speed += acceleration;
									 rotationInRadians -= rotationInRadians;
									 break;
	}
	case InputClass::FORWARDRIGHT:
	{
									 speed -= acceleration;
									 rotationInRadians += rotationInRadians;
									 break;
	}
	case InputClass::FORWARDLEFT:
	{
									speed -= acceleration;
									rotationInRadians -= rotationInRadians;
									break;
	}
	case InputClass::BACK:
	{
									 speed += acceleration;
									 break;
	}
	case InputClass::FORWARD:
	{
									speed -= acceleration;
									break;
	}
	case InputClass::LEFT:
	{
							 rotationInRadians -= rotationInRadians;
							 break;
	}
	case InputClass::RIGHT:
	{
							  rotationInRadians += rotationInRadians;
							  break;
	}
	}

	// Send data somewhere
}

int CharacterClass::UpdateLocation()
{
	return 0;
}

void CharacterClass::ApplyMesh(ID3DXMesh &pMesh)
{
	characterMesh = &pMesh;
}

void CharacterClass::GetMesh(ID3DXMesh &pMesh)
{
	pMesh = *characterMesh;
}