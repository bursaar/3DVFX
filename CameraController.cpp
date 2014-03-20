#include "Types.h"
#include "BaseCamera.h"
#include "StaticCamera.h"
#include "FreeCamera.h"
#include "ThirdPersonCamera.h"
#include "CameraController.h"
#include "Frustum.h"

/************************************************************************/

DefineSingleton(CameraController);

/************************************************************************/

CameraController::CameraController() :
	m_cameraCount(0)
{
	m_cameras[0] = new StaticCamera;
	m_currentCamera = m_cameras[0];
	m_currentCamera->SetupCamera(Vector3D(0,0,-10),Vector3D(0,0,1),Vector3D(0,1,0));
	m_cameraCount ++;

	MatrixIdentity(&m_world);
	MatrixIdentity(&m_view);
	MatrixIdentity(&m_projection);
}

/************************************************************************/

CameraController::~CameraController()
{
	for (int index = 0; index < m_cameraCount; index ++)
	{
		delete m_cameras[index];
	}

	m_currentCamera = 0;
}

/************************************************************************/

void
CameraController::AddCamera(BaseCamera* newCamera)
{
	assert(m_cameraCount < c_MaxCameraCount);
	m_cameras[m_cameraCount] = newCamera;
	m_cameraCount ++;
	m_currentCamera = m_cameras[m_cameraCount - 1];
}

/************************************************************************/

void
CameraController::RemoveCamera()
{
	if(m_cameraCount > 1)
	{
		delete m_cameras[m_cameraCount - 1];
		m_cameraCount --;
		m_currentCamera = m_cameras[m_cameraCount - 1];
	}
	else
	{
		ErrorMessage("You can't remove the only camera");
	}
}

/************************************************************************/

void
CameraController::ComputeCamera()
{
	MatrixIdentity(&m_world);
	CreateViewMatrix();
	CreateProjectionMatrix();
	m_viewFrustum.Calculate(m_view,m_projection);
	m_D3DDevice->SetTransform(D3DTS_WORLD, &m_world);
	m_D3DDevice->SetTransform(D3DTS_VIEW, &m_view);
	m_D3DDevice->SetTransform(D3DTS_PROJECTION, &m_projection);
}

/************************************************************************/

void
CameraController::Update(float elapsedTime)
{
	m_currentCamera->ProcessKeys(elapsedTime);
}

/************************************************************************/

void
CameraController::CreateViewMatrix()
{
	m_currentCamera->CreateViewMatrix(m_view);
}

/************************************************************************/

void
CameraController::CreateProjectionMatrix()
{
	m_currentCamera->CreateProjectionMatrix(m_projection);
}

/************************************************************************/

BaseCamera*
CameraController::GetCurrentCamera() const
{
	return m_currentCamera;
}

/************************************************************************/

const Matrix&
CameraController::GetWorld() const
{
	return m_world;
}

/************************************************************************/

void
CameraController::SetWorld(const Matrix &worldMatrix)
{
	m_world = worldMatrix;
	m_D3DDevice->SetTransform(D3DTS_WORLD,&m_world);
}

/************************************************************************/

void
CameraController::ResetWorld()
{
	MatrixIdentity(&m_world);
	m_D3DDevice->SetTransform(D3DTS_WORLD,&m_world);
}

/************************************************************************/

const Matrix&
CameraController::GetView() const
{
	return m_view;
}

/************************************************************************/

const Matrix&
CameraController::GetProjection() const
{
	return m_projection;
}

/************************************************************************/

const Matrix&
CameraController::GetViewProjection() const
{
	static Matrix viewProjection;
	viewProjection = m_view * m_projection;
	return viewProjection;
}

/*************************************************************************/

const Vector3D&
CameraController::GetCurrentCameraPosition()const
{
	return m_currentCamera->GetPosition();
}

/*************************************************************************/

void					
CameraController::SetProjection(const Matrix& newMat)
{
	m_projection = newMat;
	m_D3DDevice->SetTransform(D3DTS_PROJECTION, &m_projection);
}

/*************************************************************************/

void					
CameraController::SetView(const Matrix& newMat)
{
	m_view = newMat;
	m_D3DDevice->SetTransform(D3DTS_VIEW, &m_view);
}

/*************************************************************************/

const Frustum&			
CameraController::GetFrustum() const
{
	return m_viewFrustum;
}

/*************************************************************************/
