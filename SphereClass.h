#pragma once

class SphereClass
{
public:
	SphereClass();
	~SphereClass();

	static IDirect3DVertexBuffer9* mSphereVertexBuffer;

	static int mNumSphereVerts;

	static int mNumSpheres;

	Vector3D mPosition;
	float mRadius;
	DWORD mColour;
	void RenderSphere(bool wireframe = true);

private:
	void CreateWireFrameSphere();
};

