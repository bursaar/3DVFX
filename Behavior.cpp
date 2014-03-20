#include "Types.h"
#include "Behavior.h"
#include "Character.h"
#include "CharacterManager.h"
#include "EnvironmentManager.h"
#include "Sphere.h"
#include "CollisionMesh.h"

/*********************************************************************************************************************/

Behavior::Behavior(const char* ID) :
	m_ID(ID)
{
	m_playerCharacter =  CharacterManager::GetInstance()->GetCharacter("Player");
}

/*********************************************************************************************************************/

Behavior::~Behavior()
{
	m_playerCharacter = 0;
}

/*********************************************************************************************************************/

void 
Behavior::FollowTerrain(Character *owner, float elapsedTime)
{
	Vector3D position = owner->GetPosition();
	float radius = owner->GetBoundingSphere()->GetRadius();

	Vector3D top = position;
	top.y += 1.0f;

	Vector3D bottom = position;
	bottom.y = EnvironmentManager::GetInstance()->GetCollisionMesh()->GetBox().GetMin().y;

	Vector3D intersectionPoint;

	if (EnvironmentManager::GetInstance()->TestCollision(top, bottom, intersectionPoint))
	{
		position.y = intersectionPoint.y;
	}
	else
	{
		top.y = EnvironmentManager::GetInstance()->GetCollisionMesh()->GetBox().GetMax().y;
		if (EnvironmentManager::GetInstance()->TestCollision(top, bottom, intersectionPoint))
		{
			position.y = intersectionPoint.y;
		}
	}

	owner->SetPosition(position);
}

/*********************************************************************************************************************/

float
Behavior::AngleToTarget(Character *owner, const Vector3D& targetPos)
{
	const Vector3D& position = owner->GetPosition();

	float angle = atan2f(-(targetPos.x - position.x), -(targetPos.z - position.z));

	return angle;
}

/*********************************************************************************************************************/

void 
Behavior::MoveInDirection(Character* owner, float elapsedTime)
{
	float angle = owner->GetRotation().y;

	Vector3D position = owner->GetPosition();
	Vector3D velocity(-sin(angle), 0.0f, -cos(angle));

	position += velocity * elapsedTime;

	owner->SetPosition(position);

	FollowTerrain(owner,elapsedTime);
}

/*********************************************************************************************************************/

float 
Behavior::DistanceToCharacterSq(Character* owner,const Character& character)
{
	Sphere& temp = *((Character&)character).GetBoundingSphere();
	return DistanceToTargetSq(owner,temp.GetPosition());
}

/*********************************************************************************************************************/

float 
Behavior::DistanceToTargetSq(Character* owner, const Vector3D& targetPos)
{
	Vector3D vecTo =  owner->GetBoundingSphere()->GetPosition() - targetPos;
	vecTo.y = 0.0f;
	return Vector3DDotProduct(&vecTo,&vecTo);	
}

/*********************************************************************************************************************/

TurnDirection 
Behavior::TurnTo(Character* owner, float angle, float speed, float elapsedTime)
{
	Vector3D rotation = owner->GetRotation();
	float targetAngle = angle;
	TurnDirection directionToTurn = TD_FACING;
	if( angle > rotation.y )
	{
		targetAngle -= 2 * D3DX_PI;
	}

	float fDiff = rotation.y - targetAngle;

	if(fDiff < 0.001f )
	{
		return  TD_FACING;
	}

	if( fDiff < D3DX_PI )       // cw turn
	{
		// if we're overturning
		if( rotation.y - speed * elapsedTime <= targetAngle  )
		{
			rotation.y = angle;
			directionToTurn =  TD_FACING;
		}
		else
		{
			rotation.y = float( rotation.y - speed * elapsedTime );
			directionToTurn =  TD_LEFT;
		}
	}
	else                        // ccw turn
	{
		// if we're overturning
		if( rotation.y + speed * elapsedTime - 2 * D3DX_PI >= targetAngle )
		{
			rotation.y = angle;
			directionToTurn =  TD_FACING;
		}
		else
		{
			rotation.y = float( rotation.y + speed * elapsedTime );
			directionToTurn =  TD_RIGHT;	
		}
	}
	owner->SetRotation(rotation);
	return directionToTurn;
}

/*********************************************************************************************************************/