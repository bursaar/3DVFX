#ifndef _FRUSTUM_H
#define _FRUSTUM_H

class Sphere;

class Frustum
{
public:
	/**
	 * Constructor
	 */
								Frustum();
	/**
	 * Destructor
	 */
								~Frustum();
	/**
	 * Recalculates the frustrum planes for the specified view & projection matricies
	 */
	void						Calculate(
									const Matrix& view, ///< The new view matrix
									const Matrix& projection, ///< The new projection matrix
									bool normalize = true ///< Should we normalise the planes
									);
	/**
	 * Returns if a point is visible
	 */
	bool						PointVisible(
									const Vector3D& point ///< The point to test
									) const;
	/**
	 * Returns if a sphere is visible
	 */
	bool						SphereVisible(
									const Sphere& sphere ///< The sphere to test
									) const;
	/**
	 * Returns if a sphere is visible
	 */
	bool						SphereVisible(
									const Vector3D& position, ///< The centre of the sphere to test
									float radius ///< The radius of the sphere to test
									) const;
	/**
	 * Returns if a AABB is visible
	 */
	bool						BoxVisible(
									const AABB& aabb ///< the aabb to test
									) const;
private:
	enum
	{
		PLEFT = 0,
		PRIGHT,
		PTOP,
		PBOTTOM,
		PNEAR,
		PFAR,
		NUM_PLANES
	};

	/// Represents one of the frustrums planes
	struct Plane
	{
		Vector3D normal; 
		float	 distance;

		inline void Normalise()
		{
			float denom = 1 / Vector3DLength(&normal);
			normal *= denom;
			distance *= denom;
		}
	};
	/**
	 * Returns the distance a point is from a plane
	 */
	float				DistancePointPlane(
							const Plane& testPlane, ///< Plane to test
							const Vector3D& point ///< Position to test
							) const;

	Plane m_frustumPlanes[NUM_PLANES];
};

#endif