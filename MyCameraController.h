#pragma once
#include "Screen Properties.h"
#include <d3dx9.h>

#ifndef __DEG_TO_RAD
#define __DEG_TO_RAD					// I added an include guard to make sure the const is only ever included once.

const float DEG_TO_RAD = 0.017453292519943295769236907684886f;		// This constant was included in the original LIT material.

#endif

class MyCameraController
{
public:
	MyCameraController();
	~MyCameraController();

	
	void Follow(void * player);							// LIT

	bool SetPosition(float pX, float pY, float pZ);
	bool SetRotation(float angle);
	void SetViewTransform(IDirect3DDevice9 * pDevice);	// LIT

	void Move(float px, float py, float pz);			// LIT
	void Rotate(float angle);							// LIT

private:
	D3DXVECTOR3 mPosition;
	D3DXVECTOR3 mLookAt;
	D3DXVECTOR3 mUp;

	// vvvvv These private member variables were taken from the Train2Game LIT materials' camera class
	VOID *followTarget;
	float x, y, z, rotateYaw;
	D3DXMATRIXA16 viewMatrix;
};

