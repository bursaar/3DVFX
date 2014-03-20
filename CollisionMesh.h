#ifndef _COLLISIONMESH_H_
#define _COLLISIONMESH_H_

class PolygonData;
class Model;

class CollisionMesh
{
public:
	/**
	 * Constrcutor
	 */
								CollisionMesh();
	/**
	 * Destrcutor
	 */
								~CollisionMesh();
	/**
	 * Adds a mode with a transform to the collision mesh
	 */
	void						AddModelToCollisionMesh(
									Model* model, ///< New collision model
									const Matrix& position ///< The world transform to apply to this mesh whilst adding it
									);
	/**
	 * Renders the collision mesh
	 */
	void						Render();
	/**
	 * Tests to see if the line intersects with the collision mesh, returns true if an intersection has occurred
	 */
	bool						LineMeshTest(
									const Vector3D& start, ///< Line start
									const Vector3D& end, ///< Line End
									Vector3D& intersectionPoint, ///< The resulting intersection
									Vector3D& normal ///< Normal of the intersection
									);
	/**
	 * Tetst to see if a spehere moving between 2 points intersects with the collision mesh, returns true if an intersection has occurred
	 */
	bool						SphereSweepMeshTest(
									const Vector3D& start, ///< Sphere start point
									const Vector3D& end, ///< Sphere end point
									float radius, ///< Sphere radius
									Vector3D& intersectionPoint, ///< The resulting intersection point
									float& intersectionTime ///< The resulting intersction time (0-1 based upon the line)
									);
	/**
	 * Generates the search tree to optimise the generation of collision candidates
	 */
	void						CreateSearchTree();
	/**
	 * Returns the id of the collision mesh
	 */
	const char*					GetID() const;
	/**
	 * Sets the ID of the object
	 */
	void						SetID(
									const char* id
									);
	/**
	 * Gets the filename of the collision mesh
	 */
	const char*					GetFileName() const;
	/**
	 * Sets the filename of the collision mesh
	 */
	void						SetFileName(
									const char* name
									);
	/**
	 * Returns the volume of the collision mesh
	 */
	const AABB&					GetBox() const;
private:
	struct SearchTreeNode
	{
		SearchTreeNode*				childNodes[8];
		MyLinkedList<PolygonData*>*	polygons;
	};
	/**
	 * Initialises internal data
	 */
	void						Init();
	/**
	 * Generates the search node data(deciding wether to split the node or store the contained triangles)
	 */
	void						MakeSearchTree(
									SearchTreeNode* searchTreeNode, ///< The node
									const AABB& boundingBox, ///< The bounding volume of the node
									const MyLinkedList<PolygonData*>& polygons, ///< List of nodes inside or overlapping volume
									int levels ///< current level of the octree
									);
	/**
	 * Destroys all the data storage on the node and removes/destroys all chiild nodes
	 */
	void						ClearSearchTree(
									SearchTreeNode* searchTreeNode ///< Node to destroy data on
									);
	/**
	 * Returns a childs boounding volume for the child region index passed in
	 */
	void						GetSubRegion(
									const AABB& boundingBox, ///< Current nodes bound
									int regionIndex, ///< Child region index
									AABB& subBoundingBox ///< Resulting child bound
									);
	/**
	 * Test to see if a triangle is contained/overlaps within te bouding box, returns true if it does
	 */
	bool						IsTriangleInBox(
									const PolygonData* triangle, ///< Triangle to test
									const AABB& boundingBox ///< Bounding Box
									);
	/**
	 * Builds a list of potential overlapping polygons for a given volume
	 */
	void						BuildOctreeTrianglesList(
									SearchTreeNode* searchTreeNode, ///< Current octtree node
									const AABB& boundingBox, ///< Octree node bounding volume
									const AABB& searchBoundingBox, ///< Bounding volume to generate list for
									MyHashTable<PolygonData*>& polygons ///< Resulting triangles
									);
	/**
	 * Function to test line to polygon intersection
	 */
	static bool					LinePolyTest(
									const Vector3D& LA, ///< Line start
									const Vector3D& LB, ///< Line end
									const PolygonData& poly, ///< polygon
									Vector3D& intersectionPoint ///< resulting intersection point
									);
	/**
	 * Function to if a sphere moving between to points intersects with a polygon
	 */
	static bool					SphereSweepPolyTest(
									const Vector3D& start, ///< Sphere start point
									const Vector3D& end, ///< Sphere end point
									float radius, ///< Sphere radius
									const PolygonData& poly, ///< Polygon
									Vector3D& intersectionPoint, ///< Resulting intersection point
									float& intersectionTime ///< resulting intersection time
									);
	/**
	 * Returns if the point is contained within the triangle
	 */
	static bool					CheckPointInTriangle(
									const Vector3D& point, ///< Point to test
									const Vector3D& t1, ///< Triangle point 1
									const Vector3D& t2, ///< Triangle point 2
									const Vector3D& t3 ///< Triangle point 3
									);
	/**
	 * Calculates the smallest root
	 */
	static bool					GetSmallestRoot(
									float a, 
									float b, 
									float c, 
									float maxR, 
									float& root
									);

	MyString					m_id;
	MyString					m_fileName;
	MyLinkedList<PolygonData*>	m_data;
	AABB						m_box;
	SearchTreeNode				m_rootSearchTreeNode;
	AABB						m_searchBoundingBox;
	MyHashTable<PolygonData*>   m_polygons;
};

#endif // _COLLISIONMESH_H_

