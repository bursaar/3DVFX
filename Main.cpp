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

// ACKNOWLEDGEMENTS
// Basic window construction code adapted from http://www.directxtutorial.com/Lesson.aspx?lessonid=9-1-3
// Method of input taken from http://www.rastertek.com/dx11tut13.html
// Code commented with LIT was taken from the Train2Game LIT series on how to make a game in C++


#include "RenderClass.h"
#include "SystemClass.h"


// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	SystemClass System;

	System.Initialise(hInstance, nCmdShow);

	// enter the main loop:
	System.Run();

	// Shutdown system object
	return System.Shutdown();
}

