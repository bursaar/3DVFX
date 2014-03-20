#ifndef _SHADOWMAP_H_
#define _SHADOWMAP_H_

#define SHADOWMAP_SIZE 2048

class SpotLight;

//////////////////////////////////////////////////////////////////////////
//ShadowMap Class
//
//This Class along with the shadow map shader, creates a shadow map
//from a light source which is then used to display a shadow across the
//environment
//////////////////////////////////////////////////////////////////////////

class ShadowMap
{
public:
	ShadowMap(void);
	~ShadowMap(void);
	
	void Create();

	void Render();

	void SetUpDepthRender();

	void SetUpSceneRender();

	Matrix* GetCurrentView();
	Matrix* GetCurrentProj();

	void SetLightPosition(Vector3D& lightPos);

	Vector3D GetLightPosition();

private:	
	
	void RenderScene(bool renderShadow,const Matrix* view, const Matrix* Proj);

	//Our Shadow Texture and surface
	LPDIRECT3DTEXTURE9 m_shadowMap;
	LPDIRECT3DSURFACE9 m_shadowMapSurface;

	//the Shadow Projection matrix
	Matrix m_shadowMatrix;
	//the SpotLight
	SpotLight* m_light;

	Matrix m_view;
	Matrix m_proj;

};

#endif //_SHADOWMAP_H_
