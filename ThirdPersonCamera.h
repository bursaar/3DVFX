#ifndef _THIRDPERSONCAMERA_H_
#define _THIRDPERSONCAMERA_H_

//////////////////////////////////////////////////////////////////////////
//ThirdPersonCamera
//
//The Third Person Camera is a camera that is designed to rotate around an object
//keeping the same distance away from it, even if the object is moving,
//////////////////////////////////////////////////////////////////////////


#ifndef _BASECAMERA_H_
#include "BaseCamera.h"
#endif

class ThirdPersonCamera : public BaseCamera
{
public:
	/**
	 * Constructor
	 */
							ThirdPersonCamera();
	/**
	 * Destructor
	 */
							~ThirdPersonCamera();
	/**
	 * Returns the type of the camera
	 */
	virtual const char*		GetType() const {return "THIRDPERSON";};
	/**
	 * Calculates the view matrix for this camera
	 */
	virtual void			CreateViewMatrix(
								Matrix& view
								);
	/**
	 * Calculates the projection matrix for this camera
	 */
	virtual void			CreateProjectionMatrix(
								Matrix& projection
								);
	/**
	 * Updates the cameras movement
	 */
	virtual void			ProcessKeys(
								float elapsedTime
								);	
	/**
	 * Sets the distance from the object its viewing
	 */
	void					SetDistanceFromObject(
								float distance
								);
	/**
	 * Sets up the third person camera angles
	 */
	void					SetUpThirdPersonCamera(
								float yaw, 
								float pitch
								);
	/**
	 * Sets the y rotation to target
	 */
	void					SetTargetYaw(
								float yaw
								);
private:
	float m_distance;
	float m_targetDistance;

	float m_yaw;
	float m_targetYaw;
	float m_pitch;
	float m_targetPitch;

	float m_intersectionTime;

	bool m_tendTo;
};

#endif //_THIRDPERSONCAMERA_H_
