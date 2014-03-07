#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "Screen Properties.h"

// global declarations
LPDIRECT3D9 d3d;							// the pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;					// the pointer to the device class
LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;    // the pointer to the vertex buffer

// include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

struct CUSTOMVERTEX
{
	FLOAT x, y, z;    // from the D3DFVF_XYZRHW flag
	DWORD color;    // from the D3DFVF_DIFFUSE flag
};

// Function prototypes
void init_graphics(void);    // 3D declarations
void render_frame(void);    // renders a single frame
void initD3D(HWND hWnd);    // sets up and initializes Direct3D
void cleanD3D(void);		// closes Direct3D and releases memory