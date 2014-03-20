#ifndef _GAMESTATEMANAGER_H_
#define _GAMESTATEMANAGER_H_
#include "Types.h"
#include "GameState.h"

class GameStateManager : public Singleton<GameStateManager>
{
public:
	/**
	 * Constructor
	 */
						GameStateManager();
	/**
	 * Destructor
	 */
						~GameStateManager();
	/**
	 * Adds a game state to the list of states that can be used.
	 */
	void				AddState(
							GameState* state ///< New game state
							);
	/**
	 * Sets the currently active state
	 */
	void				SwitchState(
							const char* stateName ///< The name of the state to activate
							);
	/**
	 * Returns the current game state name
	 */
	const char*			GetCurrentStateName() const;
	/**
	 * Updates the currently active state
	 */
	void				Update(
							float elapsedTime
							);
	/**
	 * Renders the currently active state
	 */
	void				Render();
	/**
	 * Returns the currently active state
	 */
	GameState*			GetCurrentState() const;
private:
	static const int c_MaxNumStates = 10;
	
	GameState*				 m_currentState;
	GameState*				 m_stateList[c_MaxNumStates];
	int						 m_numStates;
	
	bool					 m_updating;
	bool					 m_cachedSwitch;
	
	MyString				 m_cachedSwitchState;
};

#endif //_GAMESTATEMANAGER_H_
