#ifndef _LIGHTINGMANAGER_H_
#define _LIGHTINGMANAGER_H_

//////////////////////////////////////////////////////////////////////////
//Lighting Manager
//
//The Lighting manager has been created to allow D3D lights to be created
//D3d supports three types of lighting, Directional Lighting, Spot Lighting and Point Lighting
//Here, the user can create a light, which is added to a list, then can be activated at any time.
//////////////////////////////////////////////////////////////////////////

class Light;

class LightingManager : public Singleton<LightingManager>
{
public:
	/**
	 * Constructor
	 */
							LightingManager();
	/**
	 * Destructor
	 */
							~LightingManager();
	/**
	 * Adds a new point light
	 */
	void					AddPointLight(
								const char* ID, ///< The id of the new point light
								const Vector3D& position, ///< The position of the point light
								float range, ///< The distance of the falloff of the light
								const Vector3D& attenuation, ///< Controls the fall off of the point light via the formula Atten = 1 /( attenuation.x + attenuation.y * d + attenuation.z * d2)
								float r, ///< The red component of the lights colour
								float g, ///< The green component of the lights colour
								float b, ///< The blue component of the lights colour
								float a ///< The alpha component of the lights colour
								);
	/**
	 * Adds a new spot light
	 */
	void					AddSpotLight(
								const char* ID, ///< The id of the new spot light
								const Vector3D& pos, ///< The position of the spot light
								const Vector3D& dir, ///< The direction of the spot light
								const Vector3D& attenuation, ///< Controls the fall off of the point light via the formula Atten = 1 /( attenuation.x + attenuation.y * d + attenuation.z * d2)
								float range, ///< The distance of the falloff of the light
								float theta, ///< The inner cone angle
								float phi, ///< The outer cone angle
								float falloff, ///< The falloff factor between the 2 angles of the cone
								float r, ///< The red component of the lights colour
								float g, ///< The green component of the lights colour
								float b, ///< The blue component of the lights colour
								float a ///< The alpha component of the lights colour
								);
	/**
	 * Add a new directional light
	 */
	void					AddDirectionalLight(
								const char* ID, ///< The id of the new light
								const Vector3D& direction ///< The direction of the light
								);
	/**
	 * Returns the light with the specified id
	 */
	Light*					GetLight(
								const char* ID ///< id of the light to return
								);
	/**
	 * Enables all the lights
	 */
	void					SetAllLightsActive();
	/**
	 * Enables a specific light
	 */
	void					SetLightActive(
								const char* ID ///< The id of the light to enable
								);
	/**
	 * Disables all the lights
	 */
	void					SetAllLightsInActive();
	/**
	 * Disables a specific light
	 */
	void					SetLightInActive(
								const char* ID ///< The id of the light to disable
								);
	/**
	 * Binds the lights to the d3d state
	 */
	void					RenderLights();
private:
	int m_indexCounter;
	static const int c_MaxNumLights = 64;
	Light* m_lights[c_MaxNumLights];
	int m_numLights;
};

#endif // _LIGHTINGMANAGER_H_

