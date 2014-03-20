#ifndef _BASECAMERA_H_
#define _BASECAMERA_H_

//////////////////////////////////////////////////////////////////////////
//BaseCamera
//
//This is the Base class for cameras used within the program, it contains virtual method for
//Creating view and projection matrices and process keyboard commands.
//
//It also contains accessors to each variable that are required for all camera types,
//including camera position, target and up vectors, Field of view, aspect ratio at so on. 
//////////////////////////////////////////////////////////////////////////

class Frustum;
class BaseCamera
{
public:
	/**
	 * Constructor
	 */
							BaseCamera();
	/**
	 * Destructor
	 */
	virtual					~BaseCamera();
	/**
	 * Returns the type id of the camera type
	 */
	virtual const char*		GetType() const = 0;
	/**
	 * Updates the camera based upon the key presses and the elapsed time
	 */
	virtual void			ProcessKeys(
								float elapsedTime ///< The elapsed time this frame
								) = 0;
	/**
	 * Performs the camera setup for the camera controller
	 */
	virtual void			SetupCamera(
								const Vector3D& position, ///< The position of the camera
								const Vector3D& at, ///< The at vector of the camera
								const Vector3D& up ///< The cameras up vector
								);
	/**
	 * Creates a view matrix for the camera
	 */
	virtual void			CreateViewMatrix(
								Matrix& view ///< the result view matrix
								) = 0;
	/**
	 * Creates a projection matrix for the camera
	 */
	virtual void			CreateProjectionMatrix(
								Matrix& projection ///< The result projection matrix
								) = 0;
	/**
	 * Moves the camera to the specified position lookAt and up verctor
	 */
	void					PositionCamera(
								const Vector3D& position, ///< The position to move the camera to
								const Vector3D& at, ///< The at vector of the camera
								const Vector3D& up ///< The vector for the up direction of the camera
								);
	/**
	 * Rotates the camera by the specified euluer angles.
	 */
	void					RotateView(
								const Vector3D& rotate ///< The angles through which to rotate the camera
								);
	/**
	 * Sets the current position of the camera
	 */
	void					SetPosition(
								const Vector3D& position ///< The new position of the camera
								);
	/**
	 * Gets the current position of the camera
	 */
	const Vector3D&			GetPosition() const;
	/**
	 * Sets the at vector of the camera
	 */
	void					SetTarget(
								const Vector3D& target
								);
	/**
	 * Gets the at vector of the camera
	 */
	const Vector3D&			GetTarget() const;
	/**
	 * Sets the up vector of the camera
	 */
	void					SetUp(
								const Vector3D& up
								);
	/**
	 * Gets the up vector of the camera
	 */
	const Vector3D&			GetUp() const;
	/**
	 * Sets the FOV angle
	 */
	void					SetFieldofView(
								float FOV
								);
	/**
	 * Gets the FOV angle
	 */
	float					GetFieldofView() const;
	/**
	 * Sets the aspect ratio
	 */
	void					SetAspectRatio(
								float ar
								);
	/**
	 * Gets the current aspect ratio
	 */
	float					GetAspectRatio() const;
	/**
	 * Sets the near clipping plane
	 */
	void					SetNearPlane(
								float np
								);
	/**
	 * Gets the current near plane
	 */
	float					GetNearPlane() const;
	/**
	 * Sets the far clipping plane
	 */
	void					SetFarPlane(
								float fp
								);
	/**
	 * Gets the current far plane
	 */
	float					GetFarPlane() const;
protected:
	
	//variables
	Vector3D m_position;
	Vector3D m_target;
	Vector3D m_up;
	Vector3D m_right;

	float m_fieldOfViewY;
	float m_aspectRatio;
	float m_nearPlane;
	float m_farPlane;


};


#endif // _BASECAMERA_H_