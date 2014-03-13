#pragma once

#include "MyMeshClass.h"
#include <iostream>

using namespace std;

class MeshManager
{
public:
	vector<MyMeshClass> RegisteredMeshes;
	vector<MyMeshClass>::iterator myIterator;
	vector<MyMeshClass>::const_iterator iter;

	int AddMesh(MyMeshClass &pMesh);
	int GetMeshCount();

	MeshManager();
	~MeshManager();

private:
	int meshCount;
};

