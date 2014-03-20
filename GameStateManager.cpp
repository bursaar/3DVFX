#include "GameStateManager.h"
#include "InputManager.h"
#include "Vertex.h"
#include "TextureCache.h"
#include "SoundManager.h"
#include "EffectManager.h"
#include "EntityLoader.h"
#include "Program.h"

/*****************************************************************************************/

DefineSingleton(GameStateManager)

/*****************************************************************************************/

GameStateManager::GameStateManager() :
	m_numStates(0),
	m_currentState(0),
	m_updating(false),
	m_cachedSwitch(false)
{
	InitAllVertexDeclarations();
}

/*****************************************************************************************/

GameStateManager::~GameStateManager()
{
	DestroyAllVertexDeclarations();

	if(m_currentState)
	{
		m_currentState->OnExit();
		m_currentState = 0;
	}
	
	for (int index = 0; index < m_numStates; index ++)
	{
		delete m_stateList[index];
	}
}
/*****************************************************************************************/

void
GameStateManager::AddState(GameState *state)
{
	for (int index = 0; index < m_numStates; index ++)
	{
		if(strcmp (m_stateList[index]->GetStateName(),state->GetStateName()) == 0)
		{
			ErrorMessage("This State Already Exists");
			//state already exists
		}
	}
	
	assert(m_numStates < c_MaxNumStates);
	m_stateList[m_numStates] = state;
	m_numStates++;

	if(m_currentState == 0)
	{
		m_currentState = state;
		m_currentState->OnEntry();
	}
}
/*****************************************************************************************/
void
GameStateManager::SwitchState(const char* stateName)
{
	if (m_updating)
	{
		m_cachedSwitch = true;
		m_cachedSwitchState = stateName;
		return;
	}

	if(m_currentState)
	{
		m_currentState->OnExit();
	}

	for (int index = 0; index < m_numStates; index ++)
	{
		if(strcmp (m_stateList[index]->GetStateName(),stateName) == 0)
		{
			m_currentState = m_stateList[index];
			m_currentState->OnEntry();
			return;
		}
	}
	assert(false);
}

/*****************************************************************************************/

const char*
GameStateManager::GetCurrentStateName() const
{
	return m_currentState->GetStateName();
}

/*****************************************************************************************/

void
GameStateManager::Update(float elapsedTime)
{
	m_updating = true;
	m_currentState->Update(elapsedTime);
	m_updating = false;

	if (m_cachedSwitch)
	{
		m_cachedSwitch = false;
		SwitchState(m_cachedSwitchState);
	}
}

/*****************************************************************************************/

void
GameStateManager::Render()
{
	m_currentState->Render();
}

/*****************************************************************************************/

GameState*
GameStateManager::GetCurrentState() const
{
	return m_currentState;
}

/*****************************************************************************************/

