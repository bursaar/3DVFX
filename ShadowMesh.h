#ifndef _SHADOWMESH_H_
#define _SHADOWMESH_H_

#define ADJACENCY_EPSILON 0.0001f

struct EdgeMapping
{
	int m_oldEdge[2];
	int m_newEdge[2][2];

	EdgeMapping()
	{
		FillMemory(m_oldEdge,sizeof(m_oldEdge),-1);
		FillMemory(m_newEdge,sizeof(m_newEdge),-1);
	}
};

class ShadowMesh
{
public:
	ShadowMesh(void);
	~ShadowMesh(void);

	static HRESULT CreateShadowMesh(Mesh* Object, Mesh** OutPutMesh);

	static int FindEdgeInMappingTable(int nV1, int nV2, EdgeMapping *pMapping, int nCount);

	static void ComputeNewEdges(EdgeMapping *mapping, DWORD* IndexData, int& numberEdges, int& nextIndex, int V1, int V2,int index,int vertCount, int offset1, int offset2);
	
	static IDirect3DVertexDeclaration9* GetShadowDecl();


private:

};

#endif //_SHADOWMESH_H_

