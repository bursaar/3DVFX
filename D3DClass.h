#pragma once
#include <d3dx9.h>
#include "Screen Properties.h"

class D3DClass
{
public:

	LPDIRECT3D9 d3d;							// our Direct3D interface
	LPDIRECT3DDEVICE9 d3ddev;					// the device class
	LPDIRECT3DVERTEXBUFFER9 v_buffer;    // the vertex buffer
	LPDIRECT3DINDEXBUFFER9 i_buffer;		// the index buffer

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

