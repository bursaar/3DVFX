#include "Types.h"
#include "ShadowMesh.h"
#include "Vertex.h"

static IDirect3DVertexDeclaration9* m_shadowDecl = 0;

struct SHADOWVERT
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Normal;
	float weight0;
	unsigned char BoneIndices[4];
	


	const static D3DVERTEXELEMENT9 Decl[5];
};

const D3DVERTEXELEMENT9 SHADOWVERT::Decl[5] =
{
	{ 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
	{ 0, 24, D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0 },
	{ 0, 28, D3DDECLTYPE_UBYTE4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 0 },

	D3DDECL_END()
};

ShadowMesh::ShadowMesh(void)
{

}

ShadowMesh::~ShadowMesh(void)
{
}

int
ShadowMesh::FindEdgeInMappingTable(int nV1, int nV2, EdgeMapping *pMapping, int nCount)
{
	for (int i = 0; i < nCount; i++)
	{
		if((pMapping[i].m_oldEdge[0] == -1 && pMapping[i].m_oldEdge[1] == -1) ||  ( pMapping[i].m_oldEdge[1] == nV1 && pMapping[i].m_oldEdge[0] == nV2 ) )
		{
			return i;
		}
	}
	ErrorMessage("no edge");
	return -1;
}

void 
ShadowMesh::ComputeNewEdges(EdgeMapping *mapping, DWORD* IndexData, int& numberEdges, int& nextIndex, int V1, int V2,int index,int vertCount, int offset1, int offset2)
{
	if(index == -1)
	{
		ErrorMessage("edge not found");
	}

	if(mapping[index].m_oldEdge[0] == -1 && mapping[index].m_oldEdge[1] == -1)
	{
		mapping[index].m_oldEdge[0] = V1;
		mapping[index].m_oldEdge[1] = V2;
		mapping[index].m_newEdge[0][0] = vertCount * 3 + offset1;
		mapping[index].m_newEdge[0][1] = vertCount * 3 + offset2;

		numberEdges++;
	}
	else
	{
		if (numberEdges <= 0)
		{
			ErrorMessage("numberEdges less than zero");
		}

		mapping[index].m_newEdge[1][0] = vertCount * 3 + offset1;
		mapping[index].m_newEdge[1][1] = vertCount * 3 + offset2;

		IndexData[nextIndex++] = mapping[index].m_newEdge[0][1];
		IndexData[nextIndex++] = mapping[index].m_newEdge[0][0];
		IndexData[nextIndex++] = mapping[index].m_newEdge[1][0];

		IndexData[nextIndex++] = mapping[index].m_newEdge[1][1];
		IndexData[nextIndex++] = mapping[index].m_newEdge[1][0];
		IndexData[nextIndex++] = mapping[index].m_newEdge[0][0];


		mapping[index] = mapping[numberEdges - 1];
		FillMemory (&mapping[numberEdges - 1], sizeof (mapping[numberEdges - 1]), 0xFF);
		numberEdges--;
	}
}

//////////////////////////////////////////////////////////////////////////
//CreateShadowMesh
//
//////////////////////////////////////////////////////////////////////////
HRESULT 
ShadowMesh::CreateShadowMesh(Mesh* Object, Mesh** OutPutMesh)
{
	if(!m_shadowDecl)
	{
		m_D3DDevice->CreateVertexDeclaration( SHADOWVERT::Decl, &m_shadowDecl);
	}
	HRESULT hr;
	Mesh* inputMesh;

	if(!OutPutMesh)
	{
		ErrorMessage("Invalid Arguement, no OutMesh");
	}

	D3DVERTEXELEMENT9 Decl[MAX_FVF_DECL_SIZE];
	hr = Object->GetDeclaration(Decl);

	
	hr = Object->CloneMesh(D3DXMESH_32BIT,(D3DVERTEXELEMENT9*)SHADOWVERT::Decl,m_D3DDevice,&inputMesh);

	if(hr != S_OK)
	{
		ErrorMessage("didnot Clone Mesh");
	}

	DWORD* tempAdj = new DWORD[3 * inputMesh->GetNumFaces()];
	DWORD* tempAdjVerts = new DWORD[inputMesh->GetNumVertices()];

	if (!tempAdj || ! tempAdjVerts)
	{
		delete[] tempAdj;
		delete[] tempAdjVerts;
		inputMesh->Release();
		ErrorMessage("no faces or verts found");
	}

	hr = inputMesh->GenerateAdjacency(ADJACENCY_EPSILON,tempAdj);

	if(hr != S_OK)
	{
		delete[] tempAdj;
		delete[] tempAdjVerts;
		inputMesh->Release();
		ErrorMessage("GenerateAdjacency failes");
	}

	inputMesh->ConvertAdjacencyToPointReps(tempAdj,tempAdjVerts);

	delete[] tempAdj;

	SHADOWVERT * vertexData = NULL;
	DWORD * indexData = NULL;

	inputMesh->LockVertexBuffer(0,(LPVOID*)&vertexData);
	inputMesh->LockIndexBuffer(0,(LPVOID*)&indexData);

	if(vertexData && indexData)
	{
		DWORD numEdges = inputMesh->GetNumFaces() * 3;
		EdgeMapping *mapping = new EdgeMapping[numEdges];
		
		if(mapping)
		{
			int numMaps = 0;

			Mesh* newMesh;
			hr = D3DXCreateMesh(inputMesh->GetNumFaces() + numEdges * 2,
				inputMesh->GetNumFaces() * 3,
				D3DXMESH_32BIT,
				(D3DVERTEXELEMENT9*)SHADOWVERT::Decl,
				m_D3DDevice,
				&newMesh);
			
			if(hr == S_OK)
			{
				SHADOWVERT * newVertexData = NULL;
				DWORD* newIndexData = NULL;

				newMesh->LockVertexBuffer(0,(LPVOID*)&newVertexData);
				newMesh->LockIndexBuffer(0,(LPVOID*)&newIndexData);
				
				int nextIndex = 0;

				if(newVertexData && newIndexData)
				{
					ZeroMemory(newVertexData, newMesh->GetNumVertices() * newMesh->GetNumBytesPerVertex());
					ZeroMemory(newIndexData, sizeof(DWORD)* newMesh->GetNumFaces() * 3);

					SHADOWVERT * nextVertOut = newVertexData;

					for(UINT count = 0; count < inputMesh->GetNumFaces(); count++)
					{
						
						CopyMemory(nextVertOut,vertexData + indexData[count * 3],sizeof(SHADOWVERT));
						CopyMemory(nextVertOut + 1,vertexData + indexData[count * 3 + 1],sizeof(SHADOWVERT));
						CopyMemory(nextVertOut + 2,vertexData + indexData[count * 3 + 2],sizeof(SHADOWVERT));

						newIndexData[nextIndex++] = count * 3;
						newIndexData[nextIndex++] = count * 3 + 1;
						newIndexData[nextIndex++] = count * 3 + 2;

						Vector3D v1,v2,normal;
						v1 = *(Vector3D*)(nextVertOut + 1) - *(Vector3D*)nextVertOut;
						v2 = *(Vector3D*)(nextVertOut + 2) - *(Vector3D*)(nextVertOut + 1);

						Vector3DCrossProduct(&normal,&v1,&v2);
						Vector3DNormalize(&normal,&normal);

						nextVertOut->Normal = normal;
						(nextVertOut + 1)->Normal = normal;
						(nextVertOut + 2)->Normal = normal;

						nextVertOut += 3;
						
						int edgeIndex;
						int vertIndex[3] = {tempAdjVerts[indexData[count * 3]],
											tempAdjVerts[indexData[count * 3 + 1]],
											tempAdjVerts[indexData[count * 3 + 2]]};

						edgeIndex = FindEdgeInMappingTable(vertIndex[0],vertIndex[1],mapping,numEdges);
						
						ComputeNewEdges(mapping,newIndexData,numMaps,nextIndex,vertIndex[0],vertIndex[1],edgeIndex,count,0,1);
					
						edgeIndex = FindEdgeInMappingTable( vertIndex[1], vertIndex[2], mapping, numEdges );

						ComputeNewEdges(mapping,newIndexData,numMaps,nextIndex,vertIndex[1],vertIndex[2],edgeIndex,count,1,2);	
						
						edgeIndex = FindEdgeInMappingTable( vertIndex[2], vertIndex[0], mapping, numEdges );

						ComputeNewEdges(mapping,newIndexData,numMaps,nextIndex,vertIndex[2],vertIndex[0],edgeIndex,count,2,0);

					}


					//create a new version of the with room for the new vert and index data, copy in the current data
					//then set newMesh to our newly sized mesh

					SHADOWVERT *patchVertexData = NULL;
					DWORD *patchIndexData = NULL;

					ID3DXMesh *pPatchMesh = NULL;
			
					hr = D3DXCreateMesh( nextIndex / 3 + numMaps * 7,
						( inputMesh->GetNumFaces() + numMaps ) * 3,
						D3DXMESH_32BIT,
						SHADOWVERT::Decl,
						m_D3DDevice,
						&pPatchMesh );


					hr = pPatchMesh->LockVertexBuffer( 0, (LPVOID*)&patchVertexData );
					
					if( SUCCEEDED( hr ) )
						hr = pPatchMesh->LockIndexBuffer( 0, (LPVOID*)&patchIndexData );

					if( patchVertexData && patchIndexData )
					{
						ZeroMemory( patchVertexData, sizeof(SHADOWVERT) * ( inputMesh->GetNumFaces() + numMaps ) * 3 );
						ZeroMemory( patchIndexData, sizeof(DWORD) * ( nextIndex + 3 * numMaps * 7 ) );


						CopyMemory( patchVertexData, newVertexData, sizeof(SHADOWVERT) * inputMesh->GetNumFaces() * 3 );
						CopyMemory( patchIndexData, newIndexData, sizeof(DWORD) * nextIndex );
					} 
					
					else
					{
	
						pPatchMesh->Release();
					}

		
					newMesh->UnlockVertexBuffer();
					newMesh->UnlockIndexBuffer();
					newVertexData = patchVertexData;
					newIndexData = patchIndexData;
					newMesh->Release();
					newMesh = pPatchMesh;

					
					int nextVertex = inputMesh->GetNumFaces() * 3;
					
					for (int i  = 0; i < numMaps ; i++)
					{
						if(mapping[i].m_oldEdge[0] != -1 && mapping[i].m_oldEdge[1] != - 1)
						{
							if(mapping[i].m_newEdge[1][0] == -1 || mapping[i].m_newEdge[1][1] == -1)
							{
								for (int i2 = i + 1; i2 < numMaps; i2++)
								{
									if(mapping[i2].m_oldEdge[0] != -1 && mapping[i2].m_oldEdge[1] != -1 &&
										(mapping[i2].m_newEdge[1][0] == -1 || mapping[i2].m_newEdge[1][1] == -1))
									{
										int vertShared = 0;
										if( mapping[i2].m_oldEdge[0] == mapping[i].m_oldEdge[1] )
											vertShared++;
										if( mapping[i2].m_oldEdge[1] == mapping[i].m_oldEdge[0] )
											vertShared++;

										if(vertShared == 2)
										{
											mapping[i2].m_newEdge[1][0] = mapping[i].m_newEdge[0][0];
											mapping[i2].m_newEdge[1][1] = mapping[i].m_newEdge[0][1];
											break;
										}
										else if(vertShared == 1)
										{
											int before, after;
											if(mapping[i2].m_oldEdge[0] == mapping[i].m_oldEdge[1] )
											{
												before = i;
												after = i2;
											}
											else
											{
												before = i2;
												after = i;
											}
											
											newVertexData[nextVertex] = newVertexData[mapping[after].m_newEdge[0][1]];
											newVertexData[nextVertex+1] = newVertexData[mapping[before].m_newEdge[0][1]];
											newVertexData[nextVertex+2] = newVertexData[mapping[before].m_newEdge[0][0]];

											Vector3D v1 = newVertexData[nextVertex+1].Position - newVertexData[nextVertex].Position;
											Vector3D v2 = newVertexData[nextVertex+2].Position - newVertexData[nextVertex+1].Position;

											Vector3DNormalize(&v1,&v1);
											Vector3DNormalize(&v2,&v2);

											Vector3DCrossProduct(&newVertexData[nextVertex].Normal, &v1, &v2);

											newVertexData[nextVertex + 1].Normal = newVertexData[nextVertex + 2].Normal = newVertexData[nextVertex].Normal;

											newIndexData[nextIndex] = nextVertex;
											newIndexData[nextIndex+1] = nextVertex + 1;
											newIndexData[nextIndex+2] = nextVertex + 2;

											newIndexData[nextIndex + 3] = mapping[before].m_newEdge[0][1];
											newIndexData[nextIndex + 4] = mapping[before].m_newEdge[0][0];
											newIndexData[nextIndex + 5] = nextVertex + 1;

											newIndexData[nextIndex+6] = nextVertex + 2;
											newIndexData[nextIndex+7] = nextVertex + 1;
											newIndexData[nextIndex+8] = mapping[before].m_newEdge[0][0];

											// 2nd quad

											newIndexData[nextIndex+9] = mapping[after].m_newEdge[0][1];
											newIndexData[nextIndex+10] = mapping[after].m_newEdge[0][0];
											newIndexData[nextIndex+11] = nextVertex;

											newIndexData[nextIndex+12] = nextVertex + 1;
											newIndexData[nextIndex+13] = nextVertex;
											newIndexData[nextIndex+14] = mapping[after].m_newEdge[0][0];


											if(mapping[i2].m_oldEdge[0] == mapping[i].m_oldEdge[1])
											{
												mapping[i2].m_oldEdge[0] = mapping[i].m_oldEdge[0];
											}
											else
											{
												mapping[i2].m_oldEdge[1] = mapping[i].m_oldEdge[1];
											}
											mapping[i2].m_newEdge[0][0] = nextVertex + 2;
											mapping[i2].m_newEdge[0][1] = nextVertex;


											nextVertex += 3;
											nextIndex += 15;

											break;

										}
									}
								}
							}
							
							else
							{
								// First triangle
								newIndexData[nextIndex++] = mapping[i].m_newEdge[0][1];
								newIndexData[nextIndex++] = mapping[i].m_newEdge[0][0];
								newIndexData[nextIndex++] = mapping[i].m_newEdge[1][0];

								// Second triangle
								newIndexData[nextIndex++] = mapping[i].m_newEdge[1][1];
								newIndexData[nextIndex++] = mapping[i].m_newEdge[1][0];
								newIndexData[nextIndex++] = mapping[i].m_newEdge[0][0];
							}
						}
					}
				}
			
				if (newVertexData)
				{
					newMesh->UnlockVertexBuffer();
					newVertexData = NULL;
				}
				if (newIndexData)
				{
					newMesh->UnlockIndexBuffer();
					newIndexData = NULL;
				}
				if (hr == S_OK)
				{
					*OutPutMesh = newMesh;
				}
				else
					newMesh->Release();
			}
			delete[] mapping;
		} 
		else
			hr = E_OUTOFMEMORY;
	} 
	else
		hr = E_FAIL;

	if( vertexData )
		inputMesh->UnlockVertexBuffer();

	if( indexData )
		inputMesh->UnlockIndexBuffer();

	delete[] tempAdjVerts;
	inputMesh->Release();

	return hr;
}

IDirect3DVertexDeclaration9*
ShadowMesh::GetShadowDecl()
{
	return m_shadowDecl;
}
