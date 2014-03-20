#include "Model.h"
#include "CameraController.h"
#include "Program.h"
#include "Vertex.h"
#include "RenderManager.h"
#include "EffectManager.h"
#include "Effect.h"
#include "TextureCache.h"

/*****************************************************************************************/

Model::Model() :
	m_position(Vector3D(0,0,0)),
	m_rotation(Vector3D(0,0,0)),
	m_scale(1.0f)
{
}

/*****************************************************************************************/

Model::Model(const char* fileName) :
	m_position(Vector3D(0,0,0)),
	m_rotation(Vector3D(0,0,0)),
	m_scale(1.0f)
{
	LoadModel(fileName);
}

/*****************************************************************************************/

Model::Model(const char* fileName, const Vector3D& position, const Vector3D& rotation, float scale):
	m_position(position),
	m_rotation(rotation),
	m_scale(scale)
{
	LoadModel(fileName);
}

/*****************************************************************************************/

Model::~Model(void)
{
	m_mesh->Release();
	m_mesh = 0;
	m_materials.clear();
	m_textureIndexList.clear();
	m_normalMapsIndexList.clear();
}

/*****************************************************************************************/

bool
Model::LoadModel(const char *fileName)
{
	m_cutterSubset = -1;
	m_navmeshSubset = -1;

	//Load the model into a system memory mesh
	Mesh* meshSys = 0;
	ID3DXBuffer* adjBuffer = 0;
	ID3DXBuffer* materialBuffer = 0;
	DWORD numberMaterials = 0;

	//load the x model
	D3DXLoadMeshFromX(fileName,D3DXMESH_SYSTEMMEM,m_D3DDevice,&adjBuffer,&materialBuffer,0,&numberMaterials,&meshSys);

	//The Model is loaded, now, check to see if the model contains 
	//normal data, this will be used later on for effects
	//if they don't d3d can create them
	D3DVERTEXELEMENT9 elems[MAX_FVF_DECL_SIZE];
	meshSys->GetDeclaration(elems);

	bool modelHasNormals = false;

	D3DVERTEXELEMENT9 term = D3DDECL_END();
	for (int i = 0; i < MAX_FVF_DECL_SIZE; i++)
	{
		if(elems[i].Stream == 0xff)
		{
			break;
		}

		if(elems[i].Type == D3DDECLTYPE_FLOAT3 && elems[i].Usage == D3DDECLUSAGE_NORMAL && elems[i].UsageIndex == 0)
		{
			modelHasNormals = true;
			break;
		}
	}

	//The Model will now be converted to support a created vertex type,
	//in this case, the VertexPositionNormalTexCoord type

	D3DVERTEXELEMENT9 elements[64];
	meshSys->GetDeclaration(elements);

	meshSys->CloneMesh(D3DXMESH_SYSTEMMEM,elements,m_D3DDevice,&m_mesh);
	meshSys->Release();

	//With the Mesh Copied and converted to the VertexPositionNormalTexCoord type
	//if the model didn't contain normal data, we will create it, as it can now be
	//stored within the VertexPositionNormalTexCoord type

	if(!modelHasNormals)
	{
		D3DXComputeNormals(m_mesh,0);
	}

	adjBuffer->Release();

	D3DVERTEXELEMENT9 elems1[MAX_FVF_DECL_SIZE];
	UINT numElems = 0;
	m_mesh->GetDeclaration(elems1);

	Mesh* tempMesh = 0;
	HRESULT hr = m_mesh->CloneMesh(D3DXMESH_MANAGED, elems1, m_D3DDevice, &tempMesh);
	m_mesh->Release();

	if(hr != S_OK)
	{
		ErrorMessage("clone mesh failed");
	}


	hr = D3DXComputeTangentFrameEx(tempMesh,D3DDECLUSAGE_TEXCOORD,0,
		D3DDECLUSAGE_BINORMAL , 0,
		D3DDECLUSAGE_TANGENT, 0,  
		D3DDECLUSAGE_NORMAL, 0,  
		0,0,0.01f,0.25f ,0.01f,
		&m_mesh,0);

	if(hr != S_OK)
	{
		ErrorMessage("D3DXComputeTangentFrameEx failed");
	}




	//The model is ready, now we need to load the textures and materials
	//(if any)
	if(materialBuffer != 0 && numberMaterials != 0)
	{
		D3DXMATERIAL* d3dxmaterial = (D3DXMATERIAL*)materialBuffer->GetBufferPointer();

		for(DWORD i = 0; i < numberMaterials; i++)
		{
			// Note: the MatD3D property does not have an ambient
			// value set when its loaded, so just set it to the diffuse value.
			Material m;
			
			m.m_ambient = d3dxmaterial[i].MatD3D.Diffuse;
			m.m_diffuse = d3dxmaterial[i].MatD3D.Diffuse;
			m.m_specular = d3dxmaterial[i].MatD3D.Specular;
			m.m_specularPower = d3dxmaterial[i].MatD3D.Power;

			m_materials.push_back(m);

			//check if this material has a external texture;

			int textureIndex = -1;
			int normalMapIndex = -1;

			if(d3dxmaterial[i].pTextureFilename != 0)
			{
				if (_stricmp(d3dxmaterial[i].pTextureFilename, "CUTTER") == 0)
				{
					m_cutterSubset = i;
				}
				else if (_stricmp(d3dxmaterial[i].pTextureFilename, "NAVMESH") == 0)
				{
					m_navmeshSubset = i;
				}
				else
				{
					MyString tempString;
					tempString.Format("%s%s%s",Program::GetInstance()->GetDirectory(),ASSETBASETEXTUREPATH,d3dxmaterial[i].pTextureFilename);
					textureIndex = TextureCache::GetInstance()->AddTexture(tempString,tempString,true);

					tempString.Format("%s%s%s",Program::GetInstance()->GetDirectory(),ASSETNORMALMAPTEXTUREPATH,d3dxmaterial[i].pTextureFilename);
					normalMapIndex = TextureCache::GetInstance()->AddTexture(tempString,tempString,true);
				}
			}

			m_textureIndexList.push_back( textureIndex );
			m_normalMapsIndexList.push_back( normalMapIndex );
		}

	}
	materialBuffer->Release();
	m_fileName = fileName;
	//model is ready
	return true;
}

/*****************************************************************************************/

void
Model::Render()
{
	if(m_mesh)
	{

		m_D3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		Matrix world, scale, position;
		Matrix rotateX, rotateY, rotateZ;

		MatrixScaling(&scale, m_scale, m_scale, m_scale);

		MatrixRotationZ(&rotateZ, m_rotation.z);
		MatrixRotationY(&rotateY, m_rotation.y);
		MatrixRotationX(&rotateX, m_rotation.x);


		MatrixTranslation(&position, m_position.x, m_position.y, m_position.z);

		MatrixMultiply(&world, &scale, &rotateZ);
		MatrixMultiply(&world, &world, &rotateY);
		MatrixMultiply(&world, &world, &rotateX);

		MatrixMultiply(&world, &world, &position);

		CameraController::GetInstance()->SetWorld(world);

		for(int j = 0; j < (int)m_materials.size(); j++)
		{
			m_D3DDevice->SetMaterial(m_materials[j]);
			m_D3DDevice->SetTexture( 0, (LPDIRECT3DBASETEXTURE9)TextureCache::GetInstance()->GetTexture(m_textureIndexList[j]));
				m_mesh->DrawSubset(j);	
			}
		m_D3DDevice->SetTexture(0,NULL);
	
		CameraController::GetInstance()->ResetWorld();
		m_D3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}

/*****************************************************************************************/

void
Model::RenderWithNormalMap()
{
	Matrix tempworld;

	MatrixIdentity(&tempworld);
	Matrix world, scale, position;
	Matrix rotateX, rotateY, rotateZ;

	MatrixScaling(&scale, m_scale, m_scale , m_scale);

	MatrixRotationZ(&rotateZ, m_rotation.z);
	MatrixRotationY(&rotateY, m_rotation.y);
	MatrixRotationX(&rotateX, m_rotation.x);

	MatrixTranslation(&position, m_position.x, m_position.y, m_position.z);

	MatrixMultiply(&world, &scale, &rotateZ);
	MatrixMultiply(&world, &world, &rotateY);
	MatrixMultiply(&world, &world, &rotateX);

	MatrixMultiply(&world, &world, &position);

	Effect* effect = EffectManager::GetInstance()->GetEffect("NormalMapEffect");

	effect->SetMatrix("m_View",CameraController::GetInstance()->GetView());
	effect->SetMatrix("m_World",world);
	effect->SetMatrix("m_Projection",CameraController::GetInstance()->GetProjection());

	effect->SetMatrix("m_WVP", world * CameraController::GetInstance()->GetViewProjection());

	for(int j = 0; j < (int)m_materials.size(); j++)
	{
		if (j != m_cutterSubset && j != m_navmeshSubset)
		{
			EffectManager::GetInstance()->SetTexture((LPDIRECT3DBASETEXTURE9)TextureCache::GetInstance()->GetTexture(m_textureIndexList[j]));
			EffectManager::GetInstance()->SetNormalMap((LPDIRECT3DBASETEXTURE9)TextureCache::GetInstance()->GetTexture(m_normalMapsIndexList[j]));
			effect->GetEffect()->CommitChanges();
			m_mesh->DrawSubset(j);
		}
	}
}

/*****************************************************************************************/

void 
Model::RenderWithShadow()
{
	if(m_mesh)
	{
		Matrix world, scale, position;
		Matrix rotateX, rotateY, rotateZ;

		MatrixScaling(&scale, m_scale, m_scale , m_scale);

		MatrixRotationZ(&rotateZ, m_rotation.z);
		MatrixRotationY(&rotateY, m_rotation.y);
		MatrixRotationX(&rotateX, m_rotation.x);

		MatrixTranslation(&position, m_position.x, m_position.y, m_position.z);

		MatrixMultiply(&world, &scale, &rotateZ);
		MatrixMultiply(&world, &world, &rotateY);
		MatrixMultiply(&world, &world, &rotateX);

		MatrixMultiply(&world, &world, &position);

		Effect* shadowMapEffect = EffectManager::GetInstance()->GetEffect("ShadowMap");

		shadowMapEffect->SetMatrix("m_World", world);

		for(int j = 0; j < (int)m_materials.size(); j++)
		{
			if (j != m_cutterSubset && j != m_navmeshSubset)
			{
				Vector4D v = Vector4D(0.8f,0.8f,0.8f,1.0f);

				shadowMapEffect->SetVector4("m_Mat", v);
				shadowMapEffect->GetEffect()->SetTexture(shadowMapEffect->GetHandle("m_Texture")->m_handle, (Texture*)TextureCache::GetInstance()->GetTexture(m_textureIndexList[j]));
				shadowMapEffect->GetEffect()->SetTexture(shadowMapEffect->GetHandle("m_NormalTexture")->m_handle, (Texture*)TextureCache::GetInstance()->GetTexture(m_normalMapsIndexList[j]));

				shadowMapEffect->GetEffect()->CommitChanges();
				m_mesh->DrawSubset(j);
			}
		}
	}
}

/*****************************************************************************************/

void 
Model::RenderWithShadowVolume()
{
	if(m_mesh)
	{
		Matrix world, scale, position;
		Matrix rotateX, rotateY, rotateZ;

		MatrixScaling(&scale, m_scale, m_scale , m_scale);

		MatrixRotationZ(&rotateZ, m_rotation.z);
		MatrixRotationY(&rotateY, m_rotation.y);
		MatrixRotationX(&rotateX, m_rotation.x);


		MatrixTranslation(&position, m_position.x, m_position.y, m_position.z);

		MatrixMultiply(&world, &scale, &rotateZ);
		MatrixMultiply(&world, &world, &rotateY);
		MatrixMultiply(&world, &world, &rotateX);

		MatrixMultiply(&world, &world, &position);

		m_D3DDevice->SetVertexDeclaration(VertexPositionNormalTexCoord::Decl);

		Effect* shadowVolumeEffect = EffectManager::GetInstance()->GetEffect("ShadowVolume");
		shadowVolumeEffect->SetMatrix("m_World", world);
		shadowVolumeEffect->SetMatrix("m_View", CameraController::GetInstance()->GetView());
		shadowVolumeEffect->SetMatrix("m_Proj", CameraController::GetInstance()->GetProjection());
		shadowVolumeEffect->SetMatrix("m_WorldView", world * CameraController::GetInstance()->GetView());
		shadowVolumeEffect->SetMatrix("m_WVP", world * CameraController::GetInstance()->GetViewProjection());

		UINT cPasses;
		shadowVolumeEffect->GetEffect()->Begin( &cPasses, 0 );
		for( UINT p = 0; p < cPasses; ++p )
		{
			shadowVolumeEffect->GetEffect()->BeginPass( p);

			for(int j = 0; j < (int)m_materials.size(); j++)
			{
				if (j != m_cutterSubset && j != m_navmeshSubset)
				{
					Vector4D v = Vector4D(m_materials[j].m_diffuse.r,
						m_materials[j].m_diffuse.g,
						m_materials[j].m_diffuse.b,
						m_materials[j].m_diffuse.a);

					shadowVolumeEffect->SetVector4("m_Material", v);
					shadowVolumeEffect->SetTexture("m_Texture", (LPDIRECT3DBASETEXTURE9)TextureCache::GetInstance()->GetTexture(m_textureIndexList[j]));
					shadowVolumeEffect->GetEffect()->CommitChanges();
					m_mesh->DrawSubset(j);
				}
			}
			shadowVolumeEffect->GetEffect()->EndPass();
		}
		shadowVolumeEffect->GetEffect()->End( );
	}
}

/*****************************************************************************************/

void
Model::SetPosition(const Vector3D& position)
{
	m_position = position;
}

/*****************************************************************************************/

const Vector3D&
Model::GetPosition() const
{
	return m_position;
}

/*****************************************************************************************/

void
Model::SetRotation(const Vector3D& rotation)
{
	m_rotation = rotation;
}

/*****************************************************************************************/

const Vector3D&
Model::GetRotation() const 
{
	return m_rotation;
}

/*****************************************************************************************/

void
Model::SetScale(float scale)
{
	m_scale = scale;
}

/*****************************************************************************************/

float
Model::GetScale() const 
{
	return m_scale;
}

/*****************************************************************************************/

Mesh*
Model::GetMesh()
{
	return m_mesh;
}

/*****************************************************************************************/

void 
Model::SetID(const char* ID)
{
	m_ID = ID;
}

/*****************************************************************************************/

const char*
Model::GetID() const
{
	return m_ID.GetPointer();
}

/*****************************************************************************************/

const char*
Model::GetFileName() const
{
	return m_fileName.GetPointer();
}

/*****************************************************************************************/

int
Model::GetCutterSubset() const
{
	return m_cutterSubset;
}

/*****************************************************************************************/

int
Model::GetNavmeshSubset() const
{
	return m_navmeshSubset;
}

/*****************************************************************************************/