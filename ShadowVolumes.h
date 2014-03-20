#ifndef _SHADOWVOLUME_H_
#define _SHADOWVOLUME_H_

#define AMBIENT 0.10f

class SpotLight;
class Model;

class ShadowVolumes
{
public:
	ShadowVolumes(void);
	~ShadowVolumes(void);
	void CreateShadowMesh(Mesh* inMesh);

	Mesh* GetShadowMesh();

	void RenderMesh();

	void Render();

	void RenderScene();

private:

	Mesh* m_ShadowMesh;
	SpotLight* m_light;
	Model* m_tempMesh;
};

#endif _SHADOWVOLUME_H_