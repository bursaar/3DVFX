#ifndef _QUAD_H_
#define _QUAD_H_

class Material;

/**
 * This class controls the generation of a mesh within a plane at a specified subdivision
 */
class Quad
{
public:
	/**
	 * Constructor
	 */
							Quad();
	/**
	 * Constructor with params
	 */
							Quad(
								const Vector3D& position, 
								const Vector3D& rotation, 
								int width, 
								int height, 
								int numSubDivisions, 
								DWORD colour
								);
	/**
	 * Destructor
	 */
							~Quad();
	/**
	 * Creates the plane mesh
	 */
	void					CreateQuad(
								const Vector3D& position, 
								const Vector3D& rotation, 
								int width, 
								int height, 
								int numSubDivisions, 
								DWORD colour
								);
	/**
	 * Renders the mesh
	 */
	void					Render();
	/**
	 * Sets the width of the plane
	 */
	void					SetWidth(
								int width
								);
	/**
	 * Sets the height of the plane
	 */
	void					SetHeight(
								int height
								);
	/**
	 * Sets the number of verts to use
	 */
	void					SetNumSubDivisions(
								int numSubDivisions
								);
	/**
	 * Sets the position of the plane
	 */
	void					SetPosition(
								const Vector3D& position
								);
	/**
	 * Sets the rotation of the plane
	 */
	void					SetRotation(
								const Vector3D& rotation
								);

private:

	Material m_material;

	Vector3D m_position;
	Vector3D m_rotation;

	int m_width;
	int m_height;

	int m_numSubDivisions;
	int m_numberOfVerts;

	DWORD m_colour;

	IDirect3DVertexBuffer9* m_vertexBuffer;

};

#endif //#ifndef _QUAD_H_