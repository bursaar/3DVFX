#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#ifndef _RENDEREVENT_H_
#include "RenderEvent.h"
#endif //_RENDEREVENT_H_

#ifndef _WAYPOINTMANAGER_H_
#include "WaypointManager.h"
#endif //_WAYPOINTMANAGER_H_

#ifndef _ASTAR_H_
#include "AStar.h"
#endif

/// Helper Define to cache off an animation index to make setting an animation quick
#define SetAnimationAndCacheIndex(o,s) { static int animationIndexCache = o->GetAnimationIndex(s); o->SetAnimation(animationIndexCache); }

class Sphere;
class SkinnedMesh;
class AnimationInstance;
class Behavior;
class WayPoint;

class Character : public RenderEvent
{
public:
	/**
	 * Constructor
	 */
	Character();
	/**
	 * Destructor
	 */
	~Character();
	/**
	 * Marks the character as its be hit if its vulnarable. And sets
	 * up the flashing on the character
	 */
	void HurtCharacter();
	/**
	 * Sets the mesh to use for renderering
	 */
	void				SetMesh(
							SkinnedMesh* meshPtr
							);
	/**
	 * Returns the id of the character
	 */
	const char*			GetID() const;
	/**
	 * Sets the id of the character
	 */
	void				SetID(
							const char* ID
							);
	/**
	 * Renders the character
	 */
	virtual void		Render();
	/**
	 * Updates the character
	 */
	void				Update(
							float elapsedTime ///< The elapsed time this frame
							);
	/**
	 * Gets the index of the animation
	 */
	int					GetAnimationIndex(
							const char* aniName
							) const;
	/**
	 * Sets the current animation to use
	 */
	void				SetAnimation(
							const char* aniName
							);
	/**
	 * Sets the current animation to use
	 */
	void				SetAnimation(
							int index
							);
	/**
	 * Returns the animation the character is playing
	 */
	const char*			GetAnimationName() const;
	/**
	 * Returns the animation instance for this character
	 */
	AnimationInstance*	GetAnimationInst()const;
	/**
	 * Sets the position of the character
	 */
	void				SetPosition(
							const Vector3D& pos
							);
	/**
	 * Gets the characters current position
	 */
	const Vector3D&		GetPosition() const;
	/**
	 * Sets the characters current rotation
	 */
	void				SetRotation(
							const Vector3D& rot
							);
	/**
	 * Gets the characters current rotation
	 */
	const Vector3D&		GetRotation() const;
	/**
	 * Sets the scale on the character
	 */
	void				SetScale(
							float scale
							);
	/**
	 * Returns the scale of the character
	 */
	float				GetScale()const;
	/**
	 * Adds a waypoint for the character to follow
	 */
	void				AddWayPoint(
							const WayPoint* waypoint
							);
	/**
	 * Sets the current behaviour on the character
	 */
	void				SetBehavior(
							const char* newBehavior
							);
	/**
	 * Sets an offset onto the characters bounding sphere
	 */
	void				SetBoundOffset(
							const Vector3D& boundPos
							);
	/**
	 * Gets the current offset on the characters bounding sphere
	 */
	const Vector3D&		GetBoundOffset() const;
	/**
	 * Gets the current behaviour on the character
	 */
	const char*			GetBehaviourID() const;

	unsigned int		GetHitCount()const;
	void		 SetHitCount(unsigned int hits){m_hitCount = hits;}

	/**
	 * Returns if the character is dead or not
	 */
	bool				IsDead() const {return m_isDead;}
	/**
	 * Returns if the character is dead or not
	 */
	void				SetDead(
							bool dead
							){m_isDead = dead;}
	/**
	 * Returns if the character is the player or not
	 */
	bool				IsPlayer() const {return m_isPlayer;}
	/**
	 * Returns the type of character this is
	 */
	const char*			GetType() const;
	/**
	 * Sets the type of character this is
	 */
	void				SetType(
							const char* type
							);
	/**
	 * Gets the number of waypoints the character has assoicated with it
	 */
	int					GetWayPointCount() const;
	/**
	 * Gets the waypoint at specified index
	 */
	const WayPoint*		GetWayPoint(int index) const;
	/**
	 * Gets the waypoint they are currently moving from
	 */
	const WayPoint*		GetSourceWayPoint() const;
	/**
	 * Gets the waypoint they are currently moving to
	 */
	const WayPoint*		GetTargetWayPoint() const;
	/**
	 * Lets the character know its arrived at a waypoint so it can move
	 * onto its next waypoint
	 */
	void				ArrivedAtWaypoint();
	/**
	 * Returns the bounding sphere of the character
	 */
	Sphere*				GetBoundingSphere() const;

private:
	const WayPoint* m_sourceWaypoint;
	const WayPoint* m_targetWaypoint;
	int m_waypointTracker;

	static const int c_MaxWayPointCount = 64;
	const WayPoint* m_waypointList[c_MaxWayPointCount];
	int m_numWaypoints;


	Sphere*	 m_boundingSphere;
	Vector3D m_boundPosition;
	float m_boundRadius;
	Vector3D m_boundPositionOffset;

	AnimationInstance* m_aniCon;

	MyString m_ID;
	MyString m_Type;
	SkinnedMesh* m_meshPtr;
	unsigned int m_instanceNum;

	Vector3D m_position;
	Vector3D m_rotation;
	Vector3D m_velocity;
	float m_speed;

	unsigned int m_hitCount;

	float m_scale;
	float m_time;
	

	bool m_isPlayer;
	bool m_isDead;

	//Current character state
	MyString m_currentBehavior;
};

#endif //_CHARACTER_H_
