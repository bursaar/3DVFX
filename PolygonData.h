#ifndef _POLYGONDATA_H_
#define _POLYGONDATA_H_

class PolygonData
{
public:
	/**
	 * Constructor
	 */
							PolygonData();
	/**
	 * Destructor
	 */
							~PolygonData();
	/**
	 * Updates the 3 points of the polygon and recalculates the normal
	 */
	void					SetVerts(
								const Vector3D& vert0, 
								const Vector3D& vert1, 
								const Vector3D& vert2
								);
	/**
	 * Renders the polygon for debug purposes
	 */
	void					RenderDebug();
	/**
	 * Gets the specified vertex of the polygon
	 */
	const Vector3D&			GetVert(
								int index ///< Index of the vertex to retrieve
								) const;
	/**
	 * Returns the normal of the polygon
	 */
	const Vector3D&			GetNormal() const;
private:
	Vector3D m_verts[3];
	Vector3D m_normal;
};

#endif //_POLYGONDATA_H_