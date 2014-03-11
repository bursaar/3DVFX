#include "MyMeshClass.h"


MyMeshClass::MyMeshClass(MeshManager pMeshManager)
{
	myMeshManager = &pMeshManager;
	myMeshManager->AddMesh();
}


MyMeshClass::~MyMeshClass()
{
	myMeshManager->RemoveMesh();
}
