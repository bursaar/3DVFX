#pragma once
#include <d3dx9.h>
#include "MeshManager.h"

class MyMeshClass
{
public:
	// Matrices for the translation of the mesh
	D3DXMATRIX matScale;											// Scale matrix
	D3DXMATRIX matTranslate;										// Translation matrix
	D3DXMATRIX matRotateZ, matRotateY, matRotateX;					// a matrix to store the rotation for each axis

	ID3DXMesh *mesh;												// Pointer to the mesh object created
	LPDIRECT3DDEVICE9 *d3ddev;										// Pointer to the D3D device

	MeshManager *myMeshManager;

	float mRotateX, mRotateY, mRotateZ;									// floats for rotations
	float mTranslateX, mTranslateY, mTranslateZ;						// floats for translations
	float mScaleX, mScaleY, mScaleZ;									// floats for scaling

	void OptimizeMesh();

	void SetScale(float pX, float pY, float pZ);
	void SetRotation(float pX, float pY, float pZ);
	void SetTranslation(float pX, float pY, float pZ);

	MyMeshClass(MeshManager myMeshManager, ID3DXMesh &pMesh, LPDIRECT3DDEVICE9 pD3ddev);	// No default empty constructor, always needs to be passed the current mesh manager, the mesh to populate it with and the LPDIRECT3DDEVICE9.
	~MyMeshClass();
};

