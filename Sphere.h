#ifndef _SPHERE_H_
#define _SPHERE_H_

class Material;

#ifndef _VERTEX_H_
#include "Vertex.h"
#endif
#include "Types.h"

class Sphere
{
public:
	/**
	 * Constructor
	 */
							Sphere();
	/**
	 * Constructor from AABB
	 */
							Sphere(
								const AABB& aabb
								);
	/**
	 * Constructor from components
	 */
							Sphere(
								const Vector3D& position,
								float radius
								);
	/**
	 * Constructor from components
	 */
							Sphere(
								const Vector3D& position, 
								float radius, 
								DWORD colour
								);
	/**
	 * Copy Constructor
	 */
							Sphere(
								const Sphere& other
								);
	/**
	 * Destructor
	 */
							~Sphere();
	/**
	 * Sets the position of the sphere
	 */
	void					SetPosition(
								const Vector3D& position
								){m_position = position;}
	/**
	 * Returns the position of the sphere
	 */
	const Vector3D&			GetPosition()const{return m_position;}
	/**
	 * Sets the radius of the sphere
	 */
	void					SetRadius(
								float radius
								);
	/**
	 * Returns the radius of the sphere
	 */
	float					GetRadius()const{return m_radius;}
	/**
	 * Returns if the sphere is overlapping with anohter sphere
	 */
	bool					CollidingWithSphere(
								const Sphere& otherSphere
								);
	/**
	 * Renders the sphere
	 */
	void					Render(bool wireframe = true);

private:
	/**
	 * Creates the shared VB for the renderering of spheres
	 */
	static void				CreateWireFrameSphere();

	Vector3D m_position;
	float	 m_radius;
	
	DWORD	m_colour;

	static IDirect3DVertexBuffer9*		ms_sphereVertexBuffer;
	static int							ms_numSphereVerts;
	static int							ms_numSpheres;
};

#endif //#ifndef _SPHERE_H_
