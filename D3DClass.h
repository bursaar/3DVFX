#pragma once
#include <d3dx9.h>
#include "Screen Properties.h"


#ifndef __DEG_TO_RAD
#define __DEG_TO_RAD					// I added an include guard to make sure the const is only ever included once.

const float DEG_TO_RAD = 0.017453292519943295769236907684886f;		// This constant was included in the original LIT material.

#endif


class D3DClass
{
public:

	LPDIRECT3D9 d3d;							// our Direct3D interface
	LPDIRECT3DDEVICE9 d3ddev;					// the device class
	LPDIRECT3DVERTEXBUFFER9 v_buffer;			// the vertex buffer
	LPDIRECT3DINDEXBUFFER9 i_buffer;			// the index buffer
	D3DPRESENT_PARAMETERS d3dpp;				// The present parameters

	float fieldOfView;
	float screenAspect;
	float nearView;
	float farView;

	D3DClass();
	~D3DClass();

	void Initialise(HWND pHWND);					// sets up and initializes Direct3D
	
private:
	D3DXMATRIX mMatWorld;									// A matrix for the world transform
	D3DXMATRIX mMatProjection;							// A matrix for the projection transform
};

