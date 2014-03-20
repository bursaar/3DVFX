#ifndef _PARTICLESYSTEM_H_
#define _PARTICLESYSTEM_H_

class ParticleEmitter;

struct Particle
{
	Vector3D m_position;
	Vector3D m_velocity;
	float m_size;
	float m_time;
	float m_life;
	float m_mass;
	Colour m_colour;

	static IDirect3DVertexDeclaration9* Decl;
};

class ParticleSystem : public Singleton<ParticleSystem>
{
public:
	/**
	 * Constructor
	 */
						ParticleSystem();
	/**
	 * Destructor
	 */
						~ParticleSystem();
	/**
	 * Adds an new particle emitter to be managed
	 */
	void				AddEmitter(
							ParticleEmitter* emitter ///< The new emitter
							);
	/**
	 * Updates all the particle emitters
	 */
	void				Update(
							float elapsedTime ///< The amount of elapsed time this frame
							);
	/**
	 * Renders all the particel emitters
	 */
	void				Render();
	/**
	 * Returns the particle emitter with the specified id
	 */
	ParticleEmitter*	GetEmitter(
							const char* ID ///< id of the particle system
							);
private:
	MyLinkedList<ParticleEmitter*> m_emitters;
};

#endif //_PARTICLESYSTEM_H_

