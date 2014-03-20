#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#ifndef _TYPES_H_
#include "Types.h"
#endif //#ifndef _TYPES_H_

/////////////////////////////////////////////////
//The GameState Class is the base class for every gamestate within the program
//each state (like game.cpp) can be added to the GameStateManager
//where each state is controlled, calling the relivent functions
//below when required.
/////////////////////////////////////////////////

class GameState
{
public:
	/**
	 * Constructor
	 */
					GameState(
						const char* stateName ///< The identifier for the game state
						);
	/** 
	 * Destructor
	 */
	virtual			~GameState() {};
	/**
	 * On entry handler, called when you enter the game state
	 */
	virtual void	OnEntry(){};
	/**
	 * On exit handler, called when you exit the game state
	 */
	virtual void	OnExit(){};
	/**
	 * Update handler, called once a frame for the state to update its logic.
	 */
	virtual void	Update(
						float elapsedTime ///< The elapsed time this frame
						){};
	/**
	 *	Render handler, handles renderering the game for its current state
	 */
	virtual void	Render(){};
	/**
	 * Returns the state name
	 */
	const char*		GetStateName() const;
private:
	MyString m_stateName; ///< The name of this state
};

#endif // _GAMESTATE_H_

