#ifndef _RENDERMANAGER_H_
#define _RENDERMANAGER_H_

#ifndef _RENDEREVENT_H_
#include "RenderEvent.h"
#endif

class RenderManager : public Singleton<RenderManager>
{
public:
	RenderManager(void);
	~RenderManager(void);

	void AddEvent(RenderEvent* event, RenderEvent* parent);

	void RemoveEvent(RenderEvent* e);

	void Render();

	void RenderEnvironment();

	const RenderEvent::RenderFlag CurrentRenderFlag();


private:
	void RemoveEvent(RenderEvent* e, RenderEvent* searchPosition);
	void RecursiveRender(RenderEvent* e, RenderEvent::RenderFlag renderFlag);

	RenderEvent*	m_firstEvent;
	RenderEvent::RenderFlag m_current;
};

#endif //_RENDERMANAGER_H_