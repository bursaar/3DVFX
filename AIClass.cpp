#include "AIClass.h"


AIClass::AIClass()
{
	stretch = 2.0f;
	speed = 0.055f;
}


AIClass::~AIClass()
{
}


void AIClass::Update(RenderableObject *pRenderableObject)
{
	double posX, posY, posZ;

	pRenderableObject->GetPosition(posX, posY, posZ);
	if (posX <= -17.0f)
	{
		pRenderableObject->RotateY(-180.0f);
		stretch += 3.0f;
		pRenderableObject->Move(0.0f, 0.0f, 0.5f);
	}
	if (posX > -18.0f && posZ > -18.0f)
	{
		if (stretch > 0.0f)
		{
			pRenderableObject->Move(0.0f, 0.0f, speed);
			stretch -= speed;
		}
		else
		{
			switch (rand() % 2)
			{
			case NONE:
				stretch + (rand() % 12);
				break;
			case LEFT:
				pRenderableObject->RotateY(90.0f);
				break;
			case RIGHT:
				pRenderableObject->RotateY(-90.0f);
			}
			stretch = rand() % 10;
		}
	}
}