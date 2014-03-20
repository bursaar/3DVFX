#include "Types.h"
#include "SpotLight.h"

/************************************************************************/

SpotLight::SpotLight(const char* ID, int index, const Vector3D& pos, const Vector3D& dir, 
					 const Vector3D& attenuation, float range, float theta, float phi, 
					 float falloff, float r,float g, float b, float a)
{
	//ZeroMemory presets all values within the m_light to zero
	ZeroMemory(&m_light,sizeof(D3DLIGHT9));
	//Set Light Type
	m_light.Type = D3DLIGHT_SPOT;
	m_index = index;
	SetID(ID);
	SetPosition(pos);
	SetDirection(dir);
	SetAttenuation(attenuation.x,attenuation.y,attenuation.x);
	SetRange(range);
	SetPhi(phi);
	SetTheta(theta);
	SetFallOff(falloff);
	SetDiffuse(r,g,b,a);
}

/************************************************************************/

SpotLight::~SpotLight()
{
}

/************************************************************************/
