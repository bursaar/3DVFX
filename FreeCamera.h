#ifndef _FREECAMERA_H_
#define _FREECAMERA_H_

//////////////////////////////////////////////////////////////////////////
//FreeCamera Class
//
//Using the BaseCamera Class as a base, the FreeCamera Class allows the user
//to move the camera using the keyboard and rotate the camera using the mouse.
//much like a first person camera, but without the y axis restrictions.
//////////////////////////////////////////////////////////////////////////

#ifndef _BASECAMERA_H_
#include "BaseCamera.h"
#endif

class FreeCamera : public BaseCamera
{
public:
	/**
	 * Constructor
	 */
							FreeCamera();
	/**
	 * Destructor
	 */
							~FreeCamera();
	/**
	 * Returns the type of the camera
	 */
	virtual const char*		GetType() const {return "FREECAM";};
	/**
	 * Calculates the view matrix for this camera
	 */
	virtual void			CreateViewMatrix(
								Matrix& view ///< The result view matrix
								);
	/**
	 * Calculates the porjection matrix for this camera
	 */
	virtual void			CreateProjectionMatrix(
								Matrix& projection ///< The result projection matrix
								);
	/**
	 * Updates the cameras movement
	 */
 	virtual void			ProcessKeys(
								float elapsedTime ///< The elapsed time for this frame
								);
private:
	float m_angle;
	float m_pitch;
	float m_speed;
	float m_xRot;
	float m_yRot;
};

#endif // _FREECAMERA_H_
