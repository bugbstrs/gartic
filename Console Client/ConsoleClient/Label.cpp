module Label;

Label::Label(COORD upLeftCorner, Align align, ColorType backgroundColor, ColorType textColor,
			 int16_t maxWidth, int16_t maxHeight, String text) :
	GUIObject { upLeftCorner, align, backgroundColor, textColor, maxWidth, maxHeight },
	m_text	  { text																 }
{}

Label::Label(int16_t x, int16_t y, Align align, ColorType backgroundColor, ColorType textColor,
			 int16_t maxWidth, int16_t maxHeight, String text) :
	GUIObject { x, y, align, backgroundColor, textColor, maxWidth, maxHeight },
	m_text	  { text														 }
{}

void Label::Draw(ConsoleManager* cm)
{
	cm->SetColor(m_backgroundColor, m_textColor);

	int index{ 0 };
	while (index < m_text.size())
	{
		cm->Write(m_text[index], m_upLeftCorner.X + index % m_width, m_upLeftCorner.Y + index / m_width);
		++index;
	}
}
