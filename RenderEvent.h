#ifndef _RENDEREVENT_H_
#define _RENDEREVENT_H_

class RenderEvent
{
public:
	enum RenderFlag
	{
		NoEffects	= 0x00000001,
		Skinned		= 0x00000001 << 1,
		NormalMap	= 0x00000001 << 2,
		ShadowVolume = 0x00000001 << 3,
		AmibentEnviroment = 0x00000001 << 4,
		BillboardEffect =  0x00000001 << 5,
		ShadowMapRender = 0x00000001 << 6,
		AmibentEnviromentShadow = 0x00000001 << 7,
	};

	RenderEvent() { m_flags = 0; m_firstChild = 0; m_nextSibling = 0; }

	virtual void	Render() = 0;

	bool			GetFlag(RenderFlag flag) { return (m_flags & flag) != 0 ; }

protected:
	unsigned int	m_flags;

private:
	friend class RenderManager;

	RenderEvent*	m_firstChild;
	RenderEvent*	m_nextSibling;
};

#endif //_RENDEREVENT_H_
