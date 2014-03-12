#include "MyMeshClass.h"


MyMeshClass::MyMeshClass(MeshManager *pMeshManager, ID3DXMesh *pMesh, RenderClass *pRenderClass)
{
	
	myMeshManager = new MeshManager (*pMeshManager);			// Load a pointer to the mesh manager
	mesh = pMesh;							// Pass a mesh by reference
	myMeshManager->AddMesh();				// Add a mesh to the mesh manager
	OptimizeMesh();							// Optimise the loaded mesh
	mRenderClass = pRenderClass;			// Load a pointer to the render class
	mRotateX = new float (0.0f);
	mRotateY = new float (0.0f);
	mRotateZ = new float(0.0f);
	mScaleX = new float (0.0f);
	mScaleY = new float(0.0f);
	mScaleZ = new float(0.0f);
	mTranslateX = new float(0.0f);
	mTranslateY = new float(0.0f);
	mTranslateZ = new float(0.0f);
}


MyMeshClass::~MyMeshClass()
{
	myMeshManager->RemoveMesh();
}

void MyMeshClass::SetScale(float &pX, float &pY, float &pZ)
{
	mScaleX = &pX;
	mScaleY = &pY;
	mScaleZ = &pZ;
	D3DXMatrixScaling(&matScale, *mScaleX, *mScaleY, *mScaleZ);
}

void MyMeshClass::SetRotation(float &pX, float &pY, float &pZ)
{
	mRotateX = &pX;									// Float to rotate by (in radians)
	D3DXMatrixRotationX(&matRotateX, *mRotateX);		// Place rotation calculation in matrix.
	mRotateY = &pY;									// Float to rotate by (in radians)
	D3DXMatrixRotationY(&matRotateY, *mRotateY);		// Place rotation calculation in matrix.
	mRotateZ = &pZ;									// Float to rotate by (in radians)
	D3DXMatrixRotationZ(&matRotateZ, *mRotateZ);		// Place rotation calculation in matrix.
}

void MyMeshClass::SetTranslation(float &pX, float &pY, float &pZ)
{
	mTranslateX = &pX;								// Float to translate in the X axis
	mTranslateY = &pY;								// Float to translate in the Y axis
	mTranslateZ = &pZ;								// Float to translate in the Z axis
	D3DXMatrixTranslation(&matTranslate, *mTranslateX, *mTranslateY, *mTranslateZ);		// Place translation calculation in matrix
}

void MyMeshClass::SetTranslation(float &speed)
{
	mTranslateZ = &speed;																// Float to translate in the Z axis
	D3DXMatrixTranslation(&matTranslate, *mTranslateX, *mTranslateY, *mTranslateZ);		// Place translation calculation in matrix
}

void MyMeshClass::OptimizeMesh()
{
	DWORD arraySize = mesh->GetNumFaces() * 3;
	DWORD * adaj = new DWORD[arraySize];											// Taken from http://ngemu.com/threads/c-setting-the-size-of-array-during-runtime.42522/
	DWORD * optAdaj = new DWORD[arraySize];
	DWORD * fRemap = new DWORD[arraySize];
	LPD3DXBUFFER vRemap;
	
	mesh->GenerateAdjacency(0.1f, adaj);

	mesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_IGNOREVERTS,
		adaj,
		optAdaj,
		fRemap,
		&vRemap);
}

void MyMeshClass::ApplyWorldTransform()
{
	mRenderClass->d3ddev->SetTransform(D3DTS_WORLD, 
		&(matRotateX
		* matRotateY
		* matRotateZ
		* matScale
		* matTranslate));
}

void MyMeshClass::UpdateMeshParameters(float pSpeed, float pRotation, float pScale)
{
	bool changeFlag = false;

	if (pScale)
	{
		SetScale(mDefaultScale, pScale, mDefaultScale);
		changeFlag = true;
	}
	if (pRotation)
	{
		SetRotation(mDefaultRotation, pRotation, mDefaultRotation);
		changeFlag = true;
	}
	if (pSpeed)
	{
		SetTranslation(pSpeed);
		changeFlag = true;
	}
	if (changeFlag)
	{
		ApplyWorldTransform();
	}
}