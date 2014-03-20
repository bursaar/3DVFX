#include "Types.h"
#include "PropItem.h"

#include "CameraController.h"
#include "EffectManager.h"
#include "Effect.h"
#include "RenderManager.h"
#include "BaseCamera.h"
#include "EnvironmentManager.h"
#include "CollisionMesh.h"
//#include "NavigationMeshCutter.h"

#include "Model.h"

#include "Sphere.h"

#include "CharacterManager.h"

#include "Character.h"

#include "AABB.h"

#include "PropManager.h"
#include "PropCollector.h"

#include "ParticleSystem.h"
#include "ParticleEmitter.h"

/************************************************************************/

PropItem::PropItem() : 
	m_modelPtr(0),
	m_position(Vector3D(0.0f,0.0f,0.0f)),
	m_rotation(Vector3D(0.0f,0.0f,0.0f)),
	m_scale(1.0f),
	m_isCollected(false),
	m_respawn(false),
	m_timeToRespawn(-1),
	m_selected(false),
	m_colisionGeometry(false)
{
	m_flags = NoEffects;
	RenderManager::GetInstance()->AddEvent(this, NULL);
}

/************************************************************************/

PropItem::~PropItem()
{
	
	RenderManager::GetInstance()->RemoveEvent(this);
	m_modelPtr = 0;
}

/************************************************************************/

float 
PropItem::GenerateRadius()
{
	if(m_modelPtr)
	{
		AABB aabb(m_modelPtr->GetMesh());

		m_sphereOffset = (aabb.GetMin() + aabb.GetMax()) * 0.5f;
		m_radius = Vector3DLength(&(aabb.GetMax() - aabb.GetMin())) * 0.5f;

		m_sphere.SetRadius(m_radius * m_scale);
		return m_radius;
	}
	return 0.0f;
}

/************************************************************************/

void
PropItem::SetPosition(const Vector3D& pos)
{
	m_position = pos;
	Vector3D spherePos(m_sphereOffset.x + m_position.x,m_sphereOffset.y + m_position.y,m_sphereOffset.z + m_position.z);
	m_sphere.SetPosition(spherePos);	
}

/************************************************************************/

void
PropItem::SetRotation(const Vector3D& rot)
{
	m_rotation = rot;
}

/************************************************************************/

void
PropItem::SetScale(float scale)
{
	m_scale = scale;
	m_sphere.SetRadius(m_radius*m_scale);
}

/************************************************************************/

float
PropItem::GetSize() const
{
	return m_radius*m_scale;
}

/************************************************************************/

void 
PropItem::Render()
{
	if(!m_isCollected || m_colisionGeometry)
	{
		if(m_modelPtr)
		{
			Vector3D spherePos(m_sphereOffset.x + m_position.x,m_sphereOffset.y + m_position.y ,m_sphereOffset.z + m_position.z);
			m_sphere.SetPosition(spherePos);

			m_modelPtr->SetPosition(m_position);
			m_modelPtr->SetRotation(m_rotation);
			m_modelPtr->SetScale(m_scale);

			m_modelPtr->Render();

			
		}
	}
}

/************************************************************************/

void 
PropItem::Update(float elapsedTime)
{
	m_time = elapsedTime;
	//Handle bobbing / rotation

	if(!m_isCollected  && !m_colisionGeometry)
	{
		m_rotation.y +=  elapsedTime;

		if(m_rotation.y > 2 * D3DX_PI)
		{
			m_rotation.y = 0.0f;
		}
	}
	
	//Handle Collection
	if(PropManager::GetInstance()->GetCollector() && ! m_isCollected)
	{
		if(CharacterManager::GetInstance()->GetCharacter(PropManager::GetInstance()->GetCollector()->GetID())->GetBoundingSphere()->CollidingWithSphere(m_sphere))
		{
			PropManager::GetInstance()->GetCollector()->OnCollected(this);
			
			//Set is collected by the actual collector in case certain types of collector shouldn't be collected
			//m_isCollected = true;
		}
	}

	//Handle Respawn
	if(m_isCollected)
	{
		if(m_respawn)
		{
			static float respawnTimer = 0.0f;
			respawnTimer += elapsedTime;

			if(respawnTimer > m_timeToRespawn)
			{
				respawnTimer = 0.0f;
				m_isCollected = false;
			}
		}
	}
}

/************************************************************************/

Sphere*
PropItem::GetBoundingSphere()
{
	return &m_sphere;
}

/************************************************************************/

void
PropItem::BakeIntoCollisionMesh()
{
	if (m_modelPtr)
	{
		Matrix mat, temp;

		MatrixIdentity(&mat);
		MatrixRotationZ(&temp, m_rotation.z);
		MatrixMultiply(&mat, &mat, &temp);
		MatrixRotationY(&temp, m_rotation.y);
		MatrixMultiply(&mat, &mat, &temp);
		MatrixRotationX(&temp, m_rotation.x);
		MatrixMultiply(&mat, &mat, &temp);
		MatrixTranslation(&temp, m_position.x, m_position.y, m_position.z);
		MatrixMultiply(&mat, &mat, &temp);

		EnvironmentManager::GetInstance()->GetCollisionMesh()->AddModelToCollisionMesh(m_modelPtr, mat);
	}
}

/************************************************************************/