#ifndef _CAMERACONTROLLER_H_
#define _CAMERACONTROLLER_H_

//////////////////////////////////////////////////////////////////////////
//CameraController Class
//
//This controls the cameras used within the program and the matrices used for
//world, view and projection. using the current camera (which consist of a choice of free camera, third person and static cameras)
//matrices are created when the rendering process is called, the world matrix can also be called by mesh based object, so 
//the world matrix can be directly effected translations, and then reset back.
//
//Camera created are stored within a list with the current active camera stored within a BaseCamera pointer.
//////////////////////////////////////////////////////////////////////////

#ifndef _TYPES_H_
#include "Types.h"
#endif //_TYPES_H_

#ifndef _FRUSTUM_H_
#include "Frustum.h"
#endif //#ifndef _FRUSTUM_H_

class BaseCamera;
class CameraController : public Singleton<CameraController>
{
public:
	/**
	 * Constrcutor
	 */
							CameraController();
	/**
	 * Destructor
	 */
							~CameraController();
	/**
	 * Adds a camera to the stack of active cameras
	 */
	void					AddCamera(
								BaseCamera* newCamera
								);
	/**
	 * Removes the camera which is currently at the top of the stack
	 * and restores the new top
	 */
	void					RemoveCamera();
	/**
	 * Creates the view & projection matrices and binds them for use
	 */
	void					ComputeCamera();
	/**
	 *	Updates the currentl active camera
	 */
	void					Update(
								float elapsedTime ///< The amount of elapsed time this frame
								);
	/**
	 * Sets the world matrix to use
	 */
	void					SetWorld(
								const Matrix& world
								);
	/**
	 * Sets the world matrix to be identity
	 */
	void					ResetWorld();
	/**
	 * Updates the view matrix from the currently active camera
	 */
	void					CreateViewMatrix();
	/**
	 * Updates the projection matrix from the currently active camera
	 */
	void					CreateProjectionMatrix();
	/**
	 * Returns the currently active camera
	 */
	BaseCamera*				GetCurrentCamera() const;
	/**
	 * Get the currently bound world matrix
	 */
	const Matrix&			GetWorld() const;
	/**
	 * Gets the view matrix
	 */
	const Matrix&			GetView() const;
	/**
	 * Sets the current projection matrix to use
	 */
	void					SetProjection(
								const Matrix& newMat
								);
	/**
	 * Sets the current view matrix to use
	 */
	void					SetView(
								const Matrix& newMat
								);
	/**
	 * Gets the current porjection matrix
	 */
	const Matrix&			GetProjection() const;
	/**
	 * Gets the current view matrix
	 */
	const Matrix&			GetViewProjection() const;
	/**
	 * Returns the current camera position
	 */
	const Vector3D&			GetCurrentCameraPosition() const;
	/**
	 * Returns the frustrum object to enable cullng tests to be performed
	 */
	const Frustum&			GetFrustum() const;
private:

	static const int c_MaxCameraCount = 16;
	//camera variables
	BaseCamera* m_currentCamera;
	BaseCamera* m_cameras[c_MaxCameraCount];
	int m_cameraCount;

	

	//World View and Projection Matrices
	Matrix m_world;
	Matrix m_view;
	Matrix m_projection;
	Frustum m_viewFrustum;

};

#endif // _CAMERACONTROLLER_H_
