#include "Types.h"
#include "ShadowMap.h"
#include "EffectManager.h"
#include "Effect.h"
#include "CameraController.h"
#include "Light.h"
#include "SpotLight.h"
#include "RenderManager.h"
#include "BaseCamera.h"

LPDIRECT3DSURFACE9 oldDepthSurface = NULL;
LPDIRECT3DSURFACE9 oldRenderTarget = NULL;
/************************************************************************/
ShadowMap::ShadowMap(void)
{

	//Create our Light
	Vector3D lightPosition(-65,70,0);
	Vector3D lightDirection;
	Vector3DNormalize(&lightDirection,&lightPosition);
	m_light = new SpotLight("Light",0,lightPosition, -lightDirection,Vector3D(0,0.5f,0.1f),10.0f,(D3DX_PI * 2) / 2,1.0f,1.0f,1,1,1,1);

}
/************************************************************************/
ShadowMap::~ShadowMap(void)
{
	//release the texture and surface
	m_shadowMap->Release();
	m_shadowMapSurface->Release();
	oldDepthSurface = NULL;
	oldRenderTarget = NULL;
}
/************************************************************************/
void 
ShadowMap::Create()
{
	
	HRESULT hr;
	//create our shadow map texture to the size of SHADOWMAP_SIZE, the texture contains one 32-bit channel within the default memory pool,
	//the texture is stored within m_shadowMap
	hr = m_D3DDevice->CreateTexture(SHADOWMAP_SIZE,SHADOWMAP_SIZE,1,D3DUSAGE_RENDERTARGET,D3DFMT_R32F,D3DPOOL_DEFAULT,&m_shadowMap,NULL);
	//error checking
	if(hr != S_OK)
	{
		ErrorMessage("Did not create shadow map texture");
	}
	
	//create the depth Stencil surface to the size of SHADOWMAP_SIZE to a 24bit depth, and no multisampling,
	//the surface is stored in m_shadowMapSurface;
	hr = m_D3DDevice->CreateDepthStencilSurface(SHADOWMAP_SIZE,SHADOWMAP_SIZE,D3DFMT_D24X8,D3DMULTISAMPLE_NONE,0,TRUE,&m_shadowMapSurface,NULL);

	if(hr != S_OK)
	{
		ErrorMessage("Did not create shadow map surface");
	}

	//calculate the max projection of the scene
	float maxProjection = D3DXVec3LengthSq(&m_light->GetPosition()) ;

	//create the shadow projection matrix
	D3DXMatrixPerspectiveFovLH( &m_shadowMatrix, D3DX_PI / 2, 1, 1.5f, maxProjection);
}

/************************************************************************/
//////////////////////////////////////////////////////////////////////////
//RenderScene renders either the scene from the lights view for the
//shadow map or the environment from the camera view.
//////////////////////////////////////////////////////////////////////////
void
ShadowMap::RenderScene(bool renderShadow,const Matrix* view, const Matrix* Proj)
{	
	
	//Set the theta of the light to that of our spot light
	EffectManager::GetInstance()->GetEffect("ShadowMap")->SetFloat("m_CosTheta", cosf((D3DX_PI * 2) / 2));


	//Set our Light Position
	Vector3D lightPos = m_light->GetPosition();
	//Create a Tempory Vector4D Variable 
	Vector4D tempVector4;
	
	//Set the View And Projection matrices within the shader
	EffectManager::GetInstance()->GetEffect("ShadowMap")->SetMatrix("m_View", *view );
	EffectManager::GetInstance()->GetEffect("ShadowMap")->SetMatrix("m_Proj", *Proj);	

	m_view = *view;
	m_proj = *Proj;
	
	//Transform our light vector by our view matrix, place the result in tempVector4
	D3DXVec3Transform( &tempVector4, &lightPos, view);

	//Set our light position within our shader
	EffectManager::GetInstance()->GetEffect("ShadowMap")->SetVector4("m_LightPosition",tempVector4);
	
	//Set our TempVector4 to our light direction
	*(D3DXVECTOR3*)&tempVector4  = m_light->GetDirection();
	//set our tempVector4.w to 0 as this will clear any tesserlation issues
	tempVector4.w =0;
	//transform the value within tempVector4 with our view
	D3DXVec4Transform( &tempVector4, &tempVector4, view);
	//Normalize it
	Vector3DNormalize((D3DXVECTOR3*)&tempVector4,(D3DXVECTOR3*)&tempVector4);
	//And place it within our shader
	EffectManager::GetInstance()->GetEffect("ShadowMap")->SetVector4("m_LightDirection",tempVector4);


	//If we are rendering the Shadow, set our shaders technique to that
	//else we set it to our scene render technique
	if(renderShadow)
	{
		m_D3DDevice->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(255,0,255),1.0f,0);

		EffectManager::GetInstance()->GetEffect("ShadowMap")->SetTechnique("mTech1");	
	}

	if(!renderShadow)
	{
		EffectManager::GetInstance()->GetEffect("ShadowMap")->SetTechnique("mTech");
	}
}
/************************************************************************/

void
ShadowMap::SetUpDepthRender()
{

	//Create a temp Render Target
	//Get the current RenderTarget and place it within our temp Render Target
	m_D3DDevice->GetRenderTarget( 0, &oldRenderTarget );

	//Create a temp ShadowSurface
	LPDIRECT3DSURFACE9 tempShadowSurface;

	//The Texture takes a reference of the surface level of the tempShadowSurface
	if( SUCCEEDED( m_shadowMap->GetSurfaceLevel( 0, &tempShadowSurface ) ) )
	{
		//it is set to target and released
		m_D3DDevice->SetRenderTarget( 0, tempShadowSurface );
		tempShadowSurface->Release() ;
	}

	//Store the current depth surface to the temp variable and set the stencil surface
	//to our member surface
	if( SUCCEEDED( m_D3DDevice->GetDepthStencilSurface( &oldDepthSurface ) ) )
	m_D3DDevice->SetDepthStencilSurface( m_shadowMapSurface );

	RenderScene( true, &m_light->GetView() ,&m_shadowMatrix);
}
/************************************************************************/

void
ShadowMap::SetUpSceneRender()
{
	//Set the now generated texture to our shader
	EffectManager::GetInstance()->GetEffect("ShadowMap")->GetEffect()->SetTexture(EffectManager::GetInstance()->GetEffect("ShadowMap")->GetHandle("m_ShadowMap")->m_handle,m_shadowMap);

	//if there is an old surface, set it back
	if( oldDepthSurface )
	{
		m_D3DDevice->SetDepthStencilSurface( oldDepthSurface );
		oldDepthSurface->Release();
	}

	//set the render target back to how it was before this process
	m_D3DDevice->SetRenderTarget( 0, oldRenderTarget );
	oldRenderTarget->Release();

	//generate a view to light projection matrix to generate how the shadow will appear
	Matrix viewToLightProj ;
	//set our matrix to our camera view
	viewToLightProj = CameraController::GetInstance()->GetView() ;
	//Inverse it
	MatrixInverse(&viewToLightProj,NULL,&viewToLightProj);
	//Multiply it with out light view matrix
	MatrixMultiply(&viewToLightProj,&viewToLightProj,&m_light->GetView());
	//then our shadow matrix
	MatrixMultiply(&viewToLightProj,&viewToLightProj,&m_shadowMatrix);
	//apply to effect
	EffectManager::GetInstance()->GetEffect("ShadowMap")->SetMatrix("m_VTLP",viewToLightProj);

	//render scene, to render the environment this time
	RenderScene(false, &CameraController::GetInstance()->GetView(),&CameraController::GetInstance()->GetProjection());
}

/************************************************************************/

void
ShadowMap::Render()
{
	//Create a temp Render Target
	LPDIRECT3DSURFACE9 oldRenderTarget = NULL;
	//Get the current RenderTarget and place it within our temp Render Target
	 m_D3DDevice->GetRenderTarget( 0, &oldRenderTarget );
	
	 //Create a temp ShadowSurface
	LPDIRECT3DSURFACE9 tempShadowSurface;
	
	//The Texture takes a reference of the surface level of the tempShadowSurface
	if( SUCCEEDED( m_shadowMap->GetSurfaceLevel( 0, &tempShadowSurface ) ) )
	{
		//it is set to target and released
		m_D3DDevice->SetRenderTarget( 0, tempShadowSurface );
		 tempShadowSurface->Release() ;
	}

	//We create a temp Depth surface
	LPDIRECT3DSURFACE9 oldDepthSurface = NULL;
	
	//Store the current depth surface to the temp variable and set the stencil surface
	//to our member surface
	if( SUCCEEDED( m_D3DDevice->GetDepthStencilSurface( &oldDepthSurface ) ) )
		m_D3DDevice->SetDepthStencilSurface( m_shadowMapSurface );

	//call render scene rendering with shadow
	RenderScene( true, &m_light->GetView() ,&m_shadowMatrix);

	//Set the now generated texture to our shader
	EffectManager::GetInstance()->GetEffect("ShadowMap")->GetEffect()->SetTexture(EffectManager::GetInstance()->GetEffect("ShadowMap")->GetHandle("m_ShadowMap")->m_handle,m_shadowMap);

	//if there is an old surface, set it back
	if( oldDepthSurface )
	{
		m_D3DDevice->SetDepthStencilSurface( oldDepthSurface );
		oldDepthSurface->Release();
	}

	//set the render target back to how it was before this process
	m_D3DDevice->SetRenderTarget( 0, oldRenderTarget );
	oldRenderTarget->Release();

	//generate a view to light projection matrix to generate how the shadow will appear
	Matrix viewToLightProj ;
	//set our matrix to our camera view
	viewToLightProj = CameraController::GetInstance()->GetView() ;
	//Inverse it
	MatrixInverse(&viewToLightProj,NULL,&viewToLightProj);
	//Multiply it with out light view matrix
	MatrixMultiply(&viewToLightProj,&viewToLightProj,&m_light->GetView());
	//then our shadow matrix
	MatrixMultiply(&viewToLightProj,&viewToLightProj,&m_shadowMatrix);
	//apply to effect
	EffectManager::GetInstance()->GetEffect("ShadowMap")->SetMatrix("m_VTLP",viewToLightProj);
	
	//render scene, to render the environment this time
	RenderScene(false, &CameraController::GetInstance()->GetView(),&CameraController::GetInstance()->GetProjection());
	
	//restore our texture back to NULL in our shader.
	EffectManager::GetInstance()->GetEffect("ShadowMap")->GetEffect()->SetTexture(EffectManager::GetInstance()->GetEffect("ShadowMap")->GetHandle("m_ShadowMap")->m_handle,NULL);

}
/************************************************************************/

Matrix*
ShadowMap::GetCurrentView()
{
	return &m_view;
}

/************************************************************************/
Matrix*
ShadowMap::GetCurrentProj()
{
	return &m_proj;
}
/************************************************************************/
void 
ShadowMap::SetLightPosition(Vector3D& lightPos)
{
	m_light->SetPosition(lightPos);
	Vector3D lightDirection;
	Vector3DNormalize(&lightDirection,&lightPos);
	m_light->SetDirection(-lightDirection);

}

/************************************************************************/
Vector3D 
ShadowMap::GetLightPosition()
{
	return m_light->GetPosition();
}