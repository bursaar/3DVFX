#ifndef _MODEL_H_
#define _MODEL_H_
#include "Material.h"
#include <vector>

class Model
{
public:
	/**
	 * Constructor
	 */
						Model();
	/**
	 * Constructor with filename
	 */
						Model(
							const char* fileName
							);
	/**
	 * Constructor with filename and transform
	 */
						Model(
							const char* fileName,
							const Vector3D& position, 
							const Vector3D& rotation, 
							float scale
							);
	/**
	 * Destructor
	 */
						~Model();
	/**
	 * Loads the specified model mesh
	 */
	bool				LoadModel(
							const char* fileName
							);
	/**
	 * Sets the position
	 */
	void				SetPosition(
							const Vector3D& position
							);
	/**
	 * Gets the position
	 */
	const Vector3D&		GetPosition() const;
	/**
	 * Sets the rotation
	 */
	void				SetRotation(
							const Vector3D& rotation
							);
	/**
	 * Gets the rotation
	 */
	const Vector3D&		GetRotation() const;
	/**
	 * Sets the scale to render the model at
	 */
	void				SetScale(
							float scale
							);
	/**
	 * Gets the scale
	 */
	float				GetScale() const;
	/**
	 * Renders the model using the fogging technique
	 */
	void				Render();
	/**
	 * Renders the model using the normalmap technique
	 */
	void				RenderWithNormalMap();
	/**
	 * Renders the model using the shadowmap technique
	 */
	void				RenderWithShadow();
	/**
	 * Renders the model using the shadow volume technique
	 */
	void				RenderWithShadowVolume();
	/**
	 * Returns the mesh of the model
	 */
	Mesh*				GetMesh();
	/**
	 * Sets the id of the model
	 */
	void				SetID(
							const char* ID
							);
	/**
	 * Returns the id of the model
	 */
	const char*			GetID() const;
	/**
	 * Returns the filename of the model
	 */
	const char*			GetFileName() const;
	/**
	 * Returns the nav mesh cutter subset
	 */
	int					GetCutterSubset() const;
	/**
	 * Returns the navmesh subset
	 */
	int					GetNavmeshSubset() const;

private:
	MyString m_ID;
	MyString m_fileName;

	Vector3D m_position;

	Vector3D m_rotation;

	float m_scale;

	Mesh* m_mesh;

	int m_cutterSubset;
	int m_navmeshSubset;
	
	std::vector<Material> m_materials;

	std::vector<int> m_textureIndexList;
	std::vector<int> m_normalMapsIndexList;

};

#endif //_MODEL_H_
