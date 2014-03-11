#pragma once
#include <d3dx9.h>
#include "MeshManager.h"

class MyMeshClass
{
public:

	D3DXMATRIX matScale;											// Scale matrix
	D3DXMATRIX matTranslate;										// Translation matrix
	D3DXMATRIX matRotateZ, matRotateY, matRotateX;					// a matrix to store the rotation for each axis

	MeshManager *myMeshManager;



	MyMeshClass(MeshManager myMeshManager);							// No default empty constructor, always needs to be passed the current mesh manager.
	~MyMeshClass();
};

