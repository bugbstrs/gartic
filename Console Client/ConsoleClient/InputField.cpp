module InputField;

import <algorithm>;

InputField::InputField(COORD upLeftCorner, Align horizontalAlign, Align verticalAlign,
					   ColorType backgroundColor, ColorType textColor,
					   int16_t maxWidth, int16_t maxHeight,
					   ColorType selectedBackgroungColor, ColorType selectedTextColor,
					   ConsoleManager* cm, InputManager* im,
					   SelectableObject*& selected, String& text, int maxTextLength) :
	SelectableObject { upLeftCorner, horizontalAlign, verticalAlign, backgroundColor,
					   textColor, maxWidth, maxHeight, selectedBackgroungColor,
					   selectedTextColor, cm, im, selected							  },
	m_text			 { text															  }
{
	m_maxTextLength = maxTextLength == -1 ? maxWidth * maxHeight : maxTextLength;
}

InputField::InputField(int16_t x, int16_t y, Align horizontalAlign, Align verticalAlign,
					   ColorType backgroundColor, ColorType textColor,
					   int16_t maxWidth, int16_t maxHeight,
					   ColorType selectedBackgroungColor, ColorType selectedTextColor,
					   ConsoleManager* cm, InputManager* im,
					   SelectableObject*& selected, String& text, int maxTextLength) :
	SelectableObject { x, y, horizontalAlign, verticalAlign, backgroundColor, textColor,
					   maxWidth, maxHeight, selectedBackgroungColor, selectedTextColor,
					   cm, im, selected													},
	m_text			 { text																}
{
	m_maxTextLength = maxTextLength == -1 ? maxWidth * maxHeight : maxTextLength;
}

InputField::InputField(Align horizontalAlign, Align verticalAlign,
					   ColorType backgroundColor, ColorType textColor,
					   int16_t maxWidth, int16_t maxHeight,
					   ColorType selectedBackgroungColor, ColorType selectedTextColor,
					   ConsoleManager *cm, InputManager *im,
					   SelectableObject *&selected, String &text, int maxTextLength) :
	SelectableObject { horizontalAlign, verticalAlign, backgroundColor, textColor,
					   maxWidth, maxHeight, selectedBackgroungColor,
					   selectedTextColor, cm, im, selected						  },
	m_text			 { text														  }
{
	m_maxTextLength = maxTextLength == -1 ? maxWidth * maxHeight : maxTextLength;
}

void InputField::Draw()
{
	if (!m_active)
		return;

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
			if(m_upObject && m_upObject->IsSelectable())
				m_selectedObject = m_upObject;
		break;
	case ControlKeys::DownArrow:
		if (m_textPos < m_width * (m_height - 1))
			m_textPos += m_width;
		else
			if (m_downObject && m_downObject->IsSelectable())
				m_selectedObject = m_downObject;
		break;
	case ControlKeys::LeftArrow:
		if (m_textPos > 0)
			m_textPos--;
		break;
	case ControlKeys::RightArrow:
		if (m_textPos + 1 < m_maxTextLength && m_text.size() > m_textPos)
			m_textPos++;
		break;
	case ControlKeys::NotControl:
		if (m_im->GetCurrentKeyboardInput())
		{
			size_t len{ m_text.size() };
			m_im->UpdateString(m_text, m_textPos, m_maxTextLength);
			m_textPos += m_text.size() - len;

			m_textPos = std::max(m_textPos, 0);
			m_textPos = std::min(m_textPos, m_maxTextLength - 1);
		}
	default:
		break;
	}
	
	if (IsPointInside(m_im->GetCurrentCursorPosition()) &&
		m_im->GetClickPressed())
	{
		COORD cursorPos = m_im->GetCurrentCursorPosition();
		m_textPos = std::min((int)m_text.size(), cursorPos.X - m_upLeftCorner.X +
					(cursorPos.Y - m_upLeftCorner.Y) * m_width);
	}

}

void InputField::DrawContents()
{
	m_textPos = m_text.size() < m_textPos ? m_text.size() : m_textPos;

	if (this == m_selectedObject)
	{
		COORD cursorPos{m_upLeftCorner};
		cursorPos.X += m_textPos % m_width;
		cursorPos.Y += m_textPos / m_width;
		m_cm->SetCursor(true, cursorPos);
	}

	m_cm->Write(m_text, m_upLeftCorner.X, m_upLeftCorner.Y,
				m_width, m_height, m_horizontalAlign, m_verticalAlign);
}
