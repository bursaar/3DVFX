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
	FLOAT x, y, z;    // from the D3DFVF_XYZRHW flag
	DWORD colour;    // from the D3DFVF_DIFFUSE flag
	float tu, tv;	 // UV co-ordinates between 0 and 1 - This part of the struct was added from the original Train2Game LIT material.
	static const DWORD FORMAT = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;		// This line was taken from the vertex struct in the Train2Game LIT material.
	static const int STRIDE_SIZE = 24;

	// Reusing the constructor from the Train2Game LIT materials, without the UV co-ordinates.
	CUSTOMVERTEX(float px, float py, float pz, DWORD pcolour, float pu, float pv)
	{
		x = px;
		y = py;
		z = pz;
		colour = pcolour;
		tu = pu;
		tv = pv;
	}
};

class RenderClass
{
public:
	D3DClass *m_D3D;
	ID3DXMesh *m_characterMesh;
	ID3DXMesh *m_wallMesh;
	ID3DXMesh *m_floorMesh;
	D3DXMATRIX m_viewMatrix;
	MyCameraController* m_camera;

	IDirect3DVertexBuffer9 * CreateVertexBuffer(vector<CUSTOMVERTEX> vertices); // Lightly adapted from Train2Game LIT material
	float uvPan;

	// Overloaded constructors
	RenderClass();
	bool Initialise(HWND phWND);
	IDirect3DTexture9 * LoadTexture(LPCWSTR fileName);
	void cleanD3D(void);						// close Direct3D and release memo

	void BeginFrame();							// Implementation taken from LIT materials.
	void init_graphics(void);					// 3D declarations - drawing
	void CreateCharacter();
	void DrawMesh();
	void Draw(IDirect3DVertexBuffer9 * vertexBuffer, IDirect3DTexture9 * texture, D3DXVECTOR3 &position, D3DXVECTOR3 &scale, D3DXVECTOR3 &rotation, const D3DXMATRIXA16 & baseMatrix, int verticeCount, IDirect3DIndexBuffer9 * indexbuff, int primCount);
	~RenderClass();

private:
	void initD3D(HWND &pHWND);					// sets up and initializes Direct3D

	// These maps used as cache and tally are taken from the LIT material.
	map<wstring, IDirect3DTexture9*> textureCache;
	map<wstring, int> textureUsageCount;

	// Mesh operations
	LPD3DXBUFFER *m_adjacencyBuffer;
	LPD3DXBUFFER *m_vRemap;
	DWORD *m_adaj;
	DWORD *m_optAdaj;
	DWORD *m_fRemap;
};

