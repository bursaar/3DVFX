#ifndef _POINTLIGHT_H_
#define _POINTLIGHT_H_

//////////////////////////////////////////////////////////////////////////
//Point Light
//
//This Class creates a PointLight using the light object derived from the
//light class, within the light manager, the user can call AddPointLight,
//the Light object will be added to the Light List and then can be controlled and
//rendered.
//
//Within D3D, a Point Light is can be described like a light bulb, the light
//has position and range, but no direction, therefore, wherever the light is,
//it will shine equally in all directions.
//
//To set up a point light, as well as a position, the user must set up a range
//and Attenuation values. these are described as follow:
//
//Range:	Distance beyond which the light has no effect. 
//			The maximum allowable value for this member is the square root of FLT_MAX.
//
//
//Attenuation (0,1 and 2): How a light's intensity decreases toward the maximum distance specified by the range property
//  
//////////////////////////////////////////////////////////////////////////

#ifndef _LIGHT_H_
#include "light.h"
#endif //#ifndef _LIGHT_H_

class PointLight : public Light
{
public:
	/**
	 * Constructor
	 */
						PointLight(
							const char* ID, ///< The light id
							int index, ///< The d3d light index
							const Vector3D& position, ///< The position of the light
							float range, ///< The range of the light
							const Vector3D& attenuation, ///< the attenuation values for this light
							float r, ///< The red colour of the light
							float g, ///< The green colour of the light
							float b, ///< The blue colour of the light
							float a ///< The alpha colour of the light
							);
	/**
	 * Destructor
	 */
	virtual				~PointLight();
	/**
	 * Returns the type of light this is
	 */
	virtual const char* GetType() const {return "POINTLIGHT";};
};

#endif //#ifndef _POINTLIGHT_H_
