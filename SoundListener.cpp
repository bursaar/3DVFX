#include "Types.h"
#include "SoundListener.h"

/*****************************************************************************************/

SoundListener::SoundListener(const char* ID) : 
	m_listener(NULL)
{
	m_ID = ID;
}

/*****************************************************************************************/

SoundListener::~SoundListener()
{
	if(m_listener)
	{
		m_listener->Release();
		m_listener = 0;
	}
}

/*****************************************************************************************/

void 
SoundListener::InitParams()
{
	m_listenerParameters.dwSize = sizeof(DS3DLISTENER);
	m_listener->GetAllParameters( &m_listenerParameters );
}

/*****************************************************************************************/

void 
SoundListener::SetParams(float distance, float doppler, float rollOff, bool defer)
{
	m_listenerParameters.flDistanceFactor = distance;
	m_listenerParameters.flDopplerFactor = doppler;
	m_listenerParameters.flRolloffFactor = rollOff;

	if(!defer)
	{
		m_listener->SetAllParameters( &m_listenerParameters, DS3D_IMMEDIATE);			
	}
	else
	{
		//parameters won't be set until CommitDeferredSettings is called in update
		m_listener->SetAllParameters( &m_listenerParameters, DS3D_DEFERRED);
	}
}

/*****************************************************************************************/

Vector3D 
SoundListener::GetPosition() const
{
	Vector3D pos;
	m_listener->GetPosition(&pos);
	return pos;
}

/*****************************************************************************************/

Vector3D 
SoundListener::GetVelocity() const
{
	Vector3D vel;
	m_listener->GetPosition(&vel);
	return vel;
}

/*****************************************************************************************/

Vector3D 
SoundListener::GetForward() const
{
	Vector3D fwd;
	Vector3D up;
	m_listener->GetOrientation(&fwd, &up);
	return fwd;
}

/*****************************************************************************************/

void 
SoundListener::SetPosition(const Vector3D& pos, bool defer /* = false */)
{
	if( m_listener )
	{
		m_listenerParameters.vPosition = pos;
		if(!defer)
		{
			m_listener->SetPosition(pos.x,pos.y,pos.z,DS3D_IMMEDIATE);
		}
		else
		{
			m_listener->SetPosition(pos.x,pos.y,pos.z,DS3D_DEFERRED);
		}
	}
}

/*****************************************************************************************/

void 
SoundListener::SetVelocity(const Vector3D& vel, bool defer /* = false */)
{
	if( m_listener )
	{
		m_listenerParameters.vVelocity = vel;
		if(!defer)
		{
			m_listener->SetVelocity(vel.x,vel.y,vel.z,DS3D_IMMEDIATE);
		}
		else
		{
			m_listener->SetVelocity(vel.x,vel.y,vel.z,DS3D_DEFERRED);
		}
	}
}

/*****************************************************************************************/

void 
SoundListener::SetForward(const Vector3D &fwd, bool defer /* = false */)
{
	if( m_listener )
	{
		m_listenerParameters.vOrientFront = fwd;
		if(!defer)
		{
			m_listener->SetOrientation(fwd.x,fwd.y,fwd.z, 0.0f, 1.0f, 0.0f, DS3D_IMMEDIATE);
		}
		else
		{
			m_listener->SetOrientation(fwd.x,fwd.y,fwd.z, 0.0f, 1.0f, 0.0f, DS3D_DEFERRED);
		}
	}
}

/*****************************************************************************************/

void 
SoundListener::Update()
{
	if( m_listener )
	{		
		m_listener->CommitDeferredSettings();			
	}
}

/*****************************************************************************************/
