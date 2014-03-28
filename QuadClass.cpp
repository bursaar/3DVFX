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
	vertices.push_back(CUSTOMVERTEX(-1.0f,  1.0f, 0.0f, 0xffffffff, 0.0f, 0.0f));
	vertices.push_back(CUSTOMVERTEX( 1.0f,  1.0f, 0.0f, 0xffffffff, 1.0f, 0.0f));
	vertices.push_back(CUSTOMVERTEX(-1.0f, -1.0f, 0.0f, 0xffffffff, 0.0f, 1.0f));
	vertices.push_back(CUSTOMVERTEX( 1.0f, -1.0f, 0.0f, 0xffffffff, 1.0f, 1.0f));

	mRenderThis = true;
}