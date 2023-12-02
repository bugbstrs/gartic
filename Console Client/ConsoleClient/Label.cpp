module Label;

Label::Label(COORD upLeftCorner, Align align, ColorType backgroundColor, ColorType textColor,
			 int16_t maxWidth, int16_t maxHeight, ConsoleManager* cm, String text) :
	GUIObject { upLeftCorner, align, backgroundColor, textColor, maxWidth, maxHeight, cm },
	m_text	  { text																	 }
{}

Label::Label(int16_t x, int16_t y, Align align, ColorType backgroundColor, ColorType textColor,
			 int16_t maxWidth, int16_t maxHeight, ConsoleManager* cm, String text) :
	GUIObject { x, y, align, backgroundColor, textColor, maxWidth, maxHeight, cm },
	m_text	  { text															 }
{}

Label::Label(Align align, ColorType backgroundColor, ColorType textColor, int16_t maxWidth,
			 int16_t maxHeight, ConsoleManager *cm, String text):
	GUIObject { align, backgroundColor, textColor, maxWidth, maxHeight, cm },
	m_text	  { text													   }
{}

void Label::Draw()
{
	SetColor();

	DrawBackground();

	DrawContents();
}

void Label::DrawContents()
{
	int index{0};
	while (index < m_text.size() && index < m_width * m_height)
	{
		m_cm->Write(m_text[index], m_upLeftCorner.X + index % m_width,
								   m_upLeftCorner.Y + index / m_width);
		++index;
	}
}
