module InputField;

InputField::InputField(COORD upLeftCorner, Align align, ColorType backgroundColor,
					   ColorType textColor, int16_t maxWidth, int16_t maxHeight,
					   ColorType selectedBackgroungColor, ColorType selectedTextColor,
					   SelectableObject*& selected, String& text) :
	SelectableObject { upLeftCorner, align, backgroundColor, textColor, maxWidth  ,
					   maxHeight, selectedBackgroungColor, selectedTextColor	  ,
					   selected													 },
	m_text			 { text														 }
{}

InputField::InputField(int16_t x, int16_t y, Align align, ColorType backgroundColor,
					   ColorType textColor, int16_t maxWidth, int16_t maxHeight,
					   ColorType selectedBackgroungColor, ColorType selectedTextColor,
					   SelectableObject*& selected, String& text) :
	SelectableObject { x, y, align, backgroundColor, textColor, maxWidth, maxHeight  ,
					   selectedBackgroungColor, selectedTextColor, selected		    },
	m_text			 { text															}
{}

void InputField::Draw(ConsoleManager* cm)
{
	if (this == m_selectedObject)
		cm->SetColor(m_selectedBackgroundColor, m_selectedTextColor);
	else
		cm->SetColor(m_backgroundColor, m_textColor);

	int index{ 0 };
	while (index < m_text.size())
	{
		cm->Write(m_text[index], m_upLeftCorner.X + index % m_width, m_upLeftCorner.Y + index / m_width);
		++index;
	}
}
