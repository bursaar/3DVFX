#pragma once
#include "D3DClass.h"
#include "Screen Properties.h"
#include "MyCameraController.h"
#include "CharacterClass.h"
#include <vector>

using namespace std;

// include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

// global declarations
struct CUSTOMVERTEX
{
	FLOAT x, y, z;    // from the D3DFVF_XYZRHW flag
	DWORD color;    // from the D3DFVF_DIFFUSE flag
};

class RenderClass
{
public:
	D3DClass *m_D3D;
	ID3DXMesh *m_characterMesh;
	ID3DXMesh *m_wallMesh;
	ID3DXMesh *m_floorMesh;
	D3DXMATRIX m_viewMatrix;
	CharacterClass *m_player;
	MyCameraController* m_camera;

	// Overloaded constructors
	RenderClass();
	bool Initialise(HWND phWND);

	void cleanD3D(void);						// close Direct3D and release memo

	void init_graphics(void);					// 3D declarations - drawing
	void CreateCharacter();
	void DrawMesh();

	~RenderClass();

private:
	void initD3D(HWND &pHWND);					// sets up and initializes Direct3D


	// Mesh operations
	LPD3DXBUFFER *m_adjacencyBuffer;
	LPD3DXBUFFER *m_vRemap;
	DWORD *m_adaj;
	DWORD *m_optAdaj;
	DWORD *m_fRemap;
};

