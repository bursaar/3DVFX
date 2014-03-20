#include "Types.h"
#include "MeshHierarchy.h"
#include "AnimationInstance.h"
#include "SkinnedMesh.h"
#include "Vertex.h"
#include "EffectManager.h"
#include "Effect.h"
#include "ShadowMesh.h"

const float TRANSITIONTIME = 0.25f;
/************************************************************************/

SkinnedMesh::SkinnedMesh() :
	m_numMeshes(0),
	m_speed(1.f),
	m_track(0),
	m_time(0),
	m_numAnimation(0),
	m_currentAnimationSet(0),
	m_boneMatrices(0),
	m_maxBones(0),
	m_ShadowVolume(0)
{

}

/************************************************************************/

SkinnedMesh::~SkinnedMesh()
{
	if(m_frameRoot)
	{
		MeshHierarchy temp;
		D3DXFrameDestroy(m_frameRoot,&temp);
		m_frameRoot = 0;
	}

	if (m_boneMatrices)
	{
		ZeroMemory(m_boneMatrices, sizeof(Matrix)*m_maxBones);
		delete [] m_boneMatrices;
		m_boneMatrices = 0;
	}
}

/************************************************************************/

bool
SkinnedMesh::Load(const char *fileName)
{
	MeshHierarchy* tempMH = new MeshHierarchy;

	//D3DXLoadMeshHierarchyFromX is a DirectX Command for loading meshes that contain bone hierarchies
	//it also returns a animation controller, containing the animations of the mesh
	HRESULT hr = D3DXLoadMeshHierarchyFromX(fileName,D3DXMESH_MANAGED,m_D3DDevice,tempMH,NULL,&m_frameRoot,&m_aniCon);
	
	//error test
	if(hr != S_OK)
	{
		ErrorMessage("Broken at load in skinned mesh");
		return false;
	}
	
	delete tempMH;
	tempMH = 0;

	//Get number of animations
	if(m_aniCon)
	{
		m_numAnimation = m_aniCon->GetMaxNumAnimationSets();
	}

	//Setup bone matrices
	if(m_frameRoot)
	{
		SetUpBone((Frame*)m_frameRoot,NULL);
		
		m_boneMatrices = new Matrix[m_maxBones];
		ZeroMemory(m_boneMatrices, sizeof(Matrix)*m_maxBones);

	}
	//SetUp the meshes normal map information
	SetUpForNormalMapping();
	
	return true;
}

/************************************************************************/

void
SkinnedMesh::SetUpBone(Frame *baseFrame, Matrix *parentMatrix)
{
	MeshContainer* tempMesh = (MeshContainer*)baseFrame->pMeshContainer;

	//if the frame passed in contains a mesh
	if(tempMesh)
	{
		//add it to the mesh list
		assert(m_numMeshes < c_MaxNumMeshes);
		m_mesh[m_numMeshes] = tempMesh;
		m_numMeshes ++;

		//if the mesh contains skinning information
		if(tempMesh->pSkinInfo && tempMesh->MeshData.pMesh)
		{
			//Get Vertex Element information
			D3DVERTEXELEMENT9 Decl[MAX_FVF_DECL_SIZE];

			if(FAILED(tempMesh->MeshData.pMesh->GetDeclaration(Decl)))
			{
				ErrorMessage("Cannot get decl, Skinned Mesh");
				return;
			}

			//clone mesh to prevent errors
			Mesh* tempMesh1 = 0;
			tempMesh->MeshData.pMesh->CloneMesh(D3DXMESH_MANAGED,Decl,m_D3DDevice,&tempMesh1);

			
			DWORD        numBoneComboEntries = 0;
			ID3DXBuffer* boneComboTable      = 0;
			//convert to index blend mesh
			HRESULT hr = tempMesh->pSkinInfo->ConvertToIndexedBlendedMesh(tempMesh1, D3DXMESH_MANAGED | D3DXMESH_WRITEONLY,  
				35, 0, 0, 0, 0, &m_maxVertInfluences,
				&numBoneComboEntries, &boneComboTable, &tempMesh->m_mesh);

			if(hr != S_OK)
			{
				ErrorMessage("Error ConvertToIndexedBlendedMesh");
			}

			boneComboTable->Release();
		
			
			m_maxBones = max(m_maxBones,(int)tempMesh->pSkinInfo->GetNumBones());
			//for each bone, find its position within the frame and create a frame matrix for that bone.
			for(unsigned int i = 0; i < tempMesh->pSkinInfo->GetNumBones(); i++)
			{
				m_boneNames[i] = tempMesh->pSkinInfo->GetBoneName(i);
				Frame* tempFrame = static_cast<Frame*>(D3DXFrameFind(m_frameRoot, m_boneNames[i]));
				tempMesh->m_frameMatrix[i] = &tempFrame->exCombinedTransformationMatrix;
			}

		}
	}
	//repeat for Sibling and children
	if(baseFrame->pFrameSibling)
	{
		SetUpBone((Frame*)baseFrame->pFrameSibling,parentMatrix);
	}
	
	if(baseFrame->pFrameFirstChild)
	{
		SetUpBone((Frame*)baseFrame->pFrameFirstChild,&baseFrame->exCombinedTransformationMatrix);
	}
}

/************************************************************************/

const Matrix&
SkinnedMesh::GetJointMatrix(const char* name, AnimationInstance* anim) const
{
	for (int i = 0; i < m_maxBones; i++)
	{
		if (strcmp(name,m_boneNames[i])==0)
		{
			return anim->GetBones()[i];
		}
	}
	return anim->GetBones()[0];
}

/************************************************************************/

void
SkinnedMesh::Render(AnimationInstance* anim)
{
	if(m_frameRoot)
	{
		m_currentEffect = EffectManager::GetInstance()->GetEffect("VertexBlend");
		
		static EffectHandle* normalParam = m_currentEffect->GetHandle("m_BoneMatrix");
		m_boneMatrixArrayHandle = normalParam;

		DrawFrame(m_frameRoot, anim);
	}
}

/************************************************************************/

void
SkinnedMesh::RenderShadow(AnimationInstance* anim)
{
	if(m_frameRoot)
	{
		m_currentEffect = EffectManager::GetInstance()->GetEffect("ShadowMap");
		static EffectHandle* shadowParam = m_currentEffect->GetHandle("m_BoneMatrix");
		m_boneMatrixArrayHandle = shadowParam;
		DrawFrame(m_frameRoot, anim);
	}
}

/************************************************************************/

void
SkinnedMesh::DrawFrame(LPD3DXFRAME frame, AnimationInstance* anim) const
{
	static int counter = 0;
	LPD3DXMESHCONTAINER tempContainer = frame->pMeshContainer;
	while (tempContainer)
	{

		DrawContainer(tempContainer,frame,counter, anim);
		tempContainer = tempContainer->pNextMeshContainer;
		counter++;
		
	}
	if (frame->pFrameSibling != NULL)
	{
		DrawFrame(frame->pFrameSibling, anim);
	}

	if (frame->pFrameFirstChild != NULL)
	{
		DrawFrame(frame->pFrameFirstChild, anim);
	}
	if(counter > 0)
	counter --;

}

/************************************************************************/

void
SkinnedMesh::DrawContainer(LPD3DXMESHCONTAINER containerBase, LPD3DXFRAME frameBase,int counter, AnimationInstance* anim) const
{
	Frame* tempframe = (Frame*)frameBase;

	MeshContainer* tempContainer = (MeshContainer*)containerBase;	

	m_currentEffect->SetMatrixArray("m_BoneMatrix", (Matrix*)anim->GetBones(), m_maxBones);
	
	m_currentEffect->GetEffect()->CommitChanges();

	for (unsigned int i = 0; i < tempContainer->NumMaterials; i++)
	{
		EffectManager::GetInstance()->SetTexture((LPDIRECT3DBASETEXTURE9)tempContainer->m_textures[i]);
		EffectManager::GetInstance()->SetNormalMap((LPDIRECT3DBASETEXTURE9)tempContainer->m_NormalMaps[i]);
	
		LPD3DXMESH drawMesh; 
		if(tempContainer->pSkinInfo)
		{
			drawMesh = tempContainer->m_mesh;
		}
		else
		{
			drawMesh =  tempContainer->MeshData.pMesh;
		}

		drawMesh->DrawSubset(i);
	}
}

/************************************************************************/

void
SkinnedMesh::CloneAniCon(AnimationInstance **instance)
{
	*instance = NULL;
	HRESULT hr;
	AnimationInstance * tempInstance = NULL;
	LPD3DXANIMATIONCONTROLLER newAniCon = NULL;

	hr = m_aniCon->CloneAnimationController(m_aniCon->GetMaxNumAnimationOutputs(),
											m_aniCon->GetMaxNumAnimationSets(),
											m_aniCon->GetMaxNumTracks(),
											m_aniCon->GetMaxNumEvents(),
											&newAniCon);

	if (hr != S_OK)
	{
		ErrorMessage("Error in cloning Animation Controller");
	}

	tempInstance = new AnimationInstance();
	tempInstance->CreateAnimationInstance(newAniCon);
	tempInstance->m_boneMatrices = new Matrix[m_maxBones];
	ZeroMemory(tempInstance->m_boneMatrices, sizeof(Matrix) * m_maxBones);
	*instance = tempInstance;

	if(hr != S_OK)
	{
		delete tempInstance;
		newAniCon->Release();
	}
}

/************************************************************************/

LPD3DXFRAME
SkinnedMesh::GetFrameRoot() const
{
	return m_frameRoot;
}

/************************************************************************/

int
SkinnedMesh::GetNumberOfMeshes() const
{
	return m_numMeshes;
}

/************************************************************************/

MeshContainer*
SkinnedMesh::GetMeshContainer(int index)
{
	return m_mesh[index];
}

/************************************************************************/

void
SkinnedMesh::SetUpForNormalMapping()
{
	for (int i = 0; i < m_numMeshes; i++)
	{
		D3DVERTEXELEMENT9 elems[MAX_FVF_DECL_SIZE];
		UINT numElems = 0;
		m_mesh[i]->MeshData.pMesh->GetDeclaration(elems);

		Mesh* tempMesh = 0;
		HRESULT hr = m_mesh[i]->MeshData.pMesh->CloneMesh(D3DXMESH_MANAGED, elems, m_D3DDevice, &tempMesh);
		m_mesh[i]->MeshData.pMesh->Release();

		if(hr != S_OK)
		{
			ErrorMessage("clone mesh failed");
		}

		hr = D3DXComputeTangentFrameEx(tempMesh,D3DDECLUSAGE_TEXCOORD,0,
				D3DDECLUSAGE_BINORMAL , 0,
				D3DDECLUSAGE_TANGENT, 0,  
				D3DDECLUSAGE_NORMAL, 0,  
				0,0,0.01f,0.25f ,0.01f,
				&m_mesh[i]->MeshData.pMesh,0);

		if(hr != S_OK)
		{
			ErrorMessage("D3DXComputeTangentFrameEx failed");
		}

		tempMesh->Release();
	}
}

/************************************************************************/

Mesh* 
SkinnedMesh::GetShadowMesh() const
{
	if(m_ShadowVolume)
	{
		return m_ShadowVolume;
	}
	return 0;
}

/************************************************************************/

int
SkinnedMesh::GetNumberBones() const
{
	return m_maxBones;
}

/************************************************************************/

void
SkinnedMesh::GetMeshForShadow(LPD3DXFRAME frame)
{
	LPD3DXMESHCONTAINER tempContainer = frame->pMeshContainer;
	while (tempContainer)
	{

		MeshContainer* temp = (MeshContainer*)tempContainer;
		ShadowMesh::CreateShadowMesh(temp->MeshData.pMesh,&m_ShadowVolume);
		return;


	}
	if (frame->pFrameSibling != NULL)
	{
		GetMeshForShadow(frame->pFrameSibling);
	}

	if (frame->pFrameFirstChild != NULL)
	{
		GetMeshForShadow(frame->pFrameFirstChild);
	}
}

/************************************************************************/