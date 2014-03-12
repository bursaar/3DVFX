#include "MeshManager.h"


MeshManager::MeshManager()
{
	meshCount = 0;
}


MeshManager::~MeshManager()
{
}

int MeshManager::AddMesh()
{
	meshCount += 1;
	cout << "A mesh has been added!" << endl;
	cout << "The current mesh count is: " << meshCount << endl;
	return meshCount;
}

int MeshManager::GetMeshCount()
{
	cout << "The current mesh count is: " << meshCount << endl;
	return meshCount;
}

int MeshManager::RemoveMesh()
{
	meshCount -= 1;
	cout << "A mesh has been removed!" << endl;
	cout << "The current mesh count is: " << meshCount << endl;
	return meshCount;
}