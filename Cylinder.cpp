#include "Types.h"
#include "CameraController.h"
#include "Material.h"
#include "Cylinder.h"

/************************************************************************/

Cylinder::Cylinder(const Vector3D& position, const Vector3D& direction, float topRadius, float bottomRadius, float length, UINT slices, UINT stacks)
{
	CreateCylinder(topRadius,bottomRadius,length,slices,stacks);
	m_position = position;
	m_direction = direction;
	m_wireFrame = false;
}

/************************************************************************/

Cylinder::~Cylinder()
{
	m_cyclinderMesh->Release();
}

/************************************************************************/

void
Cylinder::CreateCylinder(float topRadius, float bottomRadius, float length, UINT slices, UINT stacks)
{
	D3DXCreateCylinder(m_D3DDevice,topRadius,bottomRadius,length,slices,stacks,&m_cyclinderMesh,NULL);
	m_material = Material(0xffff0000,(DWORD)0,(DWORD)0,0.0f);
}

/************************************************************************/

void
Cylinder::SetMaterial(Material& material)
{
	m_material = material;
}

/************************************************************************/

Material&
Cylinder::GetMaterial()
{
	return m_material;
}

/************************************************************************/

void
Cylinder::SetPosition(const Vector3D& position)
{
	m_position = position;
}
/************************************************************************/

const Vector3D&
Cylinder::GetPosition() const
{
	return m_position;
}
/************************************************************************/

void
Cylinder::SetDirection(const Vector3D& direction)
{
	m_direction = direction;
}

/************************************************************************/

const Vector3D&
Cylinder::GetDirection() const
{
	return m_direction;
}

/************************************************************************/

void
Cylinder::SetWireFrame(bool wireFrame)
{
	m_wireFrame = wireFrame;
}

/************************************************************************/

void
Cylinder::Render()
{
	Matrix worldInv;
	Matrix world;
	
	Vector3D target = Vector3D(m_position.x + m_direction.x,
		m_position.y + m_direction.y,
		m_position.z + m_direction.z );

	Vector3D up = Vector3D(0,1,0);

	MatrixIdentity(&world);
	
	MatrixLookAtLH( &worldInv, &m_position, &target, &up);
	MatrixInverse( &world, NULL, &worldInv);

	CameraController::GetInstance()->SetWorld(world);

	if(m_wireFrame)
	{
		m_D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}

	else
	{
		m_D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
	m_material.m_emissive.r = m_material.m_ambient.r;
	m_material.m_emissive.g = m_material.m_ambient.g;
	m_material.m_emissive.b = m_material.m_ambient.b;
	m_material.m_emissive.a = m_material.m_ambient.a;
	m_D3DDevice->SetMaterial(m_material);
	
	m_cyclinderMesh->DrawSubset(0);

	CameraController::GetInstance()->ResetWorld();
}

/************************************************************************/
