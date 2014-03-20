#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "AABB.h"

//////////////////////////////////////////////////////////////////////////
//Vertex.
//
//This file, as well as the .cpp file contains all the custom vertex declaration
//required within the program, each structure can store a range of information including
//a vertex's position, colour, normal and texture co-ordinate for example.
//
//When a vertex buffer or model is created, each vertex will be assigned to one of these structures.
//that information will be used to position the vertex on screen for rendering, compute lighting
//and texture the object, vertex information can also be passed into a vertex shader for use as well.
//
//////////////////////////////////////////////////////////////////////////

//There are two functions, one to assign the declarations to memory
//and the other to remove it.
void InitAllVertexDeclarations();
void DestroyAllVertexDeclarations();

//////////////////////////////////////////////////////////////////////////
//VertexPosition
//
//Stores only the position of a vertex
//////////////////////////////////////////////////////////////////////////
struct VertexPosition
{
	VertexPosition():pos(0.0f,0.0f,0.0f){}
	VertexPosition(float x,float y,float z):pos(x,y,z){}
	VertexPosition(const Vector3D& v):pos(v){}

	Vector3D pos;
	//IDirect3DVertexDeclaration9 is used to add the vertex to the device memory.
	static IDirect3DVertexDeclaration9* Decl;

};

//////////////////////////////////////////////////////////////////////////
//VertexColour
//
//Stores the position of the vertex and a colour for the vertex to be.
//////////////////////////////////////////////////////////////////////////
struct VertexColour
{
	VertexColour():pos(0,0,0),colour(0x00000000){};
	VertexColour(float x, float y, float z , DWORD col): pos(x,y,z), colour(col){};
	VertexColour(Vector3D position,DWORD col): pos(position), colour(col){};

	Vector3D pos;
	DWORD colour;

	static IDirect3DVertexDeclaration9* Decl;
};

//////////////////////////////////////////////////////////////////////////
//VertexPositionTexCoord
//
//Stores the position of the vertex and a Texture co-ordinate
//////////////////////////////////////////////////////////////////////////
struct VertexPositionTexCoord
{	
	VertexPositionTexCoord():pos(0,0,0),textureCoord(0,0){}
	VertexPositionTexCoord(float x, float y, float z , float u, float v): pos(x,y,z), textureCoord(u,v){};
	VertexPositionTexCoord(Vector3D position,Vector2D UV): pos(position), textureCoord(UV){};

	Vector3D pos;
	Vector2D textureCoord;

	static IDirect3DVertexDeclaration9* Decl;
};

//////////////////////////////////////////////////////////////////////////
//VertexPositionNormalColour
//
//Stores the position of the vertex, the normal of the vertex and a colour
//////////////////////////////////////////////////////////////////////////
struct VertexPositionNormalColour
{

	VertexPositionNormalColour():pos(0,0,0), normal(0,0,0),colour(0x00000000){};
	VertexPositionNormalColour(float x, float y, float z,float nx,float ny,float nz,DWORD col)
		:pos(x,y,z),normal(nx,ny,nz), colour(col){};
	VertexPositionNormalColour(Vector3D position, Vector3D norm, DWORD col)
		:pos(position),normal(norm), colour(col){};

	Vector3D pos;
	Vector3D normal;
	DWORD colour;

	static IDirect3DVertexDeclaration9* Decl;
};

//////////////////////////////////////////////////////////////////////////
//VertexPositionNormalColour
//
//Stores the position of the vertex, the normal of the vertex and a Texture Co-ordinate
//////////////////////////////////////////////////////////////////////////
struct VertexPositionNormalTexCoord 
{

	VertexPositionNormalTexCoord()
		:pos(0,0,0), normal(0,0,0), textureCoord(0,0){}
	VertexPositionNormalTexCoord(float x,float y,float z, float nx, float ny, float nz, float u, float v)
		:pos(x,y,z),normal(nx,ny,nz),textureCoord(u,v){};
	VertexPositionNormalTexCoord(Vector3D position, Vector3D norm, Vector2D UV)
		:pos(position),normal(norm),textureCoord(UV){};

	Vector3D pos;
	Vector3D normal;
	Vector2D textureCoord;

	static IDirect3DVertexDeclaration9* Decl;
};

struct BillBoardVertex
{
	BillBoardVertex() :pos(0.0f, 0.0f, 0.0f),
		TexCoord(0.0f, 0.0f){}

	BillBoardVertex(const Vector3D& v, 
		const Vector2D& uv) :pos(v),
		TexCoord(uv),quadPosition(0,0,0){}

	Vector3D pos;
	Vector3D quadPosition;
	Vector2D TexCoord;

	static IDirect3DVertexDeclaration9* Decl;
};

#endif
