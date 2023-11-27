module InputField;

InputField::InputField(COORD upLeftCorner, Align align, ColorType backgroundColor,
					   ColorType textColor, int16_t maxWidth, int16_t maxHeight,
					   ColorType selectedBackgroungColor, ColorType selectedTextColor,
					   ConsoleManager* cm, InputManager* im,
					   SelectableObject*& selected, String& text) :
	SelectableObject { upLeftCorner, align, backgroundColor, textColor, maxWidth  ,
					   maxHeight, selectedBackgroungColor, selectedTextColor	  ,
					   cm, im, selected											 },
	m_text			 { text														 }
{}

InputField::InputField(int16_t x, int16_t y, Align align, ColorType backgroundColor,
					   ColorType textColor, int16_t maxWidth, int16_t maxHeight,
					   ColorType selectedBackgroungColor, ColorType selectedTextColor,
					   ConsoleManager* cm, InputManager* im,
					   SelectableObject*& selected, String& text) :
	SelectableObject { x, y, align, backgroundColor, textColor, maxWidth, maxHeight  ,
					   selectedBackgroungColor, selectedTextColor, cm, im, selected	},
	m_text			 { text															}
{}

void InputField::Draw()
{
	if (this == m_selectedObject)
	{
		m_cm->SetColor(m_selectedBackgroundColor, m_selectedTextColor);

		COORD cursorPos = m_upLeftCorner;
		cursorPos.X    += m_textPos % m_width;
		cursorPos.Y    += m_textPos / m_width;
		m_cm->SetCursor(true, cursorPos);
	}else
	{
		if (IsPointInside(m_im->GetCurrentCursorPosition()))
			m_cm->SetColor(m_hoverBackgroundColor, m_hoverTextColor);
		else
			m_cm->SetColor(m_backgroundColor, m_textColor);
	}

	int index{ 0 };
	while (index < m_text.size())
	{
		m_cm->Write(m_text[index], m_upLeftCorner.X + index % m_width,
								   m_upLeftCorner.Y + index / m_width);
		++index;
	}
}

void InputField::CheckInput()
{
	if (this == m_selectedObject)
	{
		switch (m_im->ControlKey())
		{
		case ControlKeys::Enter:
			if (m_function)
				m_function();
			break;
		case ControlKeys::UpArrow:
			if (m_textPos / m_width > 0)
				m_textPos -= m_width;
			else
				m_selectedObject = m_upObject;
			break;
		case ControlKeys::DownArrow:
			if (m_textPos < m_width * (m_height - 1))
				m_textPos += m_width;
			else
				m_selectedObject = m_downObject;
			break;
		case ControlKeys::LeftArrow:
			if (m_textPos > 0)
				m_textPos--;
			break;
		case ControlKeys::RightArrow:
			if (m_textPos + 1 < m_width * m_height)
				m_textPos++;
			break;
		default:
			break;
		}
	}
	if (IsPointInside(m_im->GetCurrentCursorPosition()) &&
		m_im->GetClickPressed())
	{
		m_selectedObject = this;
		if (m_function)
			m_function();
	}
}
