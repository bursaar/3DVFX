#pragma once
#include "Screen Properties.h"
#include <d3dx9.h>

class MyCameraController
{
public:
	MyCameraController();
	~MyCameraController();

	D3DXVECTOR3 *mPosition;
	D3DXVECTOR3 *mLookAt;
	D3DXVECTOR3 *mUp;
	D3DXVECTOR3 *mRotation;
	D3DXMATRIX mMatView;								// View matrix

	bool Render();

	bool SetPosition(float pX, float pY, float pZ);
	bool SetRotation(float pX, float pY, float pZ);

	void GetViewMatrix(D3DXMATRIX &pViewMatrix);
};

