#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Control\inputclass.h"
#include "Screen Properties.h"

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
	LPDIRECT3D9 d3d;							// the pointer to our Direct3D interface
	LPDIRECT3DDEVICE9 d3ddev;					// the pointer to the device class
	LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;    // the pointer to the vertex buffer
	LPDIRECT3DINDEXBUFFER9 i_buffer = NULL;		// the pointer to the index buffer

	// Overloaded constructors
	RenderClass();
	RenderClass(HWND hWnd);

	// Public member functions to:
	void render_frame(InputClass pInput);		// render a single frame
	void cleanD3D(void);						// close Direct3D and release memory
	void init_graphics(void);					// 3D declarations - drawing

	~RenderClass();

private:
	void initD3D(HWND hWnd);					// sets up and initializes Direct3D
};

