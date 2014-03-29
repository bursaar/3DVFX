#include "SphereClass.h"


SphereClass::SphereClass()
{
	mColour = 0xFF00FFFF;
}


SphereClass::~SphereClass()
{
	delete mMesh;
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
			vertices.push_back(CUSTOMVERTEX(vert.x, vert.y, vert.z, mColour, 0.0f, 0.0f));
		}
		mMesh->UnlockVertexBuffer();
	}

	collidable = true;
	radius = 1;

	LPDIRECT3DINDEXBUFFER9 pIndBuf;
	mMesh->GetIndexBuffer(&pIndBuf);

	mIndexBuffer = (IDirect3DIndexBuffer9 *)pIndBuf;

	facecount = mMesh->GetNumFaces();
	mRenderThis = true;
	RenderableObject::Initialise(pRenderClass);

	initialised = true;
}


void SphereClass::Update(double deltaTime, double totalTime)
{
	RenderableObject::Update(deltaTime, totalTime);
}
