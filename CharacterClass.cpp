#include "CharacterClass.h"


CharacterClass::CharacterClass()
{
	translation.x = 0.0f;
	translation.y = 0.0f;
	translation.z = 0.0f;
	rotation.x = 0.0f;
	rotation.y = 0.0f;
	rotation.z = 0.0f;
	scale.x = 1.0f;
	scale.y = 1.0f;
	scale.z = 1.0f;
}


CharacterClass::~CharacterClass()
{
}

void CharacterClass::DrawCharacter()
{
	characterMesh->mesh->DrawSubset(0);
}

void CharacterClass::UpdateCharacter()
{
	UpdateInput();
	
	D3DXMATRIX matScale;
	D3DXMATRIX matTranslate;
	D3DXMATRIX matRotateZ;
	D3DXMATRIX matRotateY;											// a matrix to store the rotation for each object
	D3DXMATRIX matRotateX;

	D3DXMatrixScaling(&matScale, 2.5f, 2.5f, 2.5f);								// Scale object
	D3DXMatrixRotationY(&matRotateY, D3DXToRadian(270));						// Rotate object left and right
	D3DXMatrixRotationX(&matRotateX, speed);										// Rotate object clockwise / counter clock
	D3DXMatrixRotationZ(&matRotateZ, 0.0f);
	D3DXMatrixTranslation(&matTranslate, 0.0f, 0.0f, speed);			// Move object
}

// Check whether there is movement required
void CharacterClass::UpdateInput()
{
	switch (Input.Frame())
	{
	case 12:
		speed -= 0.01f;
		break;
	case 18:
		speed += 0.01f;
		break;
	case 6:
		speed += 0;
		break;
	}
}

void CharacterClass::Frame()
{
	UpdateInput();
	characterMesh->SetRotation(rotation.x, rotation.y, rotation.z);
	characterMesh->SetTranslation(translation.x, translation.y, translation.z * speed);
	characterMesh->ApplyWorldTransform();
	DrawCharacter();
}