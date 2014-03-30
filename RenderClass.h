#pragma once
#include "D3DClass.h"
#include "Screen Properties.h"
#include "MyCameraController.h"
#include <vector>
#include <map>

using namespace std;

// include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

// global declarations
struct CUSTOMVERTEX
{
	FLOAT x, y, z;		// from the D3DFVF_XYZRHW flag
	DWORD colour;		// from the D3DFVF_DIFFUSE flag
	float tu, tv;		// UV co-ordinates between 0 and 1 - This part of the struct was added from the original Train2Game LIT material.
	static const DWORD FORMAT = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;		// This line was taken from the vertex struct in the Train2Game LIT material.
	D3DXVECTOR3 normal;
	static const int STRIDE_SIZE = 36;


	// Reusing the constructor from the Train2Game LIT materials.
	CUSTOMVERTEX(float px, float py, float pz, DWORD pcolour, float pu, float pv)
	{
		x = px;
		y = py;
		z = pz;
		colour = pcolour;
		tu = pu;
		tv = pv;
	}

	// Adding a default constructor for the manual sphere creation
	CUSTOMVERTEX()
		:x(0.0f), y(0.0f), z(0.0f), colour(0xffffffff), tu(0.0f), tv(0.0f)
	{}
};

class RenderClass
{
public:
	LPDIRECT3D9 d3d;							// our Direct3D interface
	LPDIRECT3DDEVICE9 d3ddev;					// the device class
	LPDIRECT3DVERTEXBUFFER9 v_buffer;			// the vertex buffer
	LPDIRECT3DINDEXBUFFER9 i_buffer;			// the index buffer
	D3DPRESENT_PARAMETERS d3dpp;				// The present parameters

	float fieldOfView;
	float screenAspect;
	float nearView;
	float farView;

	D3DXMATRIX m_viewMatrix;
	MyCameraController* GetCameraController();

	IDirect3DVertexBuffer9 * CreateVertexBuffer(vector<CUSTOMVERTEX> vertices); // Lightly adapted from Train2Game LIT material
	float uvPan;

	// Overloaded constructors
	RenderClass();
	bool Initialise(HWND phWND);
	IDirect3DTexture9 * LoadTexture(LPCWSTR fileName);
	
	bool EndFrame();							// Taken from LIT materials
	bool Reset();								// Taken from LIT materials

	void BeginFrame();							// Implementation taken from LIT materials.
	void Draw(IDirect3DVertexBuffer9 * vertexBuffer, IDirect3DTexture9 * texture, D3DXVECTOR3 &position, D3DXVECTOR3 &scale, D3DXVECTOR3 &rotation, const D3DXMATRIXA16 & baseMatrix, int verticeCount, IDirect3DIndexBuffer9 * indexbuff, int primCount);
	~RenderClass();

private:
	MyCameraController* m_camera;
	void initD3D(HWND &pHWND);					// sets up and initializes Direct3D

	// These maps used as cache and tally are taken from the LIT material.
	map<wstring, IDirect3DTexture9*> textureCache;
	map<wstring, int> textureUsageCount;
	//Vertex dec
	LPDIRECT3DVERTEXDECLARATION9 vertexDecl;

	// Mesh operations
	LPD3DXBUFFER *m_adjacencyBuffer;
	LPD3DXBUFFER *m_vRemap;
	DWORD *m_adaj;
	DWORD *m_optAdaj;
	DWORD *m_fRemap;
};

