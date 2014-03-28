#pragma once
#include "Screen Properties.h"
#include <d3dx9.h>

#ifndef __DEG_TO_RAD
#define __DEG_TO_RAD					// Include guard to make sure the const is only ever included once.

const float DEG_TO_RAD = 0.017453292519943295769236907684886f;		// This constant was included in the original LIT material.

#endif

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
	D3DXMATRIX mMatProj;								// Projection matrix

	bool Render();

	bool SetPosition(float pX, float pY, float pZ);
	bool SetRotation(float pX, float pY, float pZ);

	void GetViewMatrix(D3DXMATRIX &pViewMatrix);
	void GetProjectionMatrix(D3DXMATRIX &pProjMatrix);
};

