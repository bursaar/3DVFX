#ifndef _AABB_H_
#define _AABB_H_

class PolygonData;

class AABB
{
public:
	/**
	 * Constructor
	 */
					AABB();
	/**
	 * Constructor from 2 vectors
	 */
					AABB(
						const Vector3D& min, 
						const Vector3D& max
						);
	/**
	 * Constructor from vector array
	 */
					AABB(
						const Vector3D* vertArray, 
						int vertCount
						);
	/**
	 * Constructor from polygon data
	 */
					AABB(
						const PolygonData* polygon
						);
	/**
	 * Constructor from a mesh
	 */
					AABB(
						Mesh* mesh
						);
	/**
	 * Destructor
	 */
					~AABB();
	/**
	 * Sets the volume minimum
	 */
	void			SetMin(
						const Vector3D& min
						);
	/**
	 * Returns the volume minimum
	 */
	const Vector3D& GetMin() const;
	/**
	 * Sets the volume maximum
	 */
	void			SetMax(
						const Vector3D& max
						);
	/**
	 * Gets the volume maximum
	 */
	const Vector3D& GetMax() const;
	/**
	 * Adds on the specified amount onto the volume
	 */
	void			MoveAABB(
						const Vector3D& position
						);
	/**
	 * Returns true if the 2 volumes overlap
	 */
	bool			CheckCollisionAABB(
						const AABB& otherAABB
						) const;

	/**
	 * Returns true if this volume contains the other
	 */
	bool			SurroundsAABB(
						const AABB& otherAABB
						) const;
	/**
	 * Updates the min & max by comparing with this point
	 */
	void			AddPoint(
						const Vector3D& pos
						);

private:
	Vector3D m_min;
	Vector3D m_max;
};

#endif //_AABB_H_
