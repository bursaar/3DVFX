#include "Types.h"
#include "Vertex.h"
#include "BillBoardRegion.h"
#include "TextureCache.h"
#include "EffectManager.h"
#include "Effect.h"
#include "RenderManager.h"
#include "EnvironmentManager.h"

BillBoardRegion::BillBoardRegion(const char* textureName, const AABB &region, int numBillboards, Vector2D size,bool randomize)
{
	
	
	float tempL = size.x * 0.5f;
	float tempD = size.y * 0.5f;
	Vector3D quadPos = Vector3D(0.0f,0.0f,0.0f);

	D3DVERTEXELEMENT9 elems[MAX_FVF_DECL_SIZE];
	UINT numElems = 0;
	BillBoardVertex::Decl->GetDeclaration(elems,&numElems);

	BillBoardVertex* vertex = 0;
	WORD* index;
	int vertIndex = 0;
	int indexIndex = 0;

	if(SUCCEEDED(D3DXCreateMesh(2 * numBillboards, 4 * numBillboards, D3DXMESH_MANAGED, elems, m_D3DDevice, &m_quadMesh)))
	{
		m_quadMesh->LockVertexBuffer(0,(void**)&vertex);
		m_quadMesh->LockIndexBuffer(0,(void**)&index);


		for(int i = 0; i < numBillboards; ++i)
		{
			if(randomize)
			{
				tempD = GetRandomFloat(1.0f,size.y) * 0.5f;
				tempL = GetRandomFloat(1.0f,size.x) * 0.5f;
			}

			vertex[vertIndex + 0]  = BillBoardVertex(Vector3D(-tempL, tempD, 0.0f),Vector2D(0.0f,0.0f));
			vertex[vertIndex + 1]  = BillBoardVertex(Vector3D( tempL, tempD, 0.0f),Vector2D(1.0f,0.0f));
			vertex[vertIndex + 2]  = BillBoardVertex(Vector3D(-tempL,-tempD, 0.0f),Vector2D(0.0f,1.0f));
			vertex[vertIndex + 3]  = BillBoardVertex(Vector3D( tempL,-tempD, 0.0f),Vector2D(1.0f,1.0f));


			/************************************************************************/
			/* Set the position of each billboard                                   */
			/************************************************************************/
			//Random x z
			quadPos.x = GetRandomFloat(region.GetMin().x,region.GetMax().x);
			quadPos.z = GetRandomFloat(region.GetMin().z,region.GetMax().z);

			Vector3D top = Vector3D(quadPos.x,100,quadPos.z);
			Vector3D bottom = Vector3D(quadPos.x,-100,quadPos.z);
			Vector3D intersection;
			//Get the billboard height
			bool intersects = EnvironmentManager::GetInstance()->TestCollision(top,bottom,intersection);
			
			if (intersects)
			{
				quadPos.y = intersection.y;
			}

			while(!intersects)
			{
				quadPos.x = GetRandomFloat(region.GetMin().x,region.GetMax().x);
				quadPos.z = GetRandomFloat(region.GetMin().z,region.GetMax().z);
				top = Vector3D(quadPos.x,100,quadPos.z);
				bottom = Vector3D(quadPos.x,-100,quadPos.z);
				intersects = EnvironmentManager::GetInstance()->TestCollision(top,bottom,intersection);
			
				if (intersects)
				{
					quadPos.y = intersection.y;
				}
			}

			vertex[vertIndex + 0].quadPosition = quadPos;
			vertex[vertIndex + 1].quadPosition = quadPos;
			vertex[vertIndex + 2].quadPosition = quadPos;
			vertex[vertIndex + 3].quadPosition = quadPos;

			index[indexIndex + 0] = vertIndex + 2; 
			index[indexIndex + 1] = vertIndex + 0; 
			index[indexIndex + 2] = vertIndex + 1;
			index[indexIndex + 3] = vertIndex + 2; 
			index[indexIndex + 4] = vertIndex + 1; 
			index[indexIndex + 5] = vertIndex + 3;


			vertIndex += 4;
			indexIndex += 6;
		}

		m_quadMesh->UnlockVertexBuffer();
		m_quadMesh->UnlockIndexBuffer();

		m_texIndex = TextureCache::GetInstance()->AddTexture(textureName,textureName,true);


		m_flags = BillboardEffect;
		RenderManager::GetInstance()->AddEvent(this, NULL);

	}
}


BillBoardRegion::~BillBoardRegion(void)
{
	if(m_quadMesh)
	{
		m_quadMesh->Release();
		m_quadMesh = 0;
	}
}

void BillBoardRegion::Render()
{
	EffectManager::GetInstance()->GetEffect("Billboard")->SetTexture("m_Texture",TextureCache::GetInstance()->GetTexture(m_texIndex));
	EffectManager::GetInstance()->GetEffect("Billboard")->GetEffect()->CommitChanges();
	m_quadMesh->DrawSubset(0);
}


