
#include "GameState.h"

/************************************************************************************/

GameState::GameState(const char* stateName) :
	m_stateName(stateName)
{
}

/************************************************************************************/
	
const char*		
GameState::GetStateName() const
{
	return m_stateName;
}

/************************************************************************************/