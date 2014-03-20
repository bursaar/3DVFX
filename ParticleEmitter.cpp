#include "Types.h"
#include "ParticleEmitter.h"
#include "EffectManager.h"
#include "Effect.h"
#include "CameraController.h"
#include "RenderManager.h"
#include "TextureCache.h"

/*******************************************************************************************************************/

ParticleEmitter::ParticleEmitter() :
	m_particles(0),
	m_textureIndex(0),
	m_maxNumberParitcles(0),
	m_VB(0),
	m_time(0.f)
{
}

/*******************************************************************************************************************/

ParticleEmitter::~ParticleEmitter()
{
	if (m_particles)
	{
		delete [] m_particles;
		m_particles = 0;
	}
	
	if (m_VB)
	{
		m_VB->Release();
		m_VB = 0;
	}
}

/*******************************************************************************************************************/

void
ParticleEmitter::LoadTexture(const char* ID, const char* fileName)
{
	m_textureIndex = TextureCache::GetInstance()->AddTexture(ID,fileName);
}

/*******************************************************************************************************************/

void
ParticleEmitter::SetID(const char* ID)
{
	m_ID = ID;
}

/*******************************************************************************************************************/

const char*
ParticleEmitter::GetID() const
{
	return m_ID;
}

/*******************************************************************************************************************/

void
ParticleEmitter::SetLooping(bool loop)
{
	m_looping = loop;
}

/*******************************************************************************************************************/

bool
ParticleEmitter::GetLooping() const
{
	return m_looping;
}

/*******************************************************************************************************************/

bool
ParticleEmitter::IsAllDead() const
{
	if(m_looping)
	{
		return false;
	}

	for (int i = 0; i < m_maxNumberParitcles; i++)
	{
		if(m_time - m_particles[i].m_time < m_particles[i].m_life)
		{
			return false;
		}
	}
	return true;
}

/*******************************************************************************************************************/

void		
ParticleEmitter::CreateParticles(int maxNumberParticles)
{
	if (m_particles)
	{
		delete [] m_particles;
		m_particles = 0;
	}
	
	if (m_VB)
	{
		m_VB->Release();
		m_VB = 0;
	}

	m_particles = new Particle[maxNumberParticles];
	m_maxNumberParitcles = maxNumberParticles;

	m_D3DDevice->CreateVertexBuffer(m_maxNumberParitcles*sizeof(Particle), D3DUSAGE_DYNAMIC|D3DUSAGE_WRITEONLY|D3DUSAGE_POINTS, 0, D3DPOOL_DEFAULT, &m_VB, 0);

}

/*******************************************************************************************************************/

void		
ParticleEmitter::RenderParticles() const
{
	if (m_maxNumberParitcles)
	{
		Particle* particles = 0;

		m_VB->Lock(0, 0, (void**)&particles, D3DLOCK_DISCARD);
		
		memcpy(particles, m_particles, m_maxNumberParitcles * sizeof(Particle));
		
		m_VB->Unlock();

		m_D3DDevice->SetVertexDeclaration(Particle::Decl);
		m_D3DDevice->SetStreamSource(0, m_VB, 0, sizeof(Particle));
		m_D3DDevice->DrawPrimitive(D3DPT_POINTLIST, 0, m_maxNumberParitcles);
	}
}

/*******************************************************************************************************************/

void							
ParticleEmitter::SetUpEmitter(int numberParticles, const Vector3D& minPosition, const Vector3D& maxPosition, const Vector3D& minVelocity, 
							  const Vector3D& maxVelocity, float mass, float minlife, float maxlife, float size)
{
	m_minPosition = minPosition;
	m_maxPosition = maxPosition;
	m_minVelocity = minVelocity;
	m_maxVelocity = maxVelocity;
	m_mass = mass;
	m_maxLife = maxlife;
	m_minLife = minlife;
	m_size = size;

	CreateParticles(numberParticles);

	for (int index = 0; index < m_maxNumberParitcles; index ++)
	{
		SetUpParticle(m_particles[index]);
	}
}

/*******************************************************************************************************************/

void 
ParticleEmitter::SetUpParticle(Particle& particle)
{
	particle.m_position.x = GetRandomFloat(m_minPosition.x, m_maxPosition.x);
	particle.m_position.y = GetRandomFloat(m_minPosition.y, m_maxPosition.y);
	particle.m_position.z = GetRandomFloat(m_minPosition.z, m_maxPosition.z);
	particle.m_time = m_time;
	particle.m_colour = 0xFFFFFFFF;
	particle.m_mass = m_mass;
	particle.m_size = m_size;
	particle.m_life = GetRandomFloat(m_minLife, m_maxLife);
	particle.m_velocity.x = GetRandomFloat(m_minVelocity.x,m_maxVelocity.x);
	particle.m_velocity.y = GetRandomFloat(m_minVelocity.y,m_maxVelocity.y);
	particle.m_velocity.z = GetRandomFloat(m_minVelocity.z,m_maxVelocity.z);
}

/*******************************************************************************************************************/

void 
ParticleEmitter::Render()
{
	Matrix world;
	MatrixIdentity(&world);

	Effect* particleEffect = EffectManager::GetInstance()->GetEffect("particleeffect");

	particleEffect->SetMatrix("m_WVP", world * CameraController::GetInstance()->GetView() * CameraController::GetInstance()->GetProjection());
	particleEffect->SetVector3("m_EyePosition", CameraController::GetInstance()->GetCurrentCameraPosition());
	particleEffect->SetTexture("m_Texture", TextureCache::GetInstance()->GetTexture(m_textureIndex));
	particleEffect->SetFloat("m_Time", m_time);
	particleEffect->SetVector3("m_WorldAccel",Vector3D(0,0,0));

	particleEffect->GetEffect()->CommitChanges();

	ParticleEmitter::RenderParticles();
}

/*******************************************************************************************************************/

void
ParticleEmitter::Update(float elapsedTime)
{
	m_time += elapsedTime;
	
	for (int index = 0; index < m_maxNumberParitcles; index++)
	{
		Particle& particle = m_particles[index];

		if(m_time - particle.m_time > particle.m_life)
		{
			if(m_looping)
			{
				SetUpParticle(particle);
			}
			else
			{
				//move away
				particle.m_position = Vector3D(0,-100000,0);
			}
		}
	}
}

/*******************************************************************************************************************/

void		
ParticleEmitter::SetEmitRegion(const Vector3D& minPosition, const Vector3D& maxPosition)
{
	m_minPosition = minPosition;
	m_maxPosition = maxPosition;
}

/*******************************************************************************************************************/
