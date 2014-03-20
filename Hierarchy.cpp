#include "Types.h"
#include "Hierarchy.h"

#include "Program.h"


/*
	There are a lot of separate objects and buffers
	that get allocated in the mesh hierarchy and these two macros 
	help when freeing up the memory 
*/

#define SAFE_RELEASE(p){if(p)p->Release();p = 0;}
#define SAFE_DELETE_ARRAY(p){if(p)delete []p; p = 0;}


/*
	Creates a new frame object and initializes its matrices to Zero
	and sets its name.
*/
HRESULT Hierarchy::CreateFrame(LPCSTR name, LPD3DXFRAME *newFrame)
{
	*newFrame = 0;

	Frame *tempNewFrame = new Frame;
	ZeroMemory (tempNewFrame,sizeof(Frame));

	MatrixIdentity(&tempNewFrame->TransformationMatrix);
	MatrixIdentity(&tempNewFrame->combinedTransform);

	tempNewFrame->pMeshContainer = 0;
	tempNewFrame->pFrameSibling = 0;
	tempNewFrame->pFrameFirstChild = 0;

	*newFrame = tempNewFrame;

	if(name && strlen(name))
	{
		size_t length = strlen(name) + 1;
		char *newString = new char[length];
		memcpy(newString, name, length*sizeof(char));
		tempNewFrame->Name = (char*)newString;
	}

	return S_OK;
}

/*allocates a new mesh container.*/

HRESULT Hierarchy::CreateMeshContainer(LPCSTR name, 
									   const D3DXMESHDATA *meshData, 
									   const D3DXMATERIAL *materials, 
									   const D3DXEFFECTINSTANCE *effects, 
									   DWORD numMaterials, 
									   const DWORD *adjacency, 
									   LPD3DXSKININFO skinInfo, 
									   LPD3DXMESHCONTAINER *newMeshContainer)
{
	MeshContainer *tempMeshContainer = new MeshContainer;
	ZeroMemory(tempMeshContainer,sizeof(MeshContainer));

	*newMeshContainer = 0;

	if(name && strlen(name))
	{
		size_t length = strlen(name) + 1;
		char *newString = new char[length];
		memcpy(newString, name, length*sizeof(char));
		tempMeshContainer->Name = (char*)newString;
	}

	if(meshData->Type != D3DXMESHTYPE_MESH)
	{
		return E_FAIL;
	}

	tempMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;

	/*
	First allocate the memory for the mesh information.  Materials, Textures
	etc..
	*/

	DWORD numFaces = meshData->pMesh->GetNumFaces();
	tempMeshContainer->pAdjacency = new DWORD[numFaces*3];
	memcpy(tempMeshContainer->pAdjacency, adjacency, sizeof(DWORD) * numFaces*3);

	tempMeshContainer->MeshData.pMesh = meshData->pMesh;
	tempMeshContainer->MeshData.pMesh->AddRef();

	tempMeshContainer->NumMaterials = max(numMaterials,1);
	tempMeshContainer->m_material = new D3DMATERIAL9[tempMeshContainer->NumMaterials];
	tempMeshContainer->m_textures = new LPDIRECT3DTEXTURE9[tempMeshContainer->NumMaterials];
	tempMeshContainer->m_normalMaps = new LPDIRECT3DTEXTURE9[tempMeshContainer->NumMaterials];

	ZeroMemory(tempMeshContainer->m_textures,sizeof(LPDIRECT3DTEXTURE9)*tempMeshContainer->NumMaterials);
	ZeroMemory(tempMeshContainer->m_normalMaps,sizeof(LPDIRECT3DTEXTURE9)*tempMeshContainer->NumMaterials);

	/*
	Load all the materials and textures.  This is the same as you have already done for loading static meshes
	*/
	if(numMaterials > 0)
	{
		for (DWORD i = 0; i < numMaterials; i++)
		{
			tempMeshContainer->m_textures[i] = 0;
			tempMeshContainer->m_normalMaps[i] = 0;
			tempMeshContainer->m_material[i] = materials[i].MatD3D;

			if(materials[i].pTextureFilename)
			{

				/*
				materials[i].pTextureFilename contains the texture filename for this material
				it may be necessary to concatenate this with another string if you have seperate directories
				for your models and textures*/

				
				
				MyString tempString;
				tempString.Format("%s%s%s",Program::GetInstance()->GetDirectory(),ASSETBASETEXTUREPATH,materials[i].pTextureFilename);
				

				HRESULT hr = D3DXCreateTextureFromFile(m_D3DDevice,tempString,&tempMeshContainer->m_textures[i]);
				m_D3DDevice->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
				m_D3DDevice->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);		

				//add scan for the normal Map

				tempString.Format("%s%s%s",Program::GetInstance()->GetDirectory(),ASSETNORMALMAPTEXTUREPATH,materials[i].pTextureFilename);
				hr = D3DXCreateTextureFromFile(m_D3DDevice,tempString,&tempMeshContainer->m_normalMaps[i]);
				if(hr != S_OK)
				{
					tempMeshContainer->m_normalMaps[i] = 0;
				}

			}
		}
	}
	else
	{
		ZeroMemory(&tempMeshContainer->m_material[0],sizeof(D3DMATERIAL9));
		tempMeshContainer->m_material[0].Diffuse.r = 0.5f;
		tempMeshContainer->m_material[0].Diffuse.g = 0.5f;
		tempMeshContainer->m_material[0].Diffuse.b = 0.5f;
		tempMeshContainer->m_material[0].Diffuse.a = 0.5f;
		tempMeshContainer->m_material[0].Specular = tempMeshContainer->m_material[0].Diffuse;
		tempMeshContainer->m_textures[0] = 0;
	}
	/*
	If the geometry contains skinning information then set up the bone offset matrices
	*/

	if(skinInfo)
	{
		tempMeshContainer->pSkinInfo = skinInfo;
		skinInfo->AddRef();

		UINT numberBones = skinInfo->GetNumBones();

		tempMeshContainer->m_boneOffset = new Matrix [numberBones];

		tempMeshContainer->m_frameMatrix = new Matrix *[numberBones];

		for (UINT i = 0; i < numberBones ; i++)
		{
			tempMeshContainer->m_boneOffset[i] = *(tempMeshContainer->pSkinInfo->GetBoneOffsetMatrix(i));
		}		


		/************************************************************************/
		/* Added SHADER BASED SKINNING   
		   First set the mesh up for skinning
		*/
		/************************************************************************/
		
		D3DVERTEXELEMENT9 Decl[MAX_FVF_DECL_SIZE];

		if(FAILED(tempMeshContainer->MeshData.pMesh->GetDeclaration(Decl)))
		{
			ErrorMessage("Cannot get decl, Skinned Mesh");
			return E_FAIL;
		}

		Mesh* tempMesh1 = 0;
		HRESULT hr =  tempMeshContainer->MeshData.pMesh->CloneMesh(D3DXMESH_MANAGED,Decl,m_D3DDevice,&tempMesh1);
		if(hr != S_OK)
		{
			ErrorMessage("Error clone mesh");
		}


		DWORD        numBoneComboEntries = 0;
		ID3DXBuffer* boneComboTable      = 0;
		hr = tempMeshContainer->pSkinInfo->ConvertToIndexedBlendedMesh(tempMesh1, 
			D3DXMESH_MANAGED | D3DXMESH_WRITEONLY,  
			35, 0, 0, 0, 0, 
			&tempMeshContainer->m_maxBonesPerVert,
			&tempMeshContainer->m_numBoneConbinations, 
			&tempMeshContainer->m_boneCombinationTable, 
			&tempMeshContainer->m_mesh);

		if(hr != S_OK)
		{
			ErrorMessage("Error ConvertToIndexedBlendedMesh");
		}

		/************************************************************************/
		/* Added SHADER BASED SKINNING   
		   Set the mesh up for Normal mapping
		*/
		/************************************************************************/
		D3DVERTEXELEMENT9 elems[MAX_FVF_DECL_SIZE];
		UINT numElems = 0;
		tempMeshContainer->MeshData.pMesh->GetDeclaration(elems);

		Mesh* tempMesh = 0;
		hr = tempMeshContainer->MeshData.pMesh->CloneMesh(D3DXMESH_MANAGED, elems, m_D3DDevice, &tempMesh);
		tempMeshContainer->MeshData.pMesh->Release();

		if(hr != S_OK)
		{
			ErrorMessage("clone mesh failed");
		}

		hr = D3DXComputeTangentFrameEx(tempMesh,D3DDECLUSAGE_TEXCOORD,0,
			D3DDECLUSAGE_BINORMAL , 0,
			D3DDECLUSAGE_TANGENT, 0,  
			D3DDECLUSAGE_NORMAL, 0,  
			0,0,0.01f,0.25f ,0.01f,
			&tempMeshContainer->MeshData.pMesh,0);

		if(hr != S_OK)
		{
			ErrorMessage("D3DXComputeTangentFrameEx failed");
		}

		tempMesh->Release();

	}
	else
	{
		tempMeshContainer->pSkinInfo = 0;
		tempMeshContainer->m_boneOffset = 0;
		tempMeshContainer->m_mesh = 0;
		tempMeshContainer->m_frameMatrix = 0;
	}


	*newMeshContainer = tempMeshContainer;
	return S_OK;
}

/* releases a frame object and frees up memory*/
HRESULT Hierarchy::DestroyFrame(LPD3DXFRAME frame)
{
	Frame *temp = (Frame*)frame;
	if(!temp)
	{
		return S_OK;
	}
	SAFE_DELETE_ARRAY(temp->Name);
	delete temp;
	return S_OK;
}

/*
	Releases a mesh container.
*/
HRESULT Hierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER meshContainerToFree)
{
	MeshContainer* temp = (MeshContainer*) meshContainerToFree;

	if(!temp)
	{
		return S_OK;
	}
	SAFE_DELETE_ARRAY(temp->Name);
	SAFE_DELETE_ARRAY(temp->m_material);
	

	if(temp->m_textures)
	{
		for (UINT i = 0; i < temp->NumMaterials; i++)
		{
			if(temp->m_textures[i])
			{
				SAFE_RELEASE(temp->m_textures[i]);
			}
		}

		SAFE_DELETE_ARRAY(temp->m_textures);
	}
	
	SAFE_DELETE_ARRAY(temp->pAdjacency);
	SAFE_DELETE_ARRAY(temp->m_boneOffset);
	// frame matrices
	SAFE_DELETE_ARRAY(temp->m_frameMatrix);
	// release skin mesh
	SAFE_RELEASE(temp->m_mesh);	
	// release the main mesh
	SAFE_RELEASE(temp->MeshData.pMesh);
	SAFE_RELEASE( temp->m_boneCombinationTable );
	// release skin information
	SAFE_RELEASE(temp->pSkinInfo);		
	// finally delete the mesh container itself
	delete temp;
	temp=0;

	return S_OK;
}

