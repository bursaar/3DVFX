#include "Types.h"
#include "CameraController.h"
#include "Material.h"
#include "Sphere.h"

/*****************************************************************************************/

IDirect3DVertexBuffer9*	Sphere::ms_sphereVertexBuffer = 0;
int						Sphere::ms_numSphereVerts = 0;
int						Sphere::ms_numSpheres = 0;

/*****************************************************************************************/

Sphere::Sphere() : 
	m_position (Vector3D(0,0,0)),
	m_radius(1.0f),
	m_colour(0xffffffff)
{
	ms_numSpheres ++;
}

/*****************************************************************************************/

Sphere::Sphere(const AABB &aabb) : 
	m_colour(0xffffffff)
{
	m_position = (aabb.GetMin() + aabb.GetMax()) * 0.5f;
	m_radius   = Vector3DLength(&(aabb.GetMax() - m_position));
	ms_numSpheres ++;
}

/*****************************************************************************************/

Sphere::Sphere(const Vector3D& position,float radius) : 
	m_position(position),
	m_radius(radius),
	m_colour(0xffffffff)
{
	ms_numSpheres ++;
}

/*****************************************************************************************/

Sphere::Sphere(const Vector3D& position, float radius, DWORD colour) :	
	m_position(position),
	m_radius(radius),
	m_colour(colour)
{
	ms_numSpheres ++;
}

/*****************************************************************************************/

Sphere::Sphere(const Sphere& other) :
	m_position(other.m_position),
	m_radius(other.m_radius),
	m_colour(other.m_colour)
{
	ms_numSpheres ++;
}

/*****************************************************************************************/

Sphere::~Sphere()
{
	ms_numSpheres --;
	if (ms_sphereVertexBuffer && !ms_numSpheres)
	{
		ms_sphereVertexBuffer->Release();
		ms_sphereVertexBuffer = 0;
		ms_numSphereVerts = 0;
	}
}

/*****************************************************************************************/

bool 
Sphere::CollidingWithSphere(const Sphere& sphere)
{
	Vector3D vecTo =  sphere.GetPosition() - m_position;
	float distance = Vector3DLengthSq(&vecTo);
	float radiusSum = sphere.GetRadius() + m_radius;
	if(distance >  radiusSum  * radiusSum)
	{
		return false;
	}
	return true;
}

/*****************************************************************************************/

void 
Sphere::Render(bool wireframe)
{
	if (!ms_sphereVertexBuffer)
	{
		CreateWireFrameSphere();
	}

	Matrix world;
	D3DXMatrixIdentity(&world);
	D3DXMatrixTranslation(&world, m_position.x, m_position.y, m_position.z);

	/// Scale the transform to the size of the sphere
	world._11 = m_radius;
	world._22 = m_radius;
	world._33 = m_radius;

	m_D3DDevice->SetVertexShader(NULL);
	m_D3DDevice->SetPixelShader(NULL);
	CameraController::GetInstance()->SetWorld(world);
	m_D3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_D3DDevice->SetStreamSource(0, ms_sphereVertexBuffer, 0 , sizeof(VertexColour));
	m_D3DDevice->SetVertexDeclaration(VertexColour::Decl);
	m_D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_D3DDevice->DrawPrimitive( D3DPT_LINELIST, 0, ms_numSphereVerts/2 );
	m_D3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

/*****************************************************************************************/

void
Sphere::SetRadius(float radius)
{
	m_radius = radius;
}

/*****************************************************************************************/

void 
Sphere::CreateWireFrameSphere()
{
	if(!m_D3DDevice)
	{
		return;
	}
	
	const float uStep = ( 2 * D3DX_PI ) / 10;
	const float vStep = D3DX_PI / 10;

	ms_numSphereVerts = 10 * 10 * 4;

	m_D3DDevice->CreateVertexBuffer(ms_numSphereVerts*sizeof(VertexColour), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &ms_sphereVertexBuffer, 0);

	VertexColour* vb = 0;
	ms_sphereVertexBuffer->Lock(0, 0, (void**)&vb, 0);

	int count = 0;
	for( float u=0.0f; u<2*D3DX_PI; u+=uStep )
	{
		for( float v=-D3DX_PI/2.0f; v<D3DX_PI/2.0f; v+=vStep )
		{
			float cu  = cos(u); 
			float cv  = cos(v);
			float su  = sin(u);
			float sv  = sin(v);
			float cus = cos(u+uStep);
			float cvs = cos(v+vStep);
			float sus = sin(u+uStep);
			float svs = sin(v+vStep);

			vb[count+0] = VertexColour(Vector3D(cv*cu,  cv*su,  sv), 0xffffffff);
			vb[count+1] = VertexColour(Vector3D(cv*cus, cv*sus, sv), 0xffffffff);
			vb[count+2] = VertexColour(Vector3D(cv*cu,  cv*su,  sv), 0xffffffff);
			vb[count+3] = VertexColour(Vector3D(cvs*cu, cvs*su, svs), 0xffffffff);

			count += 4;
		}
	}
	
	ms_sphereVertexBuffer->Unlock();
}

/*****************************************************************************************/