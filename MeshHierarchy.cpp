#include "Types.h"
#include "MeshHierarchy.h"
#include "Program.h"

/*****************************************************************************************/

HRESULT 
MeshHierarchy::CreateFrame(LPCSTR name, LPD3DXFRAME *newFrame)
{
	*newFrame = 0;

	Frame* tempNewFrame = new Frame;
	ZeroMemory (tempNewFrame,sizeof(Frame));

	MatrixIdentity(&tempNewFrame->TransformationMatrix);
	MatrixIdentity(&tempNewFrame->exCombinedTransformationMatrix);

	tempNewFrame->pMeshContainer = 0;
	tempNewFrame->pFrameSibling = 0;
	tempNewFrame->pFrameFirstChild = 0;

	*newFrame = tempNewFrame;

	if(name && name[0] != '\0')
	{
		/// duplicate the name and store in the frame
		tempNewFrame->Name = strdup(name);
	}

	return S_OK;
}

/*****************************************************************************************/

HRESULT
MeshHierarchy::CreateMeshContainer(LPCSTR name, CONST D3DXMESHDATA *meshData, CONST D3DXMATERIAL *materials, CONST D3DXEFFECTINSTANCE *effects, DWORD numMaterials, CONST DWORD *adjacency, LPD3DXSKININFO skinInfo, LPD3DXMESHCONTAINER *newMeshContainer)
{
	MeshContainer *tempMeshContainer = new MeshContainer;
	ZeroMemory(tempMeshContainer,sizeof(MeshContainer));

	*newMeshContainer = 0;

	if(name && strlen(name))
	{
		/// duplicate the name and store in the mesh container
		tempMeshContainer->Name = strdup(name);
	}
	
	if(meshData->Type != D3DXMESHTYPE_MESH)
	{
		return E_FAIL;
	}

	tempMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;
	
	DWORD numFaces = meshData->pMesh->GetNumFaces();
	tempMeshContainer->pAdjacency = new DWORD[numFaces*3];
	memcpy(tempMeshContainer->pAdjacency, adjacency, sizeof(DWORD) * numFaces*3);

	tempMeshContainer->MeshData.pMesh = meshData->pMesh;
	tempMeshContainer->MeshData.pMesh->AddRef();

	tempMeshContainer->NumMaterials = max(numMaterials,1);
	tempMeshContainer->m_material = new D3DMATERIAL9[tempMeshContainer->NumMaterials];
	tempMeshContainer->m_textures = new LPDIRECT3DTEXTURE9[tempMeshContainer->NumMaterials];
	tempMeshContainer->m_NormalMaps = new LPDIRECT3DTEXTURE9[tempMeshContainer->NumMaterials];

	ZeroMemory(tempMeshContainer->m_textures,sizeof(LPDIRECT3DTEXTURE9)*tempMeshContainer->NumMaterials);
	ZeroMemory(tempMeshContainer->m_NormalMaps,sizeof(LPDIRECT3DTEXTURE9)*tempMeshContainer->NumMaterials);
	
	if(numMaterials > 0)
	{
		for (DWORD i = 0; i < numMaterials; i++)
		{
			tempMeshContainer->m_textures[i] = 0;
			tempMeshContainer->m_NormalMaps[i] = 0;
			tempMeshContainer->m_material[i] = materials[i].MatD3D;

			if(materials[i].pTextureFilename)
			{

				MyString tempString;
				tempString.Format("%s%s%s",Program::GetInstance()->GetDirectory(),ASSETBASETEXTUREPATH,materials[i].pTextureFilename);
				
				HRESULT hr = D3DXCreateTextureFromFile(m_D3DDevice,tempString,&tempMeshContainer->m_textures[i]);

				//add scan for the normal Map
				tempString.Format("%s%s%s",Program::GetInstance()->GetDirectory(),ASSETNORMALMAPTEXTUREPATH,materials[i].pTextureFilename);
				hr = D3DXCreateTextureFromFile(m_D3DDevice,tempString,&tempMeshContainer->m_NormalMaps[i]);

				if(hr != S_OK)
				{
					tempMeshContainer->m_NormalMaps[i] = 0;
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

/*****************************************************************************************/

HRESULT
MeshHierarchy::DestroyFrame(LPD3DXFRAME frame)
{
	Frame *temp = (Frame*)frame;
	if(!temp)
	{
		return S_OK;
	}
	
	if(temp->Name)
	{
		/// Release the duplicated name
		free(temp->Name);
		temp->Name = 0;
	}

	delete temp;

	return S_OK;
}

/*****************************************************************************************/

HRESULT
MeshHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER meshContainerToFree)
{
	MeshContainer* temp = (MeshContainer*) meshContainerToFree;

	if(!temp)
	{
		return S_OK;
	}

	if(temp->Name)
	{
		/// Release the duplicated name
		free(temp->Name);
		temp->Name = 0;
	}

	if(temp->m_material)
	{
		delete [] temp->m_material;
		temp->m_material = 0;
	}

	if(temp->m_textures)
	{
		for (UINT i = 0; i < temp->NumMaterials; i++)
		{
			if(temp->m_textures[i])
			{
				temp->m_textures[i]->Release();
			}
		}

		delete [] temp->m_textures;
	}

	if(temp->m_NormalMaps)
	{
		for (UINT i = 0; i < temp->NumMaterials; i++)
		{
			if(temp->m_NormalMaps[i])
			{
				temp->m_NormalMaps[i]->Release();
			}
		}

		delete [] temp->m_NormalMaps;
	}

	if(temp->pAdjacency)
	{
		delete [] temp->pAdjacency;
	}

	if (temp->m_boneOffset)
	{
		delete [] temp->m_boneOffset;
		temp->m_boneOffset = 0;
	}

	// frame matrices
	if (temp->m_frameMatrix)
	{
		delete [] temp->m_frameMatrix;
		temp->m_frameMatrix=0;
	}

	// release skin mesh
	if (temp->m_mesh)
	{
		temp->m_mesh->Release();
		temp->m_mesh=0;
	}

	// release the main mesh
	if (temp->MeshData.pMesh)
	{
		temp->MeshData.pMesh->Release();
		temp->MeshData.pMesh=0;
	}

	// release skin information
	if (temp->pSkinInfo)
	{
		temp->pSkinInfo->Release();
		temp->pSkinInfo=0;
	}

	// finally delete the mesh container itself
	delete temp;

	return S_OK;
}

/*****************************************************************************************/
