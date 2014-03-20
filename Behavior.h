#ifndef _BEHAVIOR_H_
#define _BEHAVIOR_H_

class Character;

enum TurnDirection
{
	TD_LEFT,
	TD_RIGHT,
	TD_FACING
}; 

class Behavior
{
public:
	/**
	 * Constructor
	 */
					Behavior(
						const char* ID ///< The name of the behaviour
						);
	/**
	 * Destructor
	 */
	virtual			~Behavior();
	/**
	 * Notifies the behaviour that the following character has now entered the behaviour
	 */
	virtual void	OnEnter(
						Character* owner
						) = 0;
	/**
	 * Updates the characters logic for this behaviour
	 */
	virtual void	Update(
						Character* owner, 
						float elapsedTime
						) = 0;
	/**
	 * Notifies the behaviour that the following character has now left the behaviour
	 */
	virtual void	OnExit(
						Character* owner
						) = 0;
	/**
	 * Returns the id of the behaviours
	 */
	const char*		GetID() const	{return m_ID;}
protected:
	/**
	 * General Purpose behaviour helper which snaps the character onto the terrian
	 */
	void					FollowTerrain(
								Character* owner,
								float elapsedTime
								);
	/**
	 * General Purpose behaviour helper which calculates the angle bewteen the character
	 * and the target point
	 */
	float					AngleToTarget(
								Character* owner,
								const Vector3D& targetPos
								);
	/**
	 * General Purpose behaviour helper which calculates the angle bewteen the character
	 * and the target point using their current target point on their path
	 */
	float					GetPathAngleToTarget(
								Character* owner,
								const Vector3D& targetPos
								);
	/**
	 * General Purpose behaviour helper which moves the character in the direction which they are currently
	 * facing
	 */
	void					MoveInDirection(
								Character* owner, 
								float elapsedTime
								);
	/**
	 * General Purpose behaviour helper which returns the distance between the owner character and the 
	 * specified character (cancels out y distance)
	 */
	float					DistanceToCharacterSq(
								Character* owner,
								const Character& character
								);
	/**
	 * General Purpose behaviour helper which returns the distance between the owner character and the 
	 * specified point (cancels out y distance)
	 */
	float					DistanceToTargetSq(
								Character* owner,
								const Vector3D& targetPos
								);
	/**
	 * General Purpose behaviour helper which handles turning the character.
	 */
	virtual TurnDirection	TurnTo(
								Character* owner, 
								float angle, 
								float speed, 
								float elapsedTime
								);
	
	MyString m_ID;
	Character* m_playerCharacter;
};

#endif