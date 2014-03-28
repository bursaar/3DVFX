#include "SphereClass.h"


SphereClass::SphereClass()
{
	mColour = 0;
}


SphereClass::~SphereClass()
{
}

// This method is taken from the Train2Game LIT with minor modifications.
void SphereClass::Initialise(RenderClass * pRenderClass)
{
	D3DXCreateSphere(pRenderClass->m_D3D->d3ddev, 0.5, 20, 20, &mMesh, NULL);
	int verticeCount = mMesh->GetNumFaces();
	CUSTOMVERTEX *pVert;
	if (mMesh->LockVertexBuffer(D3DLOCK_DISCARD, (LPVOID *)&pVert) == S_OK)
	{
		for (int x = 0; x < verticeCount; x++)
		{
			CUSTOMVERTEX vert = pVert[x];
			vertices.push_back(CUSTOMVERTEX(vert.x, vert.y, vert.z, mColour));
		}
		mMesh->UnlockVertexBuffer();
	}
}


void SphereClass::Update(double deltaTime, double totalTime)
{

}
