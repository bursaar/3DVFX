
#include "RenderableObject.h"
class SphereClass :
	public RenderableObject
{
public:
	SphereClass();
	~SphereClass();
private:
	LPD3DXMESH mMesh;
	DWORD mColour;
public:
	void Initialise(RenderClass * pRenderClass) override;
	void Update(double deltaTime, double totalTime) override;
};
