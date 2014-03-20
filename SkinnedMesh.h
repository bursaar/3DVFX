#ifndef _SKINNEDMESH_H_
#define _SKINNEDMESH_H_

class AnimationInstance;
class Effect;
struct EffectHandle;

#ifndef _MESHHIERARCHY_H_
#include "MeshHierarchy.h"
#endif //#ifndef _MESHHIERARCHY_H_

class SkinnedMesh
{
public:
	/**
	 * Constructor
	 */
						SkinnedMesh();
	/**
	 * Destructor
	 */
						~SkinnedMesh();
	/**
	 * Loads the skinned model
	 */
	bool				Load(
							const char* fileName
							);
	/**
	 * Renders the skinned model, using the animation info passed in
	 */
	void				Render(
							AnimationInstance* anim ///< Animation instance to apply to the character when rendering
							);
	/**
	 * Renders the skinned model, using the shadow map depth render technique
	 */
	void				RenderShadow(
							AnimationInstance* anim
							);
	/**
	 * Creates an new animation instance for this model
	 */
	void				CloneAniCon(
							AnimationInstance** instance ///< Pointer to the pointer value to be filled with the new animation instance
							);
	/**
	 * Returns the root frame
	 */
	LPD3DXFRAME			GetFrameRoot() const;
	/**
	 * Returns the number of meshes
	 */
	int					GetNumberOfMeshes() const;
	/**
	 * Returns the mesh at the specified index
	 */
	MeshContainer*		GetMeshContainer(
							int index
							);
	/**
	 * Returns the shadow mesh
	 */
	Mesh*				GetShadowMesh() const;
	/**
	 * Returns the number of bones
	 */
	int					GetNumberBones() const;
	/**
	 * Finds the mesh for the shadow and generates the shadow mesh 
	 */
	void				GetMeshForShadow(LPD3DXFRAME frame);
	/**
	 * Gets the current matrix for a bone
	 */
	const Matrix&		GetJointMatrix(
							const char* name, 
							AnimationInstance* anim
							) const;
private:

	//MyLinkedList<AnimationInstance*> m_instances;
	//int m_currentInstance;

	LPD3DXFRAME m_frameRoot;
	LPD3DXANIMATIONCONTROLLER m_aniCon;

	static const int c_MaxNumMeshes = 16;
	MeshContainer* m_mesh[c_MaxNumMeshes];
	int m_numMeshes;

	Mesh* m_ShadowVolume;

	Matrix * m_boneMatrices;
	int m_maxBones;

	unsigned int m_currentAnimationSet;
	unsigned int m_numAnimation;
	unsigned int m_track;
	float m_time;
	float m_speed;

	DWORD          m_maxVertInfluences;
	Effect*		   m_currentEffect;
	EffectHandle*  m_boneMatrixArrayHandle;

	MyString m_filename;

	void UpdateFrame(const D3DXFRAME* base,const Matrix* parentMatrix);
	void DrawFrame(LPD3DXFRAME frame, AnimationInstance* anim) const;
	void DrawContainer(LPD3DXMESHCONTAINER containerBase, LPD3DXFRAME frameBase,int counter, AnimationInstance* anim) const;
	void SetUpBone(Frame * baseFrame, Matrix* parentMatrix);

	void SetUpForNormalMapping();

	MyString m_boneNames[35];

	friend class AnimationInstance;
};

#endif //_SKINNEDMESH_H_
