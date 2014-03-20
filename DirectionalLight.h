#ifndef _DIRECTIONALLIGHT_H_
#define _DIRECTIONALLIGHT_H_
//////////////////////////////////////////////////////////////////////////
//Directional Light
//
//This Class creates a directional light using the light object derived from
//the Light Class, within the light manager, the user can call AddDirectionalLight,
//the Light object will be added to the Light List and then can be controlled and
//rendered.
//
//Within D3D, a directional light has direction only, it does not have position, 
//any object with an opposing normal value to the direction light will be illuminated. 
//////////////////////////////////////////////////////////////////////////

#ifndef _LIGHT_H_
#include "Light.h"
#endif //#ifndef _LIGHT_H_

class DirectionalLight : public Light
{
public:
	/**
	 * Constructor
	 */
							DirectionalLight(
								const char* ID, ///< The id of the light
								int index, ///< The light index to bind to in d3d
								const Vector3D& direction ///< The direction of the light
								);
	/**
	 * Destructor
	 */
	virtual					~DirectionalLight();
	/**
	 * Returns the type of light this is
	 */
	virtual const char*		GetType() const {return "DIRECTIONALLIGHT";};

};

#endif // _DIRECTIONALLIGHT_H_

