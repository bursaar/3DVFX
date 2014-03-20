#ifndef _ENVIRONMENTMAMANGER_H_
#define _ENVIRONMENTMAMANGER_H_

class Environment;
class CollisionMesh;
class BillBoardRegion;

class EnvironmentManager : public Singleton<EnvironmentManager>
{
public:
	/**
	 * Constructor
	 */
						EnvironmentManager();
	/**
	 * Destructor
	 */
						~EnvironmentManager();
	/**
	 * Adds an new environment model
	 */
	void				AddModel(
							const char* ID, ///< Id of the environment model
							const char* fileName, ///< Filename of the environment model
							const Vector3D& position = Vector3D(0,0,0), ///< Position of the model
							const Vector3D& rotation = Vector3D(0,0,0), ///< Rotation of the model
							float scale = 1.0f, ///< Scale of the model
							int UVMultiply = 1.0f ///< UV multiply scale
							);
	/**
	 * Adds an new collision mesh
	 */
	void				AddCollisionMesh(
							const char* ID, ///< Id of the collision mesh
							const char* fileName ///< Filename of the collision mesh
							);
	/**
	 * Performs intersection tests along a line, returns true if an intersection occured
	 */
	bool				TestCollision(
							const Vector3D& lineSrc, ///< Line start
							const Vector3D& lineDes, ///< Line end
							Vector3D& intersectionPoint ///< Intersection result
							);
	/**
	 * Renders the environment models
	 */
	void				Render();
	/**
	 * Returns the collision mesh
	 */
	CollisionMesh*		GetCollisionMesh();
	/**
	 * Adds an new billboard region
	 */
	void				AddBillBoardRegion(
							BillBoardRegion* billboards ///< The new billboard region
							);

private:
	static const int c_MaxEnvironmentModels = 32;
        static const int c_MaxBillBoardRegions = 128;

	int m_numModels;
	Environment* m_models[c_MaxEnvironmentModels];
	
	CollisionMesh* m_collisionMesh;
	
        BillBoardRegion* m_billboardRegions[c_MaxBillBoardRegions];
	int m_numBillboardRegions;

};

#endif //_ENVIRONMENTMAMANGER_H_
