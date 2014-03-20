#ifndef _ANIMATIONINSTANCE_H_
#define _ANIMATIONINSTANCE_H_

class SkinnedMesh;

class AnimationInstance
{
public:
	/**
	 * Constructor
	 */
						AnimationInstance();
	/**
	 * Destructor
	 */
						~AnimationInstance();
	/**
	 * Sets up the animation controller to use
	 */
	void				CreateAnimationInstance(
							LPD3DXANIMATIONCONTROLLER pAC
							);
	/**
	 * Updates the playback of the animation
	 */
	void				Update(
							float elapsedTime,
							SkinnedMesh* mesh
							);
	/**
	 * Gets the animation index for the specified animation
	 */
	unsigned int		GetIndex(
							const char* name
							) const;
	/**
	 * Sets the animation to play using the animationIndex.
	 */
	void				SetAnimation(
							unsigned int animationIndex
							);
	/**
	 * Returns the animation currently playing
	 */
	int					GetAnimation() const;
	/**
	 * Retreives the animation name for the currently playing animation
	 */
	const char*			GetAnimationName() const;
	/**
	 * Returns the bone cache for the animation
	 */
	const Matrix*		GetBones() const {return m_boneMatrices;}
	/**
	 * Returns the animation controller object
	 */
	LPD3DXANIMATIONCONTROLLER GetController() const {return m_aniCon;}

	unsigned int		GetTrack() const {return m_track;}
private:
	void				UpdateLocalBones(
							LPD3DXFRAME bone
							);

    void				UpdateFrame(
							const D3DXFRAME* base,
							const Matrix* parentMatrix
							);

	LPD3DXANIMATIONCONTROLLER  m_aniCon;

	unsigned int m_currentAnimationSet;
	unsigned int m_numAnimation;
	unsigned int m_track;
	float m_time;
	float m_speed;

	Matrix* m_boneMatrices;

	friend class SkinnedMesh;
};

#endif //_ANIMATIONINSTANCE_H_
