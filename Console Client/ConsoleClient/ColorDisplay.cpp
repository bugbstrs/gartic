module ColorDisplay;

ColorDisplay::ColorDisplay(COORD upLeftCorner, ColorType color,
						   int16_t maxWidth, int16_t maxHeight, ConsoleManager *cm) :
	GUIObject { upLeftCorner, Align::Left, Align::Up, color, color, maxWidth, maxHeight, cm }
{}

ColorDisplay::ColorDisplay(int16_t x, int16_t y, ColorType color,
						   int16_t maxWidth, int16_t maxHeight, ConsoleManager * cm) :
	GUIObject { x, y, Align::Left, Align::Up, color, color, maxWidth, maxHeight, cm }
{}

ColorDisplay::ColorDisplay(ColorType color, int16_t maxWidth, int16_t maxHeight,
						   ConsoleManager * cm) :
	GUIObject { Align::Left, Align::Up, color, color, maxWidth, maxHeight, cm }
{}

void ColorDisplay::SetColor(ColorType color)
{
	m_backgroundColor = m_textColor = color;
}
