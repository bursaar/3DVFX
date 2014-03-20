#include "Types.h"
#include "Stats.h"
#include <tchar.h>

Stats::Stats() : m_font(0),m_FPS(0.0f)
{
	D3DXFONT_DESC fontDesc;
	fontDesc.Height = 18;
	fontDesc.Width = 0;
	fontDesc.Weight = 0;
	fontDesc.MipLevels = 1;
	fontDesc.Italic = false;
	fontDesc.CharSet = DEFAULT_CHARSET;
	fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
	fontDesc.Quality = DEFAULT_QUALITY;
	fontDesc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	_tcscpy_s(fontDesc.FaceName, _T("Times New Roman"));

	if(FAILED(D3DXCreateFontIndirect(m_D3DDevice,&fontDesc,&m_font)))
	{
		ErrorMessage("Font Failed in Stats");
	}
}

Stats::~Stats()
{
	m_font->Release();
}

void
Stats::Update(float elapsedTime)
{
	static float numFrames = 0.0f;
	static float timeElapsed = 0.f;
	
	numFrames += 1.0f;
	timeElapsed += elapsedTime;

	if(timeElapsed >= 1.f)
	{
		m_FPS = numFrames;
		numFrames = 0.0f;
		timeElapsed = 0.f;
	}
}

void
Stats::Render()
{
	MyString buffer;

	buffer.Format("frames per second: %.0f",m_FPS);

	RECT r = {5,90,0,0};

	m_font->DrawText(0,buffer,-1,&r,DT_NOCLIP,D3DCOLOR_XRGB(0,0,255));
}


