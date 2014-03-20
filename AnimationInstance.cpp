#include "Types.h"
#include "SkinnedMesh.h"
#include "AnimationInstance.h"
#include "EffectManager.h"
#include "Effect.h"

/************************************************************************/

const float TRANSITIONTIME = 0.002f;

/************************************************************************/

AnimationInstance::AnimationInstance() : 
	m_aniCon(0),
	m_time(0.0f),
	m_track(0),
	m_currentAnimationSet(0),
	m_speed(1.0f)
{
}

/************************************************************************/

AnimationInstance::~AnimationInstance()
{
	if(m_aniCon)
	{
		m_aniCon->Release();
		m_aniCon = 0;
	}

	delete [] m_boneMatrices;
}

/************************************************************************/

void
AnimationInstance::CreateAnimationInstance(LPD3DXANIMATIONCONTROLLER pAC)
{
	m_aniCon = pAC;
	m_numAnimation = m_aniCon->GetMaxNumAnimationSets();
	SetAnimation((unsigned int)0);
}

/************************************************************************/

void
AnimationInstance::Update(float elapsedTime, SkinnedMesh* mesh)
{
	elapsedTime /= m_speed;

	if(m_aniCon)
	{
		//advance the time of the animation controller
		m_aniCon->AdvanceTime(elapsedTime,NULL);
	}

	m_time += elapsedTime;

	Matrix tempWorld;
	MatrixIdentity(&tempWorld);

	//Update mesh
	UpdateFrame(mesh->GetFrameRoot(),&tempWorld);

	UpdateLocalBones(mesh->GetFrameRoot());
}

/************************************************************************/

void
AnimationInstance::UpdateFrame(const D3DXFRAME *base, const Matrix *parentMatrix)
{
	Frame* currentFrame = (Frame*)base;

	if (parentMatrix != NULL)
	{
		MatrixMultiply(&currentFrame->exCombinedTransformationMatrix,&currentFrame->TransformationMatrix,parentMatrix);
	}
	else
	{
		currentFrame->exCombinedTransformationMatrix = currentFrame->TransformationMatrix;

	}

	if(currentFrame->pFrameSibling != NULL)
	{
		UpdateFrame(currentFrame->pFrameSibling,parentMatrix);
	}

	if(currentFrame->pFrameFirstChild != NULL)
	{
		UpdateFrame(currentFrame->pFrameFirstChild,&currentFrame->exCombinedTransformationMatrix);
	}
}

/************************************************************************/

void
AnimationInstance::SetAnimation(unsigned int index)
{
	//if the index passed is the same as the current animation then return
	if (index == m_currentAnimationSet)
	{
		return;
	}
	//if index is greater than the number of animations, then return
	if(index >= m_numAnimation)
	{
		return;
	}

	m_currentAnimationSet = index;

	LPD3DXANIMATIONSET set;

	//get animation information
	m_aniCon->GetAnimationSet(m_currentAnimationSet,&set);

	DWORD newTrack = (m_track == 0 ? 1:0);

	//set the new animation track
	m_aniCon->SetTrackAnimationSet(newTrack,set);
	set->Release();

	m_aniCon->UnkeyAllTrackEvents(m_track);
	m_aniCon->UnkeyAllTrackEvents(newTrack);
	
	//end old track
	m_aniCon->KeyTrackEnable(m_track,FALSE,m_time + TRANSITIONTIME);
	m_aniCon->KeyTrackSpeed(m_track,0.0f,m_time,TRANSITIONTIME,D3DXTRANSITION_LINEAR );
	m_aniCon->KeyTrackWeight(m_track,0.0f, m_time,TRANSITIONTIME,D3DXTRANSITION_LINEAR );

	//blend into new track
	m_aniCon->SetTrackEnable(newTrack,TRUE);
	m_aniCon->KeyTrackSpeed(newTrack,1.0f,m_time,TRANSITIONTIME,D3DXTRANSITION_LINEAR );
	m_aniCon->KeyTrackWeight(newTrack,1.0f,m_time,TRANSITIONTIME,D3DXTRANSITION_LINEAR );
	m_aniCon->SetTrackPosition(newTrack,0);
	//set m_track
	m_track = newTrack;
}

/************************************************************************/

unsigned int
AnimationInstance::GetIndex(const char* name) const
{
	LPD3DXANIMATIONSET set;
	for (unsigned int i = 0; i < m_numAnimation; i++)
	{
		m_aniCon->GetAnimationSet(i,&set);

		if(_stricmp(name,set->GetName())==0)
		{
			return i;
		}
	}

	return -1;
}

/************************************************************************/

const char*
AnimationInstance::GetAnimationName() const
{
	LPD3DXANIMATIONSET set;
	m_aniCon->GetAnimationSet(m_currentAnimationSet,&set);

	return set->GetName();
}

/************************************************************************/

int
AnimationInstance::GetAnimation() const 
{
	return m_currentAnimationSet;
}

/************************************************************************/

void 
AnimationInstance::UpdateLocalBones(LPD3DXFRAME bone)
{
	MeshContainer* tempContainer = (MeshContainer*)bone->pMeshContainer;
	while (tempContainer)
	{

		if(tempContainer && tempContainer->pSkinInfo)
		{
			unsigned int bones = tempContainer->pSkinInfo->GetNumBones();

			for (unsigned int i = 0; i < bones; i++)
			{
				MatrixMultiply(&m_boneMatrices[i],&tempContainer->m_boneOffset[i],tempContainer->m_frameMatrix[i]);
			}
		}

		tempContainer = (MeshContainer*)tempContainer->pNextMeshContainer;

	}
	if (bone->pFrameSibling != NULL)
	{
		UpdateLocalBones(bone->pFrameSibling);
	}

	if (bone->pFrameFirstChild != NULL)
	{
		UpdateLocalBones(bone->pFrameFirstChild);
	}
}

/************************************************************************/