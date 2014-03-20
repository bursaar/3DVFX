#include "Types.h"
#include <tchar.h>
#include "Text.h"

/************************************************************************/

Text::Text(const char* fontName, int fontSize, bool bold, bool italics)
{
	CreateDirectXFont(fontName,fontSize,bold,italics);
}

/************************************************************************/

Text::~Text()
{
	m_font->Release();
}

/************************************************************************/

void
Text::CreateDirectXFont(const char *fontName, int fontSize, bool bold, bool italics)
{
	m_foneName = fontName;
	m_fontSize = fontSize;
	m_italics = italics;

	D3DXFONT_DESC fontDesc;
	fontDesc.Height = m_fontSize;
	fontDesc.Width = 0;
	fontDesc.Weight = 0;
	fontDesc.MipLevels = 1;
	fontDesc.Italic = m_italics;
	fontDesc.CharSet = DEFAULT_CHARSET;
	fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
	fontDesc.Quality = DEFAULT_QUALITY;
	fontDesc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	_tcscpy_s(fontDesc.FaceName, m_foneName);

	if(FAILED(D3DXCreateFontIndirect(m_D3DDevice,&fontDesc,&m_font)))
	{
		ErrorMessage("Font Failed in Stats");
	}
}

/************************************************************************/

void
Text::PrintText(const Vector2D& position, const char* text, D3DCOLOR textColour)
{
	RECT positionRect;
	
	positionRect.left = (LONG)position.x;
	positionRect.top = (LONG)position.y;
	positionRect.bottom = (LONG)0;
	positionRect.right = (LONG)0;
	
	m_font->DrawText(0,text,-1, &positionRect, DT_NOCLIP, textColour);
}

/************************************************************************/

