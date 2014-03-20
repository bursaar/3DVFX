#include "Types.h"
#include "MyFileReader.h"
#include "ModelManager.h"
#include "PropItem.h"
#include "PropManager.h"
#include "PropCollector.h"

/************************************************************************/

DefineSingleton(PropManager);

/************************************************************************/

PropManager::PropManager() : 
	m_propCollector(NULL),
	m_numPropItems(0)
{
}

/************************************************************************/

PropManager::~PropManager()
{
	for (int index = 0; index < m_numPropItems; index ++)
	{
		delete m_props[index];
	}
	
	if(m_propCollector)
	{
		m_propCollector = NULL;
	}
}

/************************************************************************/

void 
PropManager::AddProp(PropItem* propIn)
{
	for (int index = 0; index < m_numPropItems; index ++)
	{
		if(strcmp(propIn->GetID(),m_props[index]->GetID())==0)
		{
			ErrorMessage("Prop already Exists");
		}
	}
	
	assert(m_numPropItems < c_MaxPropItems);
	m_props[m_numPropItems] = propIn;
	m_numPropItems ++;

}

/************************************************************************/

void
PropManager::DeleteProp(PropItem* prop)
{
	for (int index = 0; index < m_numPropItems; index ++)
	{
		if (m_props[index] == prop)
		{
			delete m_props[index];
			m_props[index] = m_props[m_numPropItems - 1];
			m_numPropItems  --;
			return;
		}
	}
}

/************************************************************************/

PropItem* 
PropManager::GetClosestProp(const Vector3D& position)
{
	float distanceSq = FLT_MAX;
	float testDist;
	PropItem* resultProp = NULL;

	for (int index = 0; index < m_numPropItems; index ++)
	{
		if(!m_props[index]->IsCollected())
		{
			testDist = Vector3DLengthSq(&(position - m_props[index]->GetPosition()));
			if(testDist < distanceSq)
			{
				distanceSq = testDist;
				resultProp = m_props[index];
			}
		}
		
	}

	return resultProp;
}

/************************************************************************/

PropItem* 
PropManager::GetClosestOfType(const char* typeName, const Vector3D& position)
{
	float distanceSq = FLT_MAX;
	float testDist;
	PropItem* resultProp = NULL;

	for (int index = 0; index < m_numPropItems; index ++)
	{
		if(!m_props[index]->IsCollected() && strcmp(m_props[index]->GetType(),typeName)==0)
		{
			testDist = Vector3DLengthSq(&(position - m_props[index]->GetPosition()));
			if(testDist < distanceSq)
			{
				distanceSq = testDist;
				resultProp = m_props[index];
			}
		}
	}

	return resultProp;
}

/************************************************************************/

PropItem* 
PropManager::GetPropItem(const char* propID)
{
	for (int i = 0; i < m_numPropItems; i++)
	{
		if(strcmp(propID, m_props[i]->GetID())==0)
		{	
			return m_props[i];
		}
	}

	ErrorMessage("Prop Doesn't exist");
	return 0;
}

/************************************************************************/

PropItem* 
PropManager::GetPropItem(int propIndex)
{
	if(propIndex <  m_numPropItems)
	{
		return m_props[propIndex];
	}
	ErrorMessage("Prop Doesn't exist");
	return 0;
}

/************************************************************************/

void 
PropManager::Render()
{
	for (int i = 0; i < m_numPropItems; i++)
	{
		m_props[i]->Render();
	}
}

/************************************************************************/

void 
PropManager::Update(float elapsedTime)
{
	for (int i = 0; i < m_numPropItems; i++)
	{
		m_props[i]->Update(elapsedTime);
	}
}

/************************************************************************/

int 
PropManager::GetNumProps()
{
	return m_numPropItems;
}

/************************************************************************/

void
PropManager::UpdateID(const char* oldName, const char* newName)
{
	for (int i = 0; i < m_numPropItems; i++)
	{
		if(_stricmp(ModelManager::GetInstance()->GetStaticModel(m_props[i]->GetMesh())->m_ID,oldName)==0)
		{
			m_props[i]->SetID(newName);
		}
	}
}

/************************************************************************/

void
PropManager::UpdateScale(const char* name, float scale)
{
	for (int i = 0; i < m_numPropItems; i++)
	{
		if(_stricmp(ModelManager::GetInstance()->GetStaticModel(m_props[i]->GetMesh())->m_ID,name)==0)
		{
			m_props[i]->SetScale(scale);
		}
	}
}

/************************************************************************/
