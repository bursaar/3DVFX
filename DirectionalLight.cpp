#include "Types.h"
#include "DirectionalLight.h"

/************************************************************************/

DirectionalLight::DirectionalLight(const char* ID, int index, const Vector3D& direction)
{
	//ZeroMemory presets all values within the m_light to zero
	ZeroMemory(&m_light,sizeof(D3DLIGHT9));
	//Set Light Type
	m_light.Type = D3DLIGHT_DIRECTIONAL;
	SetIndex(index);
	SetID(ID);
	SetDiffuse(1.0f,1.0f,1.0f,1.0f);
	SetIndex(index);
	SetDirection(direction);
}

/************************************************************************/

DirectionalLight::~DirectionalLight()
{
	
}
/************************************************************************/

