#ifndef _Text_H_
#define _Text_H_

//////////////////////////////////////////////////////////////////////////
//Text
//
//The Text Printer is a class that allows the user to create an object
//that can create and print text to screen, fonts can be set to any size,
//position and colour. 
//////////////////////////////////////////////////////////////////////////

class Text
{
public:
	/**
	 * Constructor
	 */
							Text(
								const char* fontName = "Arial", ///< The font type face to use
								int fontSize = 18, ///< The font size
								bool bold = false, ///< Use a bold folt
								bool italics = false ///< Use italic font
								);
	/**
	 * Destructor
	 */
							~Text();
	/**
	 * Prints the string using the specified position and colour
	 */
	void					PrintText(
								const Vector2D& position, ///< The position to print the text at
								const char* text, ///< The text to print
								D3DCOLOR textColour = D3DCOLOR_ARGB(255, 255, 255,255) ///< The colour to render the text 
								);
private:
	/**
	 * Create the Direct X Font object
	 */
	void					CreateDirectXFont(
								const char* fontName, 
								int fontSize, 
								bool bold, 
								bool italics
								);

	MyString m_foneName;
	int m_fontSize;
	bool m_bold;
	bool m_italics;
	ID3DXFont* m_font;
};


#endif //_Text_H_