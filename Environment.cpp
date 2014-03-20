#include "Types.h"
#include "Model.h"
#include "Environment.h"
#include "RenderManager.h"
#include "CameraController.h"
#include "BaseCamera.h"

Environment::Environment(void)
{
	m_flags = AmibentEnviroment;
}

Environment::~Environment(void)
{
	delete m_model;
	RenderManager::GetInstance()->RemoveEvent(this);
}

void
Environment::LoadEnvironment(const char* ID,const char* fileName, Vector3D pos, Vector3D rot, float scale)
{
	m_ID = ID;
	m_model = new Model(fileName,pos,rot,scale);
	RenderManager::GetInstance()->AddEvent(this, NULL);
}

void
Environment::SetUVMulitply(int UVM)
{
	m_UVMultiply = UVM;
}

void
Environment::Render()
{
	m_model->RenderWithNormalMap();
}
