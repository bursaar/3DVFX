#pragma once

#include <iostream>

using namespace std;

class MeshManager
{
public:


	int AddMesh();
	int GetMeshCount();
	int RemoveMesh();

	MeshManager();
	~MeshManager();

private:
	int meshCount;
};

