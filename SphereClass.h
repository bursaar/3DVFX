#pragma once

#include "RenderableObject.h"
#include <iostream>

class SphereClass :
	public RenderableObject
{
public:
	SphereClass();
	// Add overloaded constructor from LIT materials to enable creation of a sphere of a certain colour.
	SphereClass(DWORD pColour)
		:mColour(pColour){}
	~SphereClass();
private:

	DWORD mColour;

	// For creating the sphere manuallly
	int ui_ShapeCount;
	int ui_VCount;
	CUSTOMVERTEX *arr_Vertices;
	bool createSphereManually = true;

public:
	void Initialise(RenderClass * pRenderClass) override;
	void Update(double deltaTime, double totalTime) override;
	LPD3DXMESH mMesh;
	void CreateSphereManually();
};
