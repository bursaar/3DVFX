#include "windows.h"
#include "Types.h"
#include "SkinnedMesh.h"
#include "Model.h"
#include "ModelManager.h"

/*****************************************************************************************/

DefineSingleton(ModelManager);

/*****************************************************************************************/

ModelManager::ModelManager() :	
	m_numMeshes(0),
	m_numStaticMeshes(0)
{
}

/*****************************************************************************************/

ModelManager::~ModelManager()
{
	for (int index = 0; index < m_numStaticMeshes; index ++)
	{
		delete m_staticMeshes[index];
	}

	for (int index = 0; index < m_numMeshes; index ++)
	{
		delete m_meshes[index];
	}
}

/*****************************************************************************************/

void
ModelManager::CreateModel(const char* ID, const char* fileName, float scale)
{
	assert(m_numMeshes < c_MaxMeshCount);
	
	ObjectModel* newModel = new ObjectModel;
	
	m_meshes[m_numMeshes] = newModel;
	m_numMeshes ++;

	newModel->m_ID = ID;
	newModel->m_fileName = fileName;
	newModel->m_mesh = new SkinnedMesh();
	newModel->m_mesh->Load(fileName);
	newModel->m_scale = scale;

}

/*****************************************************************************************/

void 
ModelManager::CreateMesh(const char* ID, const char* fileName, float scale)
{
	assert(m_numStaticMeshes < c_MaxStaticMeshCount);

	StaticModel* newModel = new StaticModel;
	
	m_staticMeshes[m_numStaticMeshes] = newModel;
	m_numStaticMeshes ++;
	
	newModel->m_ID = ID;
	newModel->m_fileName = fileName;
	newModel->m_mesh = new Model();
	newModel->m_mesh->LoadModel(fileName);
	newModel->m_scale = scale;
	newModel->m_mesh->SetScale(scale);
}

/*****************************************************************************************/

SkinnedMesh*
ModelManager::GetSkinnedMeshPointer(const char *ID)
{
	for (int i = 0; i < m_numMeshes; i++)
	{
		if(_stricmp(m_meshes[i]->m_ID,ID)==0)
		{
			return m_meshes[i]->m_mesh;
		}
	}
	return 0;
}

/*****************************************************************************************/

Model* 
ModelManager::GetStaticMeshPointer(const char* ID)
{
	for (int i = 0; i < m_numStaticMeshes; ++i)
	{
		if(_stricmp(m_staticMeshes[i]->m_ID,ID)==0)
		{
			return m_staticMeshes[i]->m_mesh;
		}
	}
	return 0;
}

/*****************************************************************************************/

float
ModelManager::GetSkinnedMeshScale(const char *ID)
{
	for (int i = 0; i < m_numMeshes; i++)
	{
		if(_stricmp(m_meshes[i]->m_ID,ID)==0)
		{
			return m_meshes[i]->m_scale;
		}
	}
	return 0;
}

/*****************************************************************************************/

int 
ModelManager::GetObjectModelCount()
{
	return m_numMeshes;
}

/*****************************************************************************************/

int 
ModelManager::GetStaticModelCount()
{
	return m_numStaticMeshes;
}

/*****************************************************************************************/

ObjectModel* 
ModelManager::GetObjectModel(int index)
{
	if(index < m_numMeshes)
	{
		return m_meshes[index];
	}
	return NULL;
}

/*****************************************************************************************/

ObjectModel*
ModelManager::GetObjectModel(SkinnedMesh* mesh)
{
	for (int index=0; index<m_numMeshes; index++)
	{
		if(m_meshes[index]->m_mesh == mesh)
		{
			return m_meshes[index];
		}
	}
	return NULL;
}

/*****************************************************************************************/

ObjectModel*
ModelManager::GetObjectModel(const char* id)
{
	for (int index=0; index<m_numMeshes; index++)
	{
		if(_stricmp(m_meshes[index]->m_ID, id) == 0)
		{
			return m_meshes[index];
		}
	}
	
	return NULL;
}

/*****************************************************************************************/

StaticModel* 
ModelManager::GetStaticModel(int index)
{
	if(index < m_numStaticMeshes)
	{
		return m_staticMeshes[index];
	}
	return NULL;
}

/*****************************************************************************************/

StaticModel* 
ModelManager::GetStaticModel(Model* model)
{
	for (int index=0; index < m_numStaticMeshes; index++)
	{
		if(m_staticMeshes[index]->m_mesh == model)
		{
			return m_staticMeshes[index];
		}
	}
	return NULL;
}

/*****************************************************************************************/

StaticModel* 
ModelManager::GetStaticModel(const char* id)
{
	for (int index=0; index < m_numStaticMeshes; index++)
	{
		if(_stricmp(m_staticMeshes[index]->m_ID,id) == 0)
		{
			return m_staticMeshes[index];
		}
	}
	return NULL;
}

/*****************************************************************************************/
