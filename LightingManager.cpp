#include "Types.h"
#include "Light.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionalLight.h"
#include "LightingManager.h"

/************************************************************************/

DefineSingleton(LightingManager);

/************************************************************************/

LightingManager::LightingManager() :
	m_numLights(0),
	m_indexCounter(0)
{
}

/************************************************************************/

LightingManager::~LightingManager()
{
	for (int index = 0; index < m_numLights; index ++)
	{
		delete m_lights[index];
	}
}

/************************************************************************/

void
LightingManager::AddPointLight(const char* ID, const Vector3D& position, float range, 
							   const Vector3D& attenuation, float r, float g, float b, float a)
{
	assert(m_numLights < c_MaxNumLights);
	Light* newLight = new PointLight(ID,m_indexCounter,position,range,attenuation,r,g,b,a);
	
	m_lights[m_numLights] = newLight;
	m_numLights ++;
	m_indexCounter++;
}

/************************************************************************/

void
LightingManager::AddSpotLight(const char* ID, const Vector3D& pos, const Vector3D& dir, 
							  const Vector3D& attenuation, float range, float theta,
							  float phi, float falloff, float r, float g, float b, float a)
{
	assert(m_numLights < c_MaxNumLights);
	Light* newLight = new SpotLight(ID,m_indexCounter,pos,dir,attenuation,range,theta,phi,falloff,r,g,b,a);
	m_lights[m_numLights] = newLight;
	m_numLights ++;
	m_indexCounter++;
}

/************************************************************************/

void
LightingManager::AddDirectionalLight(const char* ID, const Vector3D& direction)
{
	assert(m_numLights < c_MaxNumLights);
	Light* newLight = new DirectionalLight(ID,m_indexCounter,direction);
	m_lights[m_numLights] = newLight;
	m_numLights ++;
	m_indexCounter++;
}

/************************************************************************/

void 
LightingManager::SetAllLightsActive()
{
	for (int i = 0; i < m_numLights; i++)
	{
		m_lights[i]->SetActive(true);
	}
}

/************************************************************************/

Light*
LightingManager::GetLight(const char *ID)
{
	for (int i = 0; i < m_numLights; i++)
	{
		if(strcmp(m_lights[i]->GetID(), ID) == 0)
		{
			return m_lights[i];
		}
	}

	return 0;
}

/************************************************************************/

void
LightingManager::RenderLights()
{
	for (int i = 0; i < m_numLights; i++)
	{
		m_lights[i]->RenderLight();
	}
}

/************************************************************************/