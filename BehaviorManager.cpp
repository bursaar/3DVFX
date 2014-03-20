#include "Types.h"
#include "BehaviorManager.h"
#include "Behavior.h"

/************************************************************************/

DefineSingleton(BehaviorManager);

/************************************************************************/

BehaviorManager::BehaviorManager() :
	m_numBehaviours(0)
{
}

/************************************************************************/

BehaviorManager::~BehaviorManager()
{
	for (int index = 0; index < m_numBehaviours; index ++)
	{
		delete m_behaviours[index];
	}
}

/************************************************************************/

void 
BehaviorManager::AddBehavior(Behavior* behaviorIn)
{
	for (int index = 0; index < m_numBehaviours; index ++)
	{
		if(strcmp(behaviorIn->GetID(),m_behaviours[index]->GetID())==0)
		{
			return;
		}
	}
	
	assert(m_numBehaviours < c_MaxBehaviours);
	m_behaviours[m_numBehaviours] = behaviorIn;
	m_numBehaviours ++;

}

/************************************************************************/

Behavior* 
BehaviorManager::GetBehavior(const char* behaviorID) const
{
	for (int index = 0; index < m_numBehaviours; index ++)
	{
		if(strcmp(behaviorID, m_behaviours[index]->GetID())==0)
		{	
			return m_behaviours[index];
		}
	}
	
	MyString errorString;
	errorString.Format("Behavior %s doesn't exist",behaviorID);
	ErrorMessage(errorString);
	return 0;
}

/************************************************************************/

Behavior* 
BehaviorManager::GetBehavior(int behaviorIndex) const
{
	if(behaviorIndex < m_numBehaviours)
	{
		return m_behaviours[behaviorIndex];
	}
	MyString errorString;
	errorString.Format("Behavior number %d doesn't exist",behaviorIndex);
	ErrorMessage(errorString);
	return 0;
}

/************************************************************************/

int 
BehaviorManager::GetNumberBehaviors() const
{
	return m_numBehaviours;
}

/************************************************************************/
