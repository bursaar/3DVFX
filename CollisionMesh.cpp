#include "Types.h"
#include "PolygonData.h"
#include "EntityLoader.h"
#include "Model.h"
#include "CollisionMesh.h"

/************************************************************************/

CollisionMesh::CollisionMesh() :
	m_polygons(32, NORESIZE)
{
	Init();
}

/************************************************************************/

CollisionMesh::~CollisionMesh()
{
	ClearSearchTree(&m_rootSearchTreeNode);

	LinkedListNode<PolygonData*>* listNode = m_data.GetFirst();
	while (listNode)
	{
		delete listNode->GetData();
		listNode = listNode->GetNext();
	}
	m_data.Clear();
}

/************************************************************************/

void
CollisionMesh::Init()
{
	for (int index = 0; index < 8; ++index)
	{
		m_rootSearchTreeNode.childNodes[index] = NULL;
	}

	m_rootSearchTreeNode.polygons = NULL;
}

/************************************************************************/

void 
CollisionMesh::AddModelToCollisionMesh(Model* model, const Matrix& position)
{
	Mesh* mesh = model->GetMesh();

	BYTE* pVerts;
	HRESULT hr = mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVerts);
	if (hr != S_OK)
	{
		ErrorMessage("LockVertexBuffer Failed");
	}

	WORD* ppData;
	hr = mesh->LockIndexBuffer(D3DLOCK_READONLY, (void**)&ppData);
	if (hr != S_OK)
	{
		ErrorMessage("LockIndexBufferFailed");
	}

	D3DVERTEXELEMENT9 Decl[MAX_FVF_DECL_SIZE];
	hr = mesh->GetDeclaration(Decl);
	if(hr != S_OK)
	{
		ErrorMessage("GetDeclaration Failed");
	}
	UINT step = D3DXGetDeclVertexSize(Decl,0);


	DWORD* pAttr;
	hr = mesh->LockAttributeBuffer(D3DLOCK_READONLY, &pAttr);
	if(hr != S_OK)
	{
		ErrorMessage("LockAttributeBuffer Failed");
	}


	DWORD faces = mesh->GetNumFaces();

	for (DWORD i = 0 ; i < faces; ++i)
	{
		Vector3D vecA = *(Vector3D*)(pVerts+ppData[i*3]*step);
		Vector3D vecB = *(Vector3D*)(pVerts+ppData[i*3+1]*step);
		Vector3D vecC = *(Vector3D*)(pVerts+ppData[i*3+2]*step);

		Vector3DTransformCoord(&vecA, &vecA, &position);
		Vector3DTransformCoord(&vecB, &vecB, &position);
		Vector3DTransformCoord(&vecC, &vecC, &position);

		PolygonData* p = new PolygonData();
		p->SetVerts(vecA, vecB, vecC);
		m_data.Insert(p);

		m_box.AddPoint(vecA);
		m_box.AddPoint(vecB);
		m_box.AddPoint(vecC);
	}

	mesh->UnlockAttributeBuffer();
	mesh->UnlockIndexBuffer();
	mesh->UnlockVertexBuffer();
}

/************************************************************************/

void
CollisionMesh::CreateSearchTree()
{
	ClearSearchTree(&m_rootSearchTreeNode);
	MakeSearchTree(&m_rootSearchTreeNode, m_box, m_data, 8);
}

/************************************************************************/

void
CollisionMesh::Render()
{
	LinkedListNode<PolygonData*>* node = m_data.GetFirst();

	while (node)
	{
		node->GetData()->RenderDebug();
		node = node->GetNext();
	}
}

/************************************************************************/

bool
CollisionMesh::LineMeshTest(const Vector3D& start, const Vector3D& end, Vector3D& intersectionPoint, Vector3D& normal)
{
	Vector3D verts[] = { start, end };
	AABB searchBoundingBox(verts, 2);

	MyHashTable<PolygonData*> polygons(32,NORESIZE);

	BuildOctreeTrianglesList(&m_rootSearchTreeNode, m_box, searchBoundingBox, polygons);

	bool foundIntersection = false;
	float bestDistance = FLT_MAX;
	Vector3D thisIntersectionPoint;

	PolygonData* node = polygons.GetFirst();
	while (node)
	{
		if(LinePolyTest(start, end, *node, thisIntersectionPoint))
		{
			float distance = Vector3DLength(&(thisIntersectionPoint-start));
			if (distance < bestDistance)
			{
				normal = node->GetNormal();

				bestDistance = distance;
				intersectionPoint = thisIntersectionPoint;
				foundIntersection = true;
			}
		}

		node = polygons.GetNext();
	}

	return foundIntersection;
}

/************************************************************************/

bool
CollisionMesh::LinePolyTest(const Vector3D& LA, const Vector3D& LB, const PolygonData& poly, Vector3D& intersectionPoint)
{
	Vector3D dir = LB - LA;
	
	// Find vectors for two edges sharing vert0
	Vector3D edge1 = poly.GetVert(1) - poly.GetVert(0);
	Vector3D edge2 = poly.GetVert(2) - poly.GetVert(0);

	// Begin calculating determinant - also used to calculate U parameter
	Vector3D pvec;
	Vector3DCrossProduct(&pvec, &dir, &edge2);

	// If determinant is near zero, ray lies in plane of triangle
	float det = Vector3DDotProduct(&edge1, &pvec);

	Vector3D tvec;

	if( det > 0.f )
	{
		tvec = LA - poly.GetVert(0);
	}
	else
	{
		tvec = poly.GetVert(0) - LA;
		det = -det;
	}

	if (det < 0.0001f)
	{
		return false;
	}

	// Calculate U parameter and test bounds
	float u = Vector3DDotProduct(&tvec, &pvec);
	if (u < 0.0f || u > det)
	{	
		return false;
	}

	// Prepare to test V parameter
	Vector3D qvec;
	Vector3DCrossProduct(&qvec, &tvec, &edge1);

	// Calculate V parameter and test bounds
	float v = Vector3DDotProduct(&dir, &qvec);
	if (v < 0.0f || u + v > det)
	{
		return false;
	}
	
	// Calculate t, scale parameters, ray intersects triangle
	float t = Vector3DDotProduct(&edge2, &qvec);
	if (t < 0.0f || t > det)
	{	
		return false;
	}

	intersectionPoint = LA + dir * t / det;

	return true;
}

/************************************************************************/

bool
CollisionMesh::SphereSweepMeshTest(const Vector3D& start, const Vector3D& end, float radius, Vector3D& intersectionPoint, float& intersectionTime)
{
	Vector3D verts[] = { start - Vector3D(radius, radius, radius), end - Vector3D(radius, radius, radius), start + Vector3D(radius, radius, radius), end + Vector3D(radius, radius, radius) };
	AABB newBoundingBox(verts, 4);

	if (!m_searchBoundingBox.SurroundsAABB(newBoundingBox))
	{
		m_searchBoundingBox = newBoundingBox;
		m_polygons.Clear();
		BuildOctreeTrianglesList(&m_rootSearchTreeNode, m_box, m_searchBoundingBox, m_polygons);
	}

	bool hadCollision = false;
	intersectionTime = 1.0f;
	Vector3D thisIntersectionPoint;
	float thisIntersectionTime;

	PolygonData* node = m_polygons.GetFirst();
	while (node)
	{
		if(SphereSweepPolyTest(start, end, radius, *node, thisIntersectionPoint, thisIntersectionTime))
		{
			if (Vector3DDotProduct(&(end-start), &(thisIntersectionPoint-start)) > 0.0f)
			{
				if (!hadCollision || thisIntersectionTime < intersectionTime)
				{
					intersectionTime = thisIntersectionTime;
					intersectionPoint = thisIntersectionPoint;
					hadCollision = true;
				}
			}
		}

		node = m_polygons.GetNext();
	}

	return hadCollision;
}

/************************************************************************/

bool
CollisionMesh::SphereSweepPolyTest(const Vector3D& start, const Vector3D& end, float radius, const PolygonData& poly, Vector3D& intersectionPoint, float& intersectionTime)
{	
	bool hadCollision = false;
	intersectionTime = 1.0f;

	Vector3D delta = end - start;
	const Vector3D& normal = poly.GetNormal();
	float polyDistanceAlongNormal = Vector3DDotProduct(&poly.GetVert(0), &normal);

	float sphereCentreToPlaneDistance = Vector3DDotProduct(&start, &normal) - polyDistanceAlongNormal;
	float distanceAlongNormal = Vector3DDotProduct(&delta, &normal);

	float t0, t1;  // Interval of intersection
	bool embeded = false;

	// Is the sphere is moving parallel to the plane?
	if (distanceAlongNormal == 0.0f)
	{
		// Are we embedded in the plane?
		if (fabs(sphereCentreToPlaneDistance) < radius)
		{
			t0 = 0.0f;
			t1 = 1.0f;
			embeded = true;
		}
		else
		{
			// We're away from the plane and not heading towards it so we can't collide
			return false;
		}
	}
	else
	{
		t0 = (-radius - sphereCentreToPlaneDistance) / distanceAlongNormal;
		t1 = ( radius - sphereCentreToPlaneDistance) / distanceAlongNormal;

		if (t0 > t1)
		{
			float temp = t0;
			t0 = t1;
			t1 = temp;
		}

		if (t0 > 1.0f || t1 < 0.0f)
		{
			// Intersection outside interval range so we can't collide
			return false;
		}

		t0 = clamp(t0, 0.0f, 1.0f);
		t1 = clamp(t1, 0.0f, 1.0f);
	}

	if (!embeded)
	{
		// Check for a collision with the inside of the triangle
		Vector3D planeIntersectionPoint = start + delta * t0;
		planeIntersectionPoint -= normal * (Vector3DDotProduct(&planeIntersectionPoint, &normal) - polyDistanceAlongNormal);

		if (CheckPointInTriangle(planeIntersectionPoint, poly.GetVert(0), poly.GetVert(1), poly.GetVert(2)))
		{
			intersectionTime = t0;
			intersectionPoint = planeIntersectionPoint;
			return true;
		}
	}

	float newT;

	// Check for a collision with one of the triangle points
	float deltaSquaredLength = Vector3DLengthSq(&delta);

	for (int index = 0; index < 3; ++index)
	{
		float b = 2.0f * Vector3DDotProduct(&delta, &(start - poly.GetVert(index)));
		float c = Vector3DLengthSq(&(poly.GetVert(index) - start)) - radius * radius;
		if (GetSmallestRoot(deltaSquaredLength, b, c, intersectionTime, newT))
		{
			intersectionTime = newT;
			intersectionPoint = poly.GetVert(index);
			hadCollision = true;
		}
	}

	// Check for a collision with one of the triangle edges
	for (int index = 0; index < 3; ++index)
	{
		Vector3D edge = poly.GetVert((index+1)%3) - poly.GetVert(index);
		Vector3D baseToVertex = poly.GetVert(index) - start;
		float edgeSquaredLength = Vector3DLengthSq(&edge);
		float edgeDotDelta = Vector3DDotProduct(&edge, &delta);
		float edgeDotBaseToVertex = Vector3DDotProduct(&edge, &baseToVertex);

		float a = edgeSquaredLength * -deltaSquaredLength + edgeDotDelta * edgeDotDelta;
		float b = edgeSquaredLength * (2 * Vector3DDotProduct(&delta, &baseToVertex)) - 2.0f * edgeDotDelta * edgeDotBaseToVertex;
		float c = edgeSquaredLength * (radius * radius - Vector3DLengthSq(&baseToVertex))+ edgeDotBaseToVertex * edgeDotBaseToVertex;

		if (GetSmallestRoot(a, b, c, intersectionTime, newT))
		{
			float f = (edgeDotDelta * newT - edgeDotBaseToVertex) / edgeSquaredLength;
			if (f >= 0.0f && f <= 1.0f)
			{
				// Intersection took place within segment.
				intersectionTime = newT;
				intersectionPoint = poly.GetVert(index) + edge * f;
				hadCollision = true;
			}
		}
	}

	return hadCollision;
}

/************************************************************************/

bool
CollisionMesh::CheckPointInTriangle(const Vector3D& point, const Vector3D& t1, const Vector3D& t2, const Vector3D& t3)
{
	float total_angle = 0.f;

	Vector3D v1 = point - t1;
	Vector3D v2 = point - t2;
	Vector3D v3 = point - t3;

	Vector3DNormalize(&v1, &v1);
	Vector3DNormalize(&v2, &v2);
	Vector3DNormalize(&v3, &v3);

	float dp = clamp(Vector3DDotProduct(&v1, &v2), -1.0f, 1.0f);
	total_angle += acos(dp);
	dp = clamp(Vector3DDotProduct(&v2, &v3), -1.0f, 1.0f);
	total_angle += acos(dp);
	dp = clamp(Vector3DDotProduct(&v3, &v1), -1.0f, 1.0f);
	total_angle += acos(dp);

	if (fabs(total_angle-2*D3DX_PI) <= 0.005f)
	{
		return true;
	}

	return false;
}

/************************************************************************/

bool
CollisionMesh::GetSmallestRoot(float a, float b, float c, float maxR, float& root)
{
	float determinant = b*b - 4.0f * a * c;

	if (determinant < 0.0f)
	{
		return false;
	}

	float sqrtD = sqrt(determinant);
	float r1 = (-b - sqrtD) / (2*a);
	float r2 = (-b + sqrtD) / (2*a);

	if (r1 > r2)
	{
		if (r2 > 0 && r2 < maxR)
		{
			root = r2;
			return true;
		}

		if (r1 > 0 && r1 < maxR)
		{
			root = r1;
			return true;
		}
	}
	else
	{
		if (r1 > 0 && r1 < maxR)
		{
			root = r1;
			return true;
		}

		if (r2 > 0 && r2 < maxR)
		{
			root = r2;
			return true;
		}
	}


	return false;
}

/*******************************************************************************************************/

void
CollisionMesh::MakeSearchTree(SearchTreeNode* searchTreeNode, const AABB& boundingBox, const MyLinkedList<PolygonData*>& polygons, int levels)
{
	int numEntries = 0;
	LinkedListNode<PolygonData*>* listNode = polygons.GetFirst();

	while (listNode)
	{
		numEntries++;
		listNode = listNode->GetNext();
	}

	if (levels == 0 || numEntries < 5)
	{
		// This is a leaf node so copy the triangle list into the node
		searchTreeNode->polygons = new MyLinkedList<PolygonData*>;

		LinkedListNode<PolygonData*>* listNode = polygons.GetFirst();
		while (listNode)
		{
			searchTreeNode->polygons->Insert(listNode->GetData());
			listNode = listNode->GetNext();
		}

		for (int regionIndex = 0; regionIndex < 8; ++regionIndex)
		{
			searchTreeNode->childNodes[regionIndex] = NULL;
		}
	}
	else
	{
		MyLinkedList<PolygonData*> subList;

		for (int regionIndex = 0; regionIndex < 8; ++regionIndex)
		{
			subList.Clear();

			AABB subBoundingBox;
			GetSubRegion(boundingBox, regionIndex, subBoundingBox);

			int numEntries = 0;
			LinkedListNode<PolygonData*>* listNode = polygons.GetFirst();
			while (listNode)
			{
				if (IsTriangleInBox(listNode->GetData(), subBoundingBox))
				{
					subList.Insert(listNode->GetData());
					numEntries ++;
				}

				listNode = listNode->GetNext();
			}

			if (numEntries)
			{
				searchTreeNode->childNodes[regionIndex] = new SearchTreeNode;
				searchTreeNode->childNodes[regionIndex]->polygons = NULL;
				MakeSearchTree(searchTreeNode->childNodes[regionIndex], subBoundingBox, subList, levels-1);
			}
			else
			{
				searchTreeNode->childNodes[regionIndex] = NULL;
			}
		}
	}
}

/************************************************************************/

void
CollisionMesh::ClearSearchTree(SearchTreeNode* searchTreeNode)
{
	if (searchTreeNode->polygons)
	{
		delete searchTreeNode->polygons;
		searchTreeNode->polygons = NULL;
	}

	for (int regionIndex = 0; regionIndex < 8; ++regionIndex)
	{
		if (searchTreeNode->childNodes[regionIndex])
		{
			ClearSearchTree(searchTreeNode->childNodes[regionIndex]);
			delete searchTreeNode->childNodes[regionIndex];
		}
	}
}

/************************************************************************/

void
CollisionMesh::GetSubRegion(const AABB& boundingBox, int regionIndex, AABB& subBoundingBox)
{
	Vector3D min, max;

	if (regionIndex & 1)
	{
		min.x = (boundingBox.GetMin().x + boundingBox.GetMax().x) / 2;
		max.x = boundingBox.GetMax().x;
	}
	else
	{
		min.x = boundingBox.GetMin().x;
		max.x = (boundingBox.GetMin().x + boundingBox.GetMax().x) / 2;
	}

	if (regionIndex & 2)
	{
		min.y = (boundingBox.GetMin().y + boundingBox.GetMax().y) / 2;
		max.y = boundingBox.GetMax().y;
	}
	else
	{
		min.y = boundingBox.GetMin().y;
		max.y = (boundingBox.GetMin().y + boundingBox.GetMax().y) / 2;
	}

	if (regionIndex & 4)
	{
		min.z = (boundingBox.GetMin().z + boundingBox.GetMax().z) / 2;
		max.z = boundingBox.GetMax().z;
	}
	else
	{
		min.z = boundingBox.GetMin().z;
		max.z = (boundingBox.GetMin().z + boundingBox.GetMax().z) / 2;
	}

	subBoundingBox.SetMin(min);
	subBoundingBox.SetMax(max);
}

/************************************************************************/

bool
CollisionMesh::IsTriangleInBox(const PolygonData* triangle, const AABB& boundingBox)
{
	AABB box(triangle);

	return boundingBox.CheckCollisionAABB(box);
}

/************************************************************************/

void
CollisionMesh::BuildOctreeTrianglesList(SearchTreeNode* searchTreeNode, const AABB& boundingBox, const AABB& searchBoundingBox, MyHashTable<PolygonData*>& polygons)
{
	if (boundingBox.CheckCollisionAABB(searchBoundingBox))
	{
		if (searchTreeNode->polygons)
		{
			LinkedListNode<PolygonData*>* listNode = searchTreeNode->polygons->GetFirst();
			while (listNode)
			{
				if (!polygons.Find(listNode->GetData()))
				{
					polygons.Insert(listNode->GetData(), listNode->GetData());
				}

				listNode = listNode->GetNext();
			}
		}
		else
		{
			for (int regionIndex = 0; regionIndex < 8; ++regionIndex)
			{
				if (searchTreeNode->childNodes[regionIndex])
				{
					AABB subBoundingBox;
					GetSubRegion(boundingBox, regionIndex, subBoundingBox);
					BuildOctreeTrianglesList(searchTreeNode->childNodes[regionIndex], subBoundingBox, searchBoundingBox, polygons);
				}
			}
		}
	}
}

/************************************************************************/

void
CollisionMesh::SetID(const char* id)
{
	m_id = id;
}

/************************************************************************/

const char* 
CollisionMesh::GetID() const
{
	return m_id.GetPointer();
}

/************************************************************************/

void
CollisionMesh::SetFileName(const char* name)
{
	m_fileName = name;
}

/************************************************************************/

const char*
CollisionMesh::GetFileName() const
{
	return m_fileName;
}

/************************************************************************/

const AABB&
CollisionMesh::GetBox() const
{
	return m_box;
}

/************************************************************************/