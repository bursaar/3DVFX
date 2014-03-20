#ifndef _LIGHT_H_
#define _LIGHT_H_

//////////////////////////////////////////////////////////////////////////
//Light Class
//
//The Light class is a base class for each of the three lighting classes,
//this class contains functions that allows aspects of each of the three lights be be changed
//(though not all values changes will effect every light type)
//
//The activation / deactivation of is also controlled here.
//////////////////////////////////////////////////////////////////////////

class Light
{
public:
	/**
	 * Constructor
	 */
							Light();
	/**
	 * Destructor
	 */
	virtual					~Light();
	/**
	 * Vritual function to return the type of light this is
	 */
	virtual const char*		GetType() const {return "BASE";};
	/**
	 * Sets the id of the light
	 */
	void					SetID(
								const char* ID
								);
	/**
	 * Gets the id of the light
	 */
	const char*				GetID() const;
	/**
	 * Sets the light index to use when bound to D3D
	 */
	void					SetIndex(
								int index
								);
	/**
	 * Sets the position of the light
	 */
	void					SetPosition(
								const Vector3D& position
								);
	/**
	 * Returns the position of the light
	 */
	const Vector3D&			GetPosition() const;
	/**
	 * Sets the direction of the light
	 */
	void					SetDirection(
								const Vector3D& direction
								);
	/**
	 * Returns the direction of the light
	 */
	const Vector3D&			GetDirection() const;
	/**
	 * Sets the light attenuation values
	 */
	void					SetAttenuation(
								float a0,
								float a1,
								float a2
								);
	/**
	 * Sets the range of the light
	 */
	void					SetRange(
								float range
								);
	/**
	 * Sets the ambient colours of the light
	 */
	void					SetAmbient(
								float r, 
								float g,
								float b, 
								float a
								);
	/**
	 * Sets the diffuse colour of the light
	 */
	void					SetDiffuse(
								float r, 
								float g,
								float b, 
								float a
								);
	/**
	 * Sets the specular colour of the light
	 */
	void					SetSpecular(
								float r, 
								float g,
								float b, 
								float a
								);
	/**
	 * Sets the outer cone angle
	 */
	void					SetPhi(
								float phi
								);
	/**
	 * Sets the falloff factor beteen the cone angles
	 */
	void					SetFallOff(
								float falloff
								);
	/**
	 * Sets the inner cone angle
	 */
	void					SetTheta(
								float theta
								);
	/**
	 * Returns the inner cone angle
	 */
	float					GetTheta() const;
	/**
	 * Sets the light active or disabled
	 */
	void					SetActive(
								bool active
								);
	/**
	 * Binds the light to the d3d state
	 */
	void					RenderLight();
	/**
	 * Returns the light index
	 */
	int						GetIndex() const;
	/**
	 * Builds a view matrix for this light
	 */
	Matrix					GetView() const;
protected:
	MyString m_lightID;
	int m_index;
	D3DLIGHT9 m_light;
	bool m_active;
};
#endif //_LIGHT_H_
