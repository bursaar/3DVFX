#ifndef _LINE_H_
#define _LINE_H_
#include "Types.h"

///////////////////////////////////////
//Line Class
//
// Helper class for renderating and rendering a line 
///////////////////////////////////////
class Line
{
public:
	/**
	 * Constructor
	 */
							Line(
								const Vector3D& from = Vector3D(0,0,0), 
								const Vector3D& to  = Vector3D(0,0,0), 
								DWORD fromColour = 0x00000000, 
								DWORD toColour = 0x00000000
								);
	/**
	 * Destructor
	 */
							~Line();
	/**
	 * Sets up the line data to render
	 */
	void					Setup(
								const Vector3D& from, 
								const Vector3D& to, 
								DWORD fromColour = 0x00000000, 
								DWORD toColour = 0x00000000
								);
	/**
	 * Renders the line
	 */
	void					Render();
	/**
	 * Updates the start & end point of the line
	 */
	void					SetPosition(
								const Vector3D& from, 
								const Vector3D& to
								);
private:
	void					CreateLine();

	Vector3D				m_pointA;
	Vector3D				m_pointB;
	DWORD					m_pointAColour;
	DWORD					m_pointBColour;

	IDirect3DVertexBuffer9*	m_vertexBuffer;
};

#endif
