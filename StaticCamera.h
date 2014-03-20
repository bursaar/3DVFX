#ifndef _STATICCAMERA_H_
#define _STATICCAMERA_H_

//////////////////////////////////////////////////////////////////////////
//Static Camera.
//
//Static Camera is a camera with fixed position and direction and is not controllable by the user directly
//the camera itself could be controlled within code.
//
//////////////////////////////////////////////////////////////////////////

#ifndef _BASECAMERA_H_
#include "BaseCamera.h"
#endif

class StaticCamera : public BaseCamera 
{
public:
	/**
	 * Constructor
	 */
						StaticCamera();
	/**
	 * Destructor
	 */
						~StaticCamera();
	/**
	 * Returns the type id of the camera type
	 */
	virtual const char* GetType() const {return "STATICCAMERA";};
	/**
	 * Performs the camera setup for the camera controller
	 */
	virtual void		SetupCamera(
							const Vector3D& position,
							const Vector3D& target,
							const Vector3D& up
							);
	/**
	 * Calculates the view matrix for this camera
	 */
	virtual void		CreateViewMatrix(
							Matrix& view
							);
	/**
	 * Calculates the projection matrix for this camera
	 */
	virtual void		CreateProjectionMatrix(
							Matrix& projection
							);
	/**
	 * No update is needed
	 */
	virtual void		ProcessKeys(
							float elapsedTime
							){};
private:


};

#endif
