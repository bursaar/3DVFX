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
	D3DXMATRIX matTurn;

	ID3DXMesh *mesh;												// Pointer to the mesh object created
	RenderClass *mRenderClass;										// Pointer to the D3D device

	bool worldTransformFlag = false;

	MeshManager *myMeshManager;

	float *mRotateX = NULL;
	float *mRotateY = NULL;
	float *mRotateZ = NULL;
	
	float *mYaw = NULL;

	float *mTranslateX, *mTranslateY, *mTranslateZ = NULL;						// floats for translations

	float *mScaleX = NULL;
	float *mScaleY = NULL;
	float *mScaleZ = NULL;

	void OptimizeMesh();

	void UpdateMeshParameters(float pSpeed, float pRotation, float pScale = 1.0f);

	MyMeshClass(MeshManager *pMeshManager, ID3DXMesh *pMesh, RenderClass *pRenderClass);	// No default empty constructor, always needs to be passed the current mesh manager, the mesh to populate it with and the LPDIRECT3DDEVICE9.
	~MyMeshClass();


private:
	void SetScale(float &pX, float &pY, float &pZ);					// Function to set scale of object
	void SetRotation(float &pX, float &pY, float &pZ);					// Function to set rotation of object
	void SetTranslation(float &pX, float &pY, float &pZ);				// Function to set translation of object
	void SetTranslation(float &speed);								// Function for forward and backward momentum
	void ApplyWorldTransform();										// Function to apply world transformation to object

	float mDefaultScale = 2.5f;
	float mDefaultRotation = 0.0f;

};

