#ifndef _PROPITEM_H
#define _PROPITEM_H

#ifndef _RENDEREVENT_H_
#include "RenderEvent.h"
#endif //_RENDEREVENT_H_

#ifndef _SPHERE_H_
#include "Sphere.h"
#endif //#ifndef _SPHERE_H_

class Model;
class SprayEmitter;

class PropItem : public RenderEvent
{
public:
	/**
	 * Constructor
	 */
							PropItem();
	/**
	 * Destructor
	 */
							~PropItem();
	/**
	 * Renders the prop
	 */
	virtual void			Render();
	/**
	 * Updates the prop
	 */
	void					Update(
								float elapsedTime
								);
	/**
	 * Resturns the current position
	 */
	const Vector3D&			GetPosition()const {return m_position;}
	/**
	 * Sets the current position
	 */
	void					SetPosition(
								const Vector3D& pos
								);
	/**
	 * Sets the current rotation
	 */
	void					SetRotation(
								const Vector3D& rot
								);
	/**
	 * Marks if the prop should respawn after it has been collected
	 */
	void					SetRespawn(
								bool respawnOn
								) {m_respawn = respawnOn;}
	/**
	 * Sets the time the prop should respawn after
	 */
	void					SetRespawnTime(
								float timeSecs
								) {m_timeToRespawn = timeSecs;}
	/**
	 * Returns if the prop should respawn
	 */
	bool					GetRespawn() const {return m_respawn;}
	/**
	 * Returns the amount of time the prop should respawn after
	 */
	float					GetRespawnTime() const {return m_timeToRespawn;}
	/**
	 * Returns the scale of the prop
	 */
	float					GetScale() const {return m_scale;}
	/**
	 * Sets the scale of the prop
	 */
	void					SetScale(
								float scale
								);
	/**
	 * Returns the size of the prop
	 */
	float					GetSize() const;
	/**
	 * Sets the model to use for renderering
	 */
	void					SetMesh(
								Model* mesh
								) {m_modelPtr = mesh;}
	/**
	 * Returns the model the prop will use for renderering
	 */
	Model*					GetMesh() const {return m_modelPtr;}
	/**
	 * Regenerates the bounding sphere information from the model on the prop
	 */
	float					GenerateRadius();
	/**
	 * Marks the prop as selected or not
	 */
	void					Select(
								bool select
								);
	/**
	 * Returns the bounding sphere of the prop
	 */
	Sphere*					GetBoundingSphere();
	/**
	 * Sets the type of the prop
	 */
	void					SetType(
								const char* type
								){m_type = type;}
	/**
	 * Gets the type of prop
	 */
	const char*				GetType() const {return m_type;}
	/**
	 * Bakes the prop into the collision mesh
	 */
	void					BakeIntoCollisionMesh();
	/**
	 * Marks if the prop has been baked into the world or not
	 */
	void					SetBakedIntoWorld(
								bool bakeIn
								){m_colisionGeometry = bakeIn;}
	/**
	 * Returns if the prop has been baked into the world
	 */
	bool					GetBakedIntoWorld() const {return m_colisionGeometry;}
	/**
	 * Returns if the prop has been collected or not
	 */
	bool					IsCollected() const {return m_isCollected;}
	/**
	 * Marks the prop collected or not
	 */
	void					SetCollected(
								bool collect
								){m_isCollected = collect;}
	/**
	 * Returns the id of the prop
	 */
	const char*				GetID() const {return m_ID;}
	/**
	 * Sets the id of the prop
	 */
	void					SetID(
								const char* ID
								){m_ID = ID;}

protected:
	//Should the props use animated meshes ???
	Model*	 m_modelPtr;

	MyString m_ID;	
	MyString m_type;	
	bool	 m_isCollected;
	bool	 m_respawn;
	float    m_timeToRespawn;

	Vector3D m_position;
	Vector3D m_rotation;
	float	 m_scale;
	float	 m_radius;
	Vector3D m_sphereOffset;
	float	 m_time;

	Sphere	m_sphere;
	bool	m_selected;

	bool    m_colisionGeometry;

};


#endif