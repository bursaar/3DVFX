#pragma once
#include "SphereClass.h"
class PlayerClass :
	public SphereClass
{
public:
	PlayerClass() : SphereClass(0xFF0000FF)		// Starting sphere as seen in LIT material
	{

	};
};

