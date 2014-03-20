#ifndef _MODELMANAGER_H_
#define _MODELMANAGER_H_

#ifndef _SKINNEDMESH_H_
#include "SkinnedMesh.h"
#endif //#ifndef _SKINNEDMESH_H_

#ifndef _MODEL_H_
#include "Model.h"
#endif //#ifndef _MODEL_H_

/**
 * Structure for storing a skinned model entry
 */
struct ObjectModel
{
	~ObjectModel()
	{
		delete m_mesh;
	}
	MyString m_ID;
	MyString m_fileName;
	SkinnedMesh* m_mesh;
	float m_scale;
};

/**
 * Structure for storing a static model entry
 */
struct StaticModel
{
	~StaticModel()
	{
		delete m_mesh;
	}
	MyString m_ID;
	MyString m_fileName;
	Model* m_mesh;
	float m_scale;
};

class ModelManager : public Singleton<ModelManager>
{
public:
	/**
	 * Constructor
	 */
									ModelManager();
	/**
	 * Destructor
	 */
									~ModelManager();
	/**
	 * Loads an new skinned model
	 */
	void							CreateModel(
										const char* ID,
										const char* fileName, 
										float scale
										);
	/**
	 * Loads an new static model
	 */
	void							CreateMesh(
										const char* ID,
										const char* fileName, 
										float scale
										);
	/**
	 * Gets a handle to the skinned model mesh set for the specified id
	 */
	SkinnedMesh*					GetSkinnedMeshPointer(
										const char* ID ///< Id of model to return data for
										);
	/**
	 * Gets a handle to the static model mesh set for the specified id
	 */
	Model*							GetStaticMeshPointer(
										const char* ID ///< Id of model to return data for
										);
	/**
	 * Returns the skinned model scale for the specified id
	 */
	float							GetSkinnedMeshScale(
										const char* ID ///< Id of model to return data for
										);
	/**
	 * Returns the the number of skinned models currently stored
	 */
	int								GetObjectModelCount();
	/**
	 * Returns the the number of static models currently stored
	 */
	int								GetStaticModelCount();
	/**
	 * Returns the the skinned model at the specified index
	 */
	ObjectModel*					GetObjectModel(
										int index ///< index of model
										);
	/**
	 * Returns the the skinned model which utilises the skinned mesh class passes in
	 */
	ObjectModel*					GetObjectModel(
										SkinnedMesh* mesh
										);
	/**
	 * Returns the the skinned model with the specified id.
	 */
	ObjectModel*					GetObjectModel(
										const char* id ///< Id of model
										);
	/**
	 * Returns the the static model at the specified index
	 */
	StaticModel*					GetStaticModel(
										int index ///< index of model
										);
	/**
	 * Returns the the static model which uses the specified static model
	 */
	StaticModel*					GetStaticModel(
										Model* model
										);
	/**
	 * Returns the the static model with the specified id.
	 */
	StaticModel*					GetStaticModel(
										const char* id ///< Id of model
										);
private:
	static const int c_MaxMeshCount = 256;
	static const int c_MaxStaticMeshCount = 256;
	
	ObjectModel* m_meshes[c_MaxMeshCount];
	int m_numMeshes;

	StaticModel* m_staticMeshes[c_MaxStaticMeshCount];
	int m_numStaticMeshes;
};

#endif //_MODELMANAGER_H_
