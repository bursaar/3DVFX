#pragma once

#include "RenderableObject.h"

class AIClass
{
public:
	enum TURNS {NONE, LEFT, RIGHT};

	void Update(RenderableObject *pRenderableObject);
	AIClass();
	~AIClass();

private:
	float stretch;
	float speed;
};

