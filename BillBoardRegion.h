#ifndef _BILLBOARDREGION_H_
#define _BILLBOARDREGION_H_


#ifndef _RENDEREVENT_H_
#include "RenderEvent.h"
#endif



/*
	Creates a region containing billboards all using the
	same texture.
	Billboards will be placed randomly within the AABB
	and rendered using single draw
*/

class BillBoardRegion : public RenderEvent
{
public:
	BillBoardRegion(const char* textureName, 
					const AABB &region, 
					int numBillboards, 
					Vector2D size,
					bool randomize = true);
	~BillBoardRegion(void);

	void Render();
private:
	
	Mesh* m_quadMesh;

	int m_texIndex;

};

#endif