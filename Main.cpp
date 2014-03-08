// ================================================================================================ //
//																									//
//						Level 7 3D Graphics for Computer Games (4241-504)							//
//																									//
//											 3DVFX													//
//											   by													//
//									       Ben Keenan												//
//																									//
//									  Student No. CD900002O											//
//																									//
//								   ben@ben.ie | +353 87 935 0483									//
//																									//
// ================================================================================================	//

// Basic window construction code taken from http://www.directxtutorial.com/Lesson.aspx?lessonid=9-1-3
// Method of input taken from http://www.rastertek.com/dx11tut13.html


#include "RenderClass.h"
#include "MyWindows.h"
#include "SystemClass.h"

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	SystemClass System(hInstance, nCmdShow);

	System.Run();
}