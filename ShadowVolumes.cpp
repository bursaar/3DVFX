#include "Types.h"
#include "Light.h"
#include "Model.h"
#include "SpotLight.h"
#include "ShadowVolumes.h"
#include "ShadowMesh.h"
#include "RenderManager.h"
#include "EffectManager.h"
#include "Effect.h"
#include "CameraController.h"
#include "Program.h"

bool m_first = false;

ShadowVolumes::ShadowVolumes(void)
{
	Vector3D lightPosition(-3,10,0);
	Vector3D lightDirection;
	Vector3DNormalize(&lightDirection,&lightPosition);
	m_light = new SpotLight("Light1",0,lightPosition,-lightDirection,Vector3D(2.0,0.5f,0.1f),10.0f,(D3DX_PI * 2) / 2,1.0f,1.0f,1,1,1,1);
	m_tempMesh = new Model("Assets\\Models\\Air_Tank.x",Vector3D(5.0f,0,-5),Vector3D(0.0f,2.0f,0.2f),1.0f);
}

ShadowVolumes::~ShadowVolumes(void)
{
}

void
ShadowVolumes::CreateShadowMesh(Mesh *inMesh)
{
	ShadowMesh::CreateShadowMesh(inMesh,&m_ShadowMesh);
}


void
ShadowVolumes::Render()
{
	Vector3D rotation = m_tempMesh->GetRotation();
	rotation.y += 0.05f;

	m_tempMesh->SetRotation(rotation);

	EffectManager::GetInstance()->GetEffect("ShadowVolume")->SetMatrix("m_Proj",CameraController::GetInstance()->GetProjection());

	EffectManager::GetInstance()->GetEffect("ShadowVolume")->SetTechnique("mTech");
	Vector4D Ambi(AMBIENT,AMBIENT,AMBIENT,1.0f);
	EffectManager::GetInstance()->GetEffect("ShadowVolume")->SetVector4("m_Ambient",Ambi);

	EffectManager::GetInstance()->GetEffect("ShadowVolume")->SetFloat( "m_ZClip", 100.0f - 0.1f );
	RenderScene();

	m_D3DDevice->Clear(0, NULL, D3DCLEAR_STENCIL, D3DCOLOR_ARGB(0, 170, 170, 170), 1.0f, 0 );

	Vector4D lightPosition = Vector4D(m_light->GetPosition().x,m_light->GetPosition().y,m_light->GetPosition().z,1.0f);
	Matrix m;
	MatrixIdentity(&m);
	D3DXVec4Transform(&lightPosition,&lightPosition,&m);
	D3DXVec4Transform(&lightPosition,&lightPosition,&CameraController::GetInstance()->GetView());
	Vector4D lights[10];
	ZeroMemory(&lights,sizeof(Vector4D) * 10);
	lights[0] = lightPosition;
	EffectManager::GetInstance()->GetEffect("ShadowVolume")->GetEffect()->SetValue(EffectManager::GetInstance()->GetEffect("ShadowVolume")->GetHandle("m_LightPosition")->m_handle,&lights,sizeof(Vector4D) * 10);
	EffectManager::GetInstance()->GetEffect("ShadowVolume")->SetVector4("m_LightColour",Vector4D(15,15,15,1));

	if(Program::GetInstance()->Allow2SidedShadows())
	{
		EffectManager::GetInstance()->GetEffect("ShadowVolume")->SetTechnique("mTechShadow2");
	}
	else
	{
		EffectManager::GetInstance()->GetEffect("ShadowVolume")->SetTechnique("mTechShadow");
	}

	EffectManager::GetInstance()->GetEffect("ShadowVolume")->SetVector4("m_ShadowColour",Vector4D(0.0f,0.1f,0.0f,0.2f));

	if(m_ShadowMesh)
	{
		UINT cPasses;
		EffectManager::GetInstance()->GetEffect("ShadowVolume")->GetEffect()->Begin( &cPasses, 0 );
		for( UINT i = 0; i < cPasses; ++i )
		{
			EffectManager::GetInstance()->GetEffect("ShadowVolume")->GetEffect()->BeginPass( i );
			EffectManager::GetInstance()->GetEffect("ShadowVolume")->GetEffect()->CommitChanges();
			m_ShadowMesh->DrawSubset( 0 );
			EffectManager::GetInstance()->GetEffect("ShadowVolume")->GetEffect()->EndPass();
		}
		EffectManager::GetInstance()->GetEffect("ShadowVolume")->GetEffect()->End();
	}
	
	EffectManager::GetInstance()->GetEffect("ShadowVolume")->SetTechnique("mTechScene");
	RenderScene();
}

void
ShadowVolumes::RenderScene()
{
	RenderManager::GetInstance()->RenderEnvironment();
	m_tempMesh->RenderWithShadowVolume();
	
}
