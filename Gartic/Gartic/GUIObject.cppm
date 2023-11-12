export module GUIObject;

import <Windows.h>;

export import ColorType;
export import Align;

export typedef unsigned short uint16_t;
export typedef short int16_t;

export class GUIObject
{
public:
	virtual void Draw() = 0;
	GUIObject(COORD upLeftCorner, Align align, ColorType backgroundColor, ColorType textColor, uint16_t width);
	GUIObject(int16_t x, int16_t y, Align align, ColorType backgroundColor, ColorType textColor, uint16_t width);
	virtual ~GUIObject();
protected:
	COORD m_upLeftCorner;
	uint16_t m_width;
	Align m_align;
	ColorType m_backgroundColor;
	ColorType m_textColor;
};