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

InputField::InputField(Align align, ColorType backgroundColor, ColorType textColor,
					   int16_t maxWidth, int16_t maxHeight,
					   ColorType selectedBackgroungColor, ColorType selectedTextColor,
					   ConsoleManager *cm, InputManager *im,
					   SelectableObject *&selected, String &text):
	SelectableObject { align, backgroundColor, textColor, maxWidth, maxHeight		 ,
					   selectedBackgroungColor, selectedTextColor, cm, im, selected },
	m_text			 { text															}
{}

void InputField::Draw()
{
	SetColor();

	DrawBackground();

	DrawContents();
}

void InputField::CheckInput()
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
			if(m_upObject)
				m_selectedObject = m_upObject;
		break;
	case ControlKeys::DownArrow:
		if (m_textPos < m_width * (m_height - 1))
			m_textPos += m_width;
		else
			if (m_downObject)
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

void InputField::DrawContents()
{
	if (this == m_selectedObject)
	{
		COORD cursorPos{m_upLeftCorner};
		cursorPos.X += m_textPos % m_width;
		cursorPos.Y += m_textPos / m_width;
		m_cm->SetCursor(true, cursorPos);
	}

	int index{0};
	while (index < m_text.size())
	{
		m_cm->Write(m_text[index], m_upLeftCorner.X + index % m_width,
					m_upLeftCorner.Y + index / m_width);
		++index;
	}
}
