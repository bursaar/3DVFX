#include "Types.h"
#include "PointLight.h"

/************************************************************************/

PointLight::PointLight(const char* ID, int index, const Vector3D& position, float range, 
					   const Vector3D& attenuation, float r,float g, float b, float a)
{
	//ZeroMemory presets all values within the m_light to zero
	ZeroMemory( &m_light, sizeof(D3DLIGHT9) );
	//Set Light Type
	m_light.Type = D3DLIGHT_POINT;
	SetID(ID);
	SetPosition(position);
	SetRange(range);
	SetAttenuation(attenuation.x,attenuation.y,attenuation.z);
	SetDiffuse(r,g,b,a);
	SetIndex(index);
	m_D3DDevice->SetLight(m_index,&m_light);
}

/************************************************************************/

PointLight::~PointLight()
{
}

/************************************************************************/
