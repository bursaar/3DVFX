#include "QuadClass.h"


QuadClass::QuadClass()
{
}


QuadClass::~QuadClass()
{
}

void QuadClass::Initialise(RenderClass * pRenderClass)
{
	// Creating a quad by pushing the vertices to the draw stack.
	vertices.push_back(CUSTOMVERTEX(-1.0f,  1.0f, 0.0f, 0xffff00ff, 0.0f, 0.0f));
	vertices.push_back(CUSTOMVERTEX( 1.0f,  1.0f, 0.0f, 0xffffff00, 1.0f, 0.0f));
	vertices.push_back(CUSTOMVERTEX(-1.0f, -1.0f, 0.0f, 0xff00ffff, 0.0f, 1.0f));
	vertices.push_back(CUSTOMVERTEX( 1.0f, -1.0f, 0.0f, 0xfffff00f, 1.0f, 1.0f));

	mRenderThis = true;
}