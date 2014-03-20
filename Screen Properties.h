// define the screen resolution
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)
#include <windows.h>

using namespace std;

// Need to put in an include guard here so the struct is defined multiple times.
#ifndef _CVERT
#define _CVERT

// global declarations
struct CUSTOMVERTEX
{
	FLOAT x, y, z;    // from the D3DFVF_XYZRHW flag
	DWORD color;    // from the D3DFVF_DIFFUSE flag
};

#endif