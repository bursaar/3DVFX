#ifndef _PARTICLEEMITTER_H_
#define _PARTICLEEMITTER_H_

#ifndef _PARTICLESYSTEM_H_
#include "ParticleSystem.h"
#endif //#ifndef _PARTICLESYSTEM_H_

#ifndef _RENDEREVENT_H_
#include "RenderEvent.h"
#endif //#ifndef _RENDEREVENT_H_

class ParticleEmitter : public RenderEvent
{
public:
	/**
	 * Constructor
	 */
									ParticleEmitter();
	/**
	 * Destructor
	 */
	virtual							~ParticleEmitter();
	/**
	 * Sets up the particle emitter
	 */
	void							SetUpEmitter(
										int numberParticles, ///< The number of particles
										const Vector3D& minPosition, ///< The minimum position
										const Vector3D& maxPosition, ///< The maximum position
										const Vector3D& minVelocity, ///< The minimum velocity
										const Vector3D& maxVelocity, ///< The maximum velocity
										float mass, ///< Mass of the paticle
										float minlife, ///< The minimum life time of the particle
										float maxlife, ///< The maximum life time of the particle
										float size ///< The size of the particle
										);
	/**
	 * Initialises a new particle based upon the emitters settings
	 */
	virtual void					SetUpParticle(
										Particle& par ///< Particle to setup
										);
	/**
	 * Renders the particel emitter
	 */
	virtual void					Render();
	/**
	 * Updates the particle emitter
	 */
	virtual void					Update(
										float elapsedTime ///< The amount of time elapsed this frame
										);
	/**
	 * Sets the texture to use for the particles
	 */
	void							LoadTexture(
										const char* ID, ///< Id of the texture
										const char* fileName ///< The filename of the texture
										);
	/**
	 * Sets the id of the particel emitter
	 */
	void							SetID(
										const char* ID
										);
	/**
	 * Gets the id of the particle emitter
	 */
	const char*						GetID() const;
	/**
	 * Returns if the particle emitter is constantly spawning
	 */
	bool							GetLooping() const;
	/**
	 * Sets if the particle emitter is constantly spawning
	 */
	void							SetLooping(
										bool loop
										);
	/**
	 * Returns if all the particles has all died
	 */
	bool							IsAllDead() const;
	/**
	 * Updates the region within which the particles can be spawned
	 */
	void							SetEmitRegion(
										const Vector3D& minPosition, 
										const Vector3D& maxPosition
										);
private:
	/**
	 * Initialises the particle array ready for use
	 */
	void							CreateParticles(
										int maxNumberParticles
										);
	/**
	 * Renders all the particles
	 */
	void							RenderParticles() const;

	MyString m_ID;

	float m_time;

	Vector3D m_minPosition;
	Vector3D m_maxPosition;

	Vector3D m_minVelocity;

	Vector3D m_maxVelocity;

	float m_maxLife;

	float m_minLife;

	float m_mass;

	float m_size;
	
	int m_maxNumberParitcles;
	
	float m_particleDelay;

	Particle* m_particles;

	int m_textureIndex;

	IDirect3DVertexBuffer9* m_VB;

	bool m_looping;
};

#endif //#ifndef _PARTICLEEMITTER_H_
