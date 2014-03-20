#ifndef _CYCLINDER_H_
#define _CYCLINDER_H_

class Material;

//////////////////////////////////////////////////////////////////////////
//The Cylinder class
//
//This uses a D3D command called D3DXCreateCylinder to create a predefined mesh,
//with this command, you can define the radius of the top and bottom faces, the length of the cylinder
//and the number of polygons, symbolized by the slices and stacks of the Cylinder.
//
//As the radius of the top and bottom faces can be defines, this class can be used to create
//cones shaped objects.
//////////////////////////////////////////////////////////////////////////

class Cylinder
{
public:
						Cylinder(
							const Vector3D& position,
							const Vector3D& direction,
							float topRadius, 
							float bottomRadius, 
							float length,
							UINT slices,
							UINT stacks
							);

						~Cylinder();
	/**
	 * Sets weather to render the cylinder in wire frame or not
	 */
	void				SetWireFrame(
							bool wireFrame
							);
	/**
	 * Sets the material to use to render the cylinder
	 */
	void				SetMaterial(
							Material& material
							);
	/**
	 * Gets the material currently in use by the cylinder
	 */
	Material&			GetMaterial();
	/**
	 * Updates the position of the cylinder
	 */
	void				SetPosition(
							const Vector3D& position
							);
	/**
	 * Gets the position of the cylinder
	 */
	const Vector3D&		GetPosition() const; 
	/**
	 * Sets the direction of the cylinder
	 */
	void				SetDirection(
							const Vector3D& direction 
							);
	/**
	 * Gets the direction of the cylinder
	 */
	const Vector3D&		GetDirection() const;
	/**
	 * Renders the cylinder
	 */
	void				Render();
private:
	void				CreateCylinder(
							float topRadius, 
							float bottomRadius, 
							float length,
							UINT slices,
							UINT stacks
							);

	//The Cylinder information is stored within a mesh,
	Mesh* m_cyclinderMesh;
	Vector3D m_position;
	Vector3D m_direction;

	bool m_wireFrame;
	Material m_material;
};

#endif
