#pragma once
#include "RenderClass.h"
#include "MeshManager.h"

class MyMeshClass
{
public:
	// Matrices for the translation of the mesh
	D3DXMATRIX matScale;											// Scale matrix
	D3DXMATRIX matTranslate;										// Translation matrix
	D3DXMATRIX matRotateZ, matRotateY, matRotateX;					// a matrix to store the rotation for each axis

	ID3DXMesh *mesh;												// Pointer to the mesh object created
	RenderClass *mRenderClass;										// Pointer to the D3D device

	bool worldTransformFlag = false;

	MeshManager *myMeshManager;

	float mRotateX, mRotateY, mRotateZ;									// floats for rotations
	float mTranslateX, mTranslateY, mTranslateZ;						// floats for translations
	float mScaleX, mScaleY, mScaleZ;									// floats for scaling

	void OptimizeMesh();

	void SetScale(float pX, float pY, float pZ);					// Function to set scale of object
	void SetRotation(float pX, float pY, float pZ);					// Function to set rotation of object
	void SetTranslation(float pX, float pY, float pZ);				// Function to set translation of object
	void ApplyWorldTransform();										// Function to apply world transformation to object

	

	MyMeshClass(MeshManager *pMeshManager, ID3DXMesh *pMesh, RenderClass *pRenderClass);	// No default empty constructor, always needs to be passed the current mesh manager, the mesh to populate it with and the LPDIRECT3DDEVICE9.
	~MyMeshClass();
};

