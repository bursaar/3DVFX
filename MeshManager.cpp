#include "MeshManager.h"


MeshManager::MeshManager()
{
	meshCount = 0;
}


MeshManager::~MeshManager()
{
}

int MeshManager::AddMesh(MyMeshClass &pMesh)
{
	meshCount += 1;
	cout << "A mesh has been added!" << endl;
	cout << "The current mesh count is: " << meshCount << endl;
	RegisteredMeshes.push_back(&pMesh);
	return meshCount;
}

int MeshManager::GetMeshCount()
{
	cout << "The current mesh count is: " << meshCount << endl;
	return meshCount;
}
