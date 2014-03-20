#include "Types.h"
#include "Light.h"
/************************************************************************/

Light::Light() :
	m_active(false)
{
}

/************************************************************************/

Light::~Light()
{
}

/************************************************************************/

void
Light::SetID(const char* ID)
{
	m_lightID = ID;
}

/************************************************************************/

const char*
Light::GetID() const
{
	return m_lightID;
}

/************************************************************************/

void
Light::SetIndex(int index)
{
	m_index = index;
}

/************************************************************************/

void
Light::SetPosition(const Vector3D &position)
{
	m_light.Position = position;

	if(m_active)
	{
		m_D3DDevice->SetLight( m_index, &m_light );
	}
}

/************************************************************************/

const Vector3D&
Light::GetPosition() const 
{
	const Vector3D& pos = (const Vector3D&)m_light.Position;
	return pos;
}

/************************************************************************/

void
Light::SetDirection(const Vector3D& direction)
{
	m_light.Direction = direction;
	
	if(m_active)
	{
		m_D3DDevice->SetLight( m_index, &m_light );
	}
}

/************************************************************************/

const Vector3D&
Light::GetDirection() const 
{
	const Vector3D& direction = (const Vector3D&)m_light.Direction;
	return direction;
}

/************************************************************************/

void
Light::SetAttenuation(float a0,float a1,float a2)
{
	m_light.Attenuation0 = a0;
	m_light.Attenuation1 = a1;
	m_light.Attenuation2 = a2;

	if(m_active)
	{
		m_D3DDevice->SetLight( m_index, &m_light );
	}
}

/************************************************************************/

void
Light::SetRange(float range)
{
	m_light.Range = range;
	
	if(m_active)
	{
		m_D3DDevice->SetLight( m_index, &m_light );
	}

}

/************************************************************************/

void
Light::SetAmbient(float r, float g ,float b, float a)
{
	m_light.Ambient.r = r;
	m_light.Ambient.g = g;
	m_light.Ambient.b = b;
	m_light.Ambient.a = a;
	
	if(m_active)
	{
		m_D3DDevice->SetLight( m_index, &m_light );
	}
}

/************************************************************************/

void
Light::SetDiffuse(float r, float g ,float b, float a)
{
	m_light.Diffuse.r = r;
	m_light.Diffuse.g = g;
	m_light.Diffuse.b = b;
	m_light.Diffuse.a = a;
	
	if(m_active)
	{
		m_D3DDevice->SetLight( m_index, &m_light );
	}
}

/************************************************************************/

void
Light::SetSpecular(float r, float g ,float b, float a)
{
	m_light.Specular.r = r;
	m_light.Specular.g = g;
	m_light.Specular.b = b;
	m_light.Specular.a = a;
	
	if(m_active)
	{
		m_D3DDevice->SetLight( m_index, &m_light );
	}
}

/************************************************************************/

void
Light::SetPhi(float phi)
{
	m_light.Phi = phi;
	
	if(m_active)
	{
		m_D3DDevice->SetLight( m_index, &m_light );
	}
}

/************************************************************************/
void
Light::SetTheta(float theta)
{
	m_light.Theta = theta;
	
	if(m_active)
	{
		m_D3DDevice->SetLight( m_index, &m_light );
	}
}

/************************************************************************/

float
Light::GetTheta() const
{
	return m_light.Theta;
}

/************************************************************************/

void
Light::SetFallOff(float falloff)
{
	m_light.Falloff = falloff;
	
	if(m_active)
	{
		m_D3DDevice->SetLight( m_index, &m_light );
	}
}

/************************************************************************/

void
Light::SetActive(bool active)
{
	m_active = active;
}

/************************************************************************/

int 
Light::GetIndex() const
{
	return m_index;
}

/************************************************************************/

void
Light::RenderLight()
{
	if (m_active)
	{
		m_D3DDevice->LightEnable( GetIndex(), TRUE );
		m_D3DDevice->SetLight( m_index, &m_light );
	}
	else
	{
		m_D3DDevice->LightEnable( GetIndex(), FALSE );
	}
}

/************************************************************************/

Matrix
Light::GetView() const
{
	Matrix view;

	Vector3D up = Vector3D(0,1,0);
	Vector3D at;
	Vector3D pos = m_light.Position;
	at = m_light.Position;
	at += m_light.Direction;
	MatrixLookAtLH(&view, &pos, &at,  &up);

	
	
	/*Vector3D pos = m_light.Position;
	Vector3D dir = m_light.Direction;
	Vector3D Ri;


	Vector3DNormalize(&dir,&dir);

	Vector3DCrossProduct(&Ri,&up,&dir); 

	float x = -Vector3DDotProduct(&pos, &Ri);
	float y = -Vector3DDotProduct(&pos, &up);
	float z = -Vector3DDotProduct(&pos, &dir);

	view(0,0) = Ri.x; 
	view(1,0) = Ri.y; 
	view(2,0) = Ri.z; 
	view(3,0) = x;   

	view(0,1) = up.x;
	view(1,1) = up.y;
	view(2,1) = up.z;
	view(3,1) = y;  

	view(0,2) = dir.x; 
	view(1,2) = dir.y; 
	view(2,2) = dir.z; 
	view(3,2) = z;   

	view(0,3) = 0.0f;
	view(1,3) = 0.0f;
	view(2,3) = 0.0f;
	view(3,3) = 1.0f;*/

	return view;
}

/************************************************************************/
