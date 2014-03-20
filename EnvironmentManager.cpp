#include "Types.h"
#include "Model.h"
#include "CollisionMesh.h"
#include "BillBoardRegion.h"
#include "EnvironmentManager.h"
#include "Environment.h"

/************************************************************************/

DefineSingleton(EnvironmentManager);

/************************************************************************/

EnvironmentManager::EnvironmentManager() :
	m_numModels(0),
        m_numBillboardRegions(0),
	m_collisionMesh(NULL)
{
}

/************************************************************************/

EnvironmentManager::~EnvironmentManager()
{
	for (int index = 0; index < m_numModels; index ++)
	{
		delete m_models[index];
	}

	for (int index = 0; index < m_numBillboardRegions; index ++)
	{
		delete m_billboardRegions[index];
	}

	if (m_collisionMesh)
	{
		delete m_collisionMesh;
	}
}

/************************************************************************/

void
EnvironmentManager::AddModel(const char* ID, const char* fileName, const Vector3D& position, const Vector3D& rotation, float scale, int UVMultiply)
{
	Environment* newModel = new Environment();
	
	assert(m_numModels < c_MaxEnvironmentModels);
	m_models[m_numModels] = newModel;
	m_numModels ++;
	newModel->LoadEnvironment(ID,fileName,position,rotation,scale);
	newModel->SetUVMulitply(UVMultiply);
}

/************************************************************************/

void 
EnvironmentManager::AddCollisionMesh(const char* ID, const char* fileName)
{
	if (m_collisionMesh)
	{
		delete m_collisionMesh;
	}

	Model* temp = new Model(fileName);
	m_collisionMesh = new CollisionMesh();

	m_collisionMesh->SetID(ID);
	m_collisionMesh->SetFileName(fileName);
	Matrix mat;
	MatrixIdentity(&mat);
	m_collisionMesh->AddModelToCollisionMesh(temp, mat);

	delete temp;
}

/************************************************************************/

bool
EnvironmentManager::TestCollision(const Vector3D& lineSrc, const Vector3D& lineDes, Vector3D& intersectionPoint)
{
	if (m_collisionMesh)
	{
		Vector3D normal;
		return m_collisionMesh->LineMeshTest(lineSrc, lineDes, intersectionPoint, normal);
	}
	else
	{
		return false;
	}
}

/************************************************************************/

void 
EnvironmentManager::Render()
{
	for (int i = 0; i < m_numModels; i++)
	{
		m_models[i]->Render();
	}
}

/************************************************************************/

void 
EnvironmentManager::AddBillBoardRegion(BillBoardRegion* billboards)
{
	assert(m_numBillboardRegions < c_MaxBillBoardRegions);
	m_billboardRegions[m_numBillboardRegions] = billboards;
	m_numBillboardRegions ++;
}

/************************************************************************/

CollisionMesh* 
EnvironmentManager::GetCollisionMesh()
{
	return m_collisionMesh;
}

/************************************************************************/
