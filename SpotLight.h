#ifndef _SPOTLIGHT_H_
#define _SPOTLIGHT_H_

//////////////////////////////////////////////////////////////////////////
//SpotLight
//
//This Class creates a SpotLight using the light object derived from the
//light class, within the light manager, the user can call AddSpotLight,
//the Light object will be added to the Light List and then can be controlled and
//rendered.
//
//Within D3D, a SpotLight is much like a spot light in the real world,
//it is a light with position and direction, the light can also shine with
//different intercity and range.
//
//In addition to Attenuation and range, a Spot Light requires a Theta, Phi
//and Falloff,
//
//Theta: Angle, in radians, of a spotlight's inner cone - that is, 
//		 the fully illuminated spotlight cone. This value must be in the range from 0 through the value specified by Phi. 
//
//Phi: Angle, in radians, defining the outer edge of the spotlight's outer cone. 
//	   Points outside this cone are not lit by the spotlight. This value must be between 0 and pi. 
//
//Falloff: Decrease in illumination between a spotlight's inner cone (the angle specified by Theta) 
//		   and the outer edge of the outer cone (the angle specified by Phi). 
//		   The effect of falloff on the lighting is subtle. Furthermore, 
//		   a small performance penalty is incurred by shaping the falloff curve. For these reasons, most developers set this value to 1.0. 
//
//
//////////////////////////////////////////////////////////////////////////

#ifndef _LIGHT_H_
#include "Light.h"
#endif //#ifndef _LIGHT_H_

class SpotLight: public Light
{
public:
	/**
	 * Constructor
	 */
						SpotLight(
							const char* ID, ///< The id of the new spot light
							int index, ///< The light index (as used by D3D)
							const Vector3D& pos, ///< The position of the spot light
							const Vector3D& dir, ///< The direction of the spot light
							const Vector3D& attenuation, ///< Controls the fall off of the point light via the formula Atten = 1 /( attenuation.x + attenuation.y * d + attenuation.z * d2)
							float range, ///< The range for which this light effects
							float theta, ///< The inner cone angle
							float phi, ///< The outer cone angle
							float falloff, ///< The falloff factor between the 2 angles of the cone
							float r, ///< The red component of the lights colour
							float g, ///< The green component of the lights colour
							float b, ///< The blue component of the lights colour
							float a ///< The alpha component of the lights colour
							);
	/**
	 * Destructor
	 */
	virtual				~SpotLight();
	/**
	 * Returns the type of light this is
	 */
	virtual const char* GetType() const {return "SPOTLIGHT";};
};

#endif // _SPOTLIGHT_H_