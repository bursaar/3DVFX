#ifndef _BEHAVIORMANAGER_H_
#define _BEHAVIORMANAGER_H_

class Behavior;

class BehaviorManager : public Singleton<BehaviorManager>
{
public:
	/**
	 * Constructor
	 */
					BehaviorManager();
	/**
	 * Destructor
	 */
					~BehaviorManager();
	/**
	 * Adds a new behaviour to the list which can be used.
	 * Note that the BehaviorManager will now be responsible for 
	 * freeing this object
	 */
	void			AddBehavior(
						Behavior* behaviorIn ///< New Behaviour
						);
	/**
	 * Returns the behaviour for the correspoding id.
	 */
	Behavior*		GetBehavior(
						const char* behaviorID ///< Id of the behaviour we want.
						) const;
	/**
	 * Returns the behaviour at the corresponding index in the array of behaviours
	 */
	Behavior*		GetBehavior(
						int behaviorIndex
						) const;
	/**
	 * Returns the number of behaviours current soted within the manager
	 */
	int				GetNumberBehaviors() const;
private:
	static const int c_MaxBehaviours = 256;
	Behavior* m_behaviours[c_MaxBehaviours];
	int m_numBehaviours;
};

#endif