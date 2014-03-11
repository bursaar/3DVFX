#include "MyMeshClass.h"


MyMeshClass::MyMeshClass(MeshManager pMeshManager, ID3DXMesh &pMesh, LPDIRECT3DDEVICE9 pD3ddev)
{
	myMeshManager = &pMeshManager;	// Load a pointer to the mesh manager
	mesh = &pMesh;					// Pass a mesh by reference
	myMeshManager->AddMesh();		// Add a mesh to the mesh manager
	OptimizeMesh();					// Optimise the loaded mesh
	d3ddev = &pD3ddev;				// Load a pointer to the D3D device
}


MyMeshClass::~MyMeshClass()
{
	myMeshManager->RemoveMesh();
}

void MyMeshClass::SetScale(float pX, float pY, float pZ)
{
	mScaleX = pX;
	mScaleY = pY;
	mScaleZ = pZ;
}

void MyMeshClass::SetRotation(float pX, float pY, float pZ)
{
	mRotateX = pX;
	mRotateY = pY;
	mRotateZ = pZ;
}

void MyMeshClass::SetTranslation(float pX, float pY, float pZ)
{
	mTranslateX = pX;
	mTranslateY = pY;
	mTranslateZ = pZ;
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

