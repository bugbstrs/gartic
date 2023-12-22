module Label;

Label::Label(COORD upLeftCorner, Align horizontalAlign, Align verticalAlign,
			 ColorType backgroundColor, ColorType textColor,
			 int16_t maxWidth, int16_t maxHeight,
			 ConsoleManager* cm, String text) :
	GUIObject { upLeftCorner, horizontalAlign, verticalAlign,
				backgroundColor, textColor, maxWidth, maxHeight, cm },
	m_text	  { text												}
{}

Label::Label(int16_t x, int16_t y, Align horizontalAlign, Align verticalAlign,
			 ColorType backgroundColor, ColorType textColor,
			 int16_t maxWidth, int16_t maxHeight,
			 ConsoleManager* cm, String text) :
	GUIObject { x, y, horizontalAlign, verticalAlign,
				backgroundColor, textColor, maxWidth, maxHeight, cm },
	m_text	  { text												}
{}

Label::Label(Align horizontalAlign, Align verticalAlign,
			 ColorType backgroundColor, ColorType textColor,
			 int16_t maxWidth, int16_t maxHeight,
			 ConsoleManager *cm, String text):
	GUIObject { horizontalAlign, verticalAlign,
				backgroundColor, textColor, maxWidth, maxHeight, cm },
	m_text	  { text												}
{}

void Label::UpdateText(const String &text)
{
	m_text = text;
}

void Label::Draw()
{
	if (!m_active)
		return;

	SetColor();

	DrawBackground();

	DrawContents();
}

void Label::DrawContents()
{
	m_cm->Write(m_text, m_upLeftCorner.X, m_upLeftCorner.Y,
				m_width, m_height, m_horizontalAlign, m_verticalAlign);
}
