#ifndef _MATERIAL_H_
#define _MATERIAL_H_
#include "Types.h"

//Pre-Defined Colours
const Colour WHITE(1.f, 1.f, 1.f, 1.f);
const Colour BLACK(0.f, 0.f, 0.f, 0.f);


////////////////////////////////////////
//Material Class 
//Stores Colour data for models, specifically, the
//ambient, diffuse and specular colour values.
////////////////////////////////////////
class Material
{
public:
	/**
	 * Constructor
	 */
			Material();
	/**
	 * Constructor with elements
	 */
			Material(
				const Colour& ambient,
				const Colour& diffuse,
				const Colour& specular,
				float specularPower
				);
	/**
	 * Destructor
	 */
			~Material() {}
	/**
	 * D3DMATERIAL9 conversion operator
	 */
	inline operator D3DMATERIAL9*()
	{
		return (D3DMATERIAL9*)(this);
	}

	/// Defined in same order as D3DMATERIAL9 struct so we can interchange the types via a cast
	Colour m_diffuse;
	Colour m_ambient;
	Colour m_specular;
	Colour m_emissive;
	float m_specularPower;
};


#endif//_MATERIAL_H_