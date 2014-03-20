#include "Types.h"
#include "PolygonData.h"
#include "Line.h"

/************************************************************************/

PolygonData::PolygonData()
{
	m_verts[0] = Vector3D(0,0,0);
	m_verts[1] = Vector3D(0,0,0);
	m_verts[2] = Vector3D(0,0,0);
}

/************************************************************************/

PolygonData::~PolygonData()
{
}

/************************************************************************/

void 
PolygonData::SetVerts(const Vector3D& vert0, const Vector3D& vert1, const Vector3D& vert2)
{
	m_verts[0] = vert0;
	m_verts[1] = vert1;
	m_verts[2] = vert2;

	Vector3DCrossProduct(&m_normal, &(vert1 - vert0), &(vert2 - vert0));
	Vector3DNormalize(&m_normal, &m_normal);
}

/************************************************************************/

const Vector3D&
PolygonData::GetVert(int index) const
{
	return m_verts[index];
}

/************************************************************************/

const Vector3D&
PolygonData::GetNormal() const
{
	return m_normal;
}

/************************************************************************/

void 
PolygonData::RenderDebug()
{
	Line* ab;
	Line* bc;
	Line* ca;

	ab = new Line(m_verts[0],m_verts[1],0x00FF0000,0x00FF0000);
	bc = new Line(m_verts[1],m_verts[2],0x00FF0000,0x00FF0000);
	ca = new Line(m_verts[2],m_verts[0],0x00FF0000,0x00FF0000);

	ab->Render();
	bc->Render();
	ca->Render();

	delete ab;
	delete bc;
	delete ca;
}

/************************************************************************/
