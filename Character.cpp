#include "Types.h"
#include "Model.h"
#include "Character.h"
#include "CameraController.h"
#include "RenderManager.h"
#include "BaseCamera.h"
#include "Vertex.h"

#include "Effect.h"
#include "EffectManager.h"

#include "InputManager.h"
#include "Sphere.h"
#include "Frustum.h"
#include "AnimationInstance.h"
#include "MeshHierarchy.h"
#include "SkinnedMesh.h"
#include "BehaviorManager.h"
#include "Behavior.h"

#include "WayPointManager.h"

Character::Character() : 
	m_velocity(Vector3D(0,0,0)), 
	m_numWaypoints(0),
	m_hitCount(0),
	m_isDead(false),
	m_aniCon(0)
{
	m_meshPtr = 0;
	m_position = Vector3D(0,0,0);
	m_rotation = Vector3D(0,0,0);
	m_boundPositionOffset = Vector3D(0,0,0);
	m_scale = 1.0f;

	m_sourceWaypoint = 0;
	m_targetWaypoint = 0;
	m_waypointTracker = 0;

	m_flags = Skinned;
    m_boundingSphere = NULL;

	m_currentBehavior = "";

	RenderManager::GetInstance()->AddEvent(this, NULL);
}

/************************************************************************/

Character::~Character()
{
	RenderManager::GetInstance()->RemoveEvent(this);
	m_meshPtr = 0;
	if(m_aniCon)
	{
		delete m_aniCon;
		m_aniCon = 0;
	}
	if(m_boundingSphere)
	{
		delete m_boundingSphere;
		m_boundingSphere = 0;
	}
}

/************************************************************************/

void 
Character::HurtCharacter()
{
	this->m_hitCount++;	
}

void
Character::SetMesh(SkinnedMesh *meshPtr)
{
	//delete animation controller if one exists already
	if(m_aniCon)
	{
		delete m_aniCon;
		m_aniCon = 0;
	}
	//delete bounding Sphere if one exists already
	if(m_boundingSphere)
	{
		delete m_boundingSphere;
		m_boundingSphere = 0;
	}
	//set m_meshPtr to the mesh pointer passed into the function
	m_meshPtr = meshPtr;
	//get a clone of its animation controller
	m_meshPtr->CloneAniCon(&m_aniCon);
	//if it requires a shadow volume, get that too
	if(m_meshPtr->GetShadowMesh())
	{
		m_flags |= ShadowVolume;
	}

	//create a bounding sphere
	D3DXFrameCalculateBoundingSphere(meshPtr->GetFrameRoot(),&m_boundPosition,&m_boundRadius);
	if(m_boundingSphere)
	{
		m_boundingSphere->SetPosition(m_position+m_boundPosition);
		m_boundingSphere->SetRadius(m_boundRadius*m_scale);
	}
	else
	{
		m_boundingSphere = new Sphere(m_boundPosition,m_boundRadius);
	}
	m_aniCon->Update(0, m_meshPtr);
}
	
/************************************************************************/

void
Character::Render()
{
	//check the character is in the viewing frustum
	const Frustum& frustum = CameraController::GetInstance()->GetFrustum();
	Vector3D pos = m_position + m_boundPosition;
	float radius = m_boundRadius * m_scale;
	bool visible = frustum.SphereVisible(pos, radius);

	if(!visible)
	{
		return;
	}

	//if render flag is Skinned
	if(RenderManager::GetInstance()->CurrentRenderFlag() == Skinned)
	{
		//transform mesh to position
        Matrix tempWorld, tempScale, tempPosition, tempRot;
		Matrix rotateX, rotateY, rotateZ;

		MatrixScaling(&tempScale,m_scale,m_scale,m_scale);

		MatrixRotationX(&rotateX,m_rotation.x);
		MatrixRotationY(&rotateY,m_rotation.y);
		MatrixRotationZ(&rotateZ,m_rotation.z);

		MatrixTranslation(&tempPosition,m_position.x,m_position.y,m_position.z);
		MatrixMultiply(&tempRot, &rotateX, &rotateY);
		MatrixMultiply(&tempRot, &tempRot, &rotateZ);

		MatrixMultiply(&tempWorld, &tempScale, &rotateY);
		MatrixMultiply(&tempWorld, &tempWorld, &rotateX);
		MatrixMultiply(&tempWorld, &tempWorld, &rotateZ);
		MatrixMultiply(&tempWorld, &tempWorld, &tempPosition);
		
		Effect* vertexBlend = EffectManager::GetInstance()->GetEffect("VertexBlend");
		vertexBlend->SetMatrix("m_World", tempWorld);

		//create a WVP
		tempWorld = tempWorld * CameraController::GetInstance()->GetViewProjection();
		
		//set the vertexblend shader
		vertexBlend->SetMatrix("m_WVP", tempWorld);
		vertexBlend->SetVector4("m_LightPosition", Vector4D(0,1,0,0));
		vertexBlend->SetMatrix("m_View", CameraController::GetInstance()->GetView());
		vertexBlend->SetMatrix("m_Rotation", tempRot);

		vertexBlend->GetEffect()->CommitChanges();

		/*Skinned meshes that have multiple instances
		MUST be rendered via the animation controller
		as the controller will set the bones to the one in the current anim set
		for its particular instance :s*/
		m_meshPtr->Render(m_aniCon);
	}

	//if a ShadowMap render call
	else if(RenderManager::GetInstance()->CurrentRenderFlag() == ShadowMapRender)
	{
		//transform mesh to position
		Matrix tempWorld, tempScale, tempPosition, tempRot;
		Matrix rotateX, rotateY, rotateZ;

		MatrixScaling(&tempScale,m_scale,m_scale,m_scale);
		
		MatrixRotationX(&rotateX,m_rotation.x);
		MatrixRotationY(&rotateY,m_rotation.y);
		MatrixRotationZ(&rotateZ,m_rotation.z);

		MatrixTranslation(&tempPosition,m_position.x,m_position.y,m_position.z);
		MatrixMultiply(&tempRot, &rotateX, &rotateY);
		MatrixMultiply(&tempRot, &tempRot, &rotateZ);

		MatrixMultiply(&tempWorld, &tempScale, &rotateY);
		MatrixMultiply(&tempWorld, &tempWorld, &rotateX);
		MatrixMultiply(&tempWorld, &tempWorld, &rotateZ);
		MatrixMultiply(&tempWorld, &tempWorld, &tempPosition);
		
		Effect* shadowMap = EffectManager::GetInstance()->GetEffect("ShadowMap");

		//set shadow map shader
		shadowMap->SetMatrix("m_World", tempWorld);
		shadowMap->GetEffect()->CommitChanges();
		
		m_meshPtr->RenderShadow(m_aniCon);
	}
}

/************************************************************************/

void
Character::Update(float elapsedTime)
{
	m_time = elapsedTime;
	m_aniCon->Update(m_time,m_meshPtr);
	

	
	//find a key bone that we can use as a center point for the bounding sphere
	const Matrix& hipPos = m_meshPtr->GetJointMatrix("spine_hips",m_aniCon);
	m_boundPosition = Vector3D(hipPos._41,hipPos._42,hipPos._43);
	Matrix rot;	
	MatrixRotationY(&rot,this->GetRotation().y);
	Vector3DTransformCoord(&m_boundPosition,&m_boundPosition,&rot);
	Vector3D offsetRot;
	Vector3DTransformCoord(&offsetRot,&m_boundPositionOffset,&rot);
	//update sphere position
	if(m_boundingSphere)
	{
		m_boundingSphere->SetPosition(m_position+m_boundPosition+offsetRot);	
	}

	//update behavior
	if(m_currentBehavior.Length() > 0)
	{
		BehaviorManager::GetInstance()->GetBehavior(m_currentBehavior)->Update(this,elapsedTime);
	}
}

/************************************************************************/

int
Character::GetAnimationIndex(const char* aniName) const
{
	return m_aniCon->GetIndex(aniName);
}

/************************************************************************/

void
Character::SetAnimation(int index)
	{
	m_aniCon->SetAnimation(index);
	}
	
/************************************************************************/

const char*
Character::GetAnimationName() const
{
	return m_aniCon->GetAnimationName();
}

/************************************************************************/

void
Character::SetPosition(const Vector3D& pos)
{
	m_position = pos;

	if(m_boundingSphere)
	{
		Vector3D spherePos = m_position + m_boundPosition + m_boundPositionOffset;
		m_boundingSphere->SetPosition(spherePos);
	}
}

/************************************************************************/

const Vector3D& 
Character::GetPosition() const
{
	return m_position;
}

/************************************************************************/

void
Character::SetRotation(const Vector3D&  rot)
{
	m_rotation = rot;
}

/************************************************************************/

const Vector3D& 
Character::GetRotation() const
{
	return m_rotation;
}

/************************************************************************/

void 
Character::SetScale(float scale)
{
	m_scale = scale;

	if(m_boundingSphere)
	{
		m_boundingSphere->SetRadius(m_boundRadius*m_scale);
	}
}

/************************************************************************/

float
Character::GetScale() const
{
	return m_scale;
}

/************************************************************************/

const char*
Character::GetID() const
{
	return m_ID;
}

/************************************************************************/

void 
Character::SetID(const char* ID)
{
	m_ID = ID;
	if(strcmp(ID, "Player") == 0 || strcmp(ID, "Skeleton") == 0)
	{
		m_isPlayer = true;
	}
	else
	{
		m_isPlayer = false;
	}
}

/************************************************************************/

void
Character::AddWayPoint(const WayPoint* waypoint)
{
	if(m_sourceWaypoint && m_targetWaypoint == 0)
	{
		m_targetWaypoint = waypoint;
		m_waypointTracker = 1;
	}
	if(m_sourceWaypoint == 0)
	{
		m_sourceWaypoint = waypoint;
		SetPosition(m_sourceWaypoint->m_Position);
	}

	assert(m_numWaypoints < c_MaxWayPointCount);
	m_waypointList[m_numWaypoints] = waypoint;
	m_numWaypoints ++;
}

/************************************************************************/

void 
Character::SetBehavior(const char* newBehavior)
{
	if(m_currentBehavior.Length() > 0)
	{
		BehaviorManager::GetInstance()->GetBehavior(m_currentBehavior)->OnExit(this);
	}
	m_currentBehavior = newBehavior;
	BehaviorManager::GetInstance()->GetBehavior(m_currentBehavior)->OnEnter(this);
}

/************************************************************************/

const char* 
Character::GetBehaviourID() const
{
	return m_currentBehavior;
}

/************************************************************************/

const WayPoint*
Character::GetSourceWayPoint() const
{
	return m_sourceWaypoint;
}
/************************************************************************/

const WayPoint*
Character::GetTargetWayPoint() const
{
	if(!m_targetWaypoint)
	{
		return m_sourceWaypoint;
	}
	return m_targetWaypoint;
}

/************************************************************************/

void
Character::ArrivedAtWaypoint()
{
	m_sourceWaypoint = m_targetWaypoint;
	m_waypointTracker++;

	if(m_waypointTracker >= m_numWaypoints)
{
		m_waypointTracker = 0;
	}

	m_targetWaypoint = m_waypointList[m_waypointTracker];
}

/************************************************************************/

Sphere*
Character::GetBoundingSphere() const
{
	return m_boundingSphere;
}

/************************************************************************/

int
Character::GetWayPointCount() const
{
	return m_numWaypoints;
}

/************************************************************************/

const WayPoint*
Character::GetWayPoint(int index) const
{
	if(index < m_numWaypoints)
	{
		return m_waypointList[index];
	}
	return NULL;
}
/************************************************************************/

void 
Character::SetBoundOffset(const Vector3D& boundPos)
{
	m_boundPositionOffset = boundPos;
}

/************************************************************************/

const Vector3D&
Character::GetBoundOffset() const
{
	return m_boundPositionOffset;
}

/************************************************************************/

AnimationInstance*	
Character::GetAnimationInst()const
{
	return m_aniCon;
}

/************************************************************************/

unsigned int		
Character::GetHitCount() const
{
	return m_hitCount;
}

/************************************************************************/

const char*			
Character::GetType() const
{
	return m_Type;
}

/************************************************************************/

void				
Character::SetType(const char* type)
{
	m_Type = type;
}

/************************************************************************/

void				
Character::SetAnimation(const char* aniName)
{
	SetAnimation(GetAnimationIndex(aniName));
}

/************************************************************************/
