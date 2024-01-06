module Button;

Button::Button(COORD upLeftCorner, Align horizontalAlign, Align verticalAlign,
			   ColorType backgroundColor, ColorType textColor,
			   int16_t maxWidth, int16_t maxHeight,
			   ColorType selectedBackgroungColor, ColorType selectedTextColor,
			   ConsoleManager *cm, InputManager *im,
			   SelectableObject *&selected, String text) :
	SelectableObject { upLeftCorner, horizontalAlign, verticalAlign,
					   backgroundColor, textColor, maxWidth,
					   maxHeight, selectedBackgroungColor, selectedTextColor,
					   cm, im, selected										 },
	m_text			 { text													 }
{}

Button::Button(int16_t x, int16_t y, Align horizontalAlign, Align verticalAlign,
			   ColorType backgroundColor, ColorType textColor,
			   int16_t maxWidth, int16_t maxHeight,
			   ColorType selectedBackgroungColor, ColorType selectedTextColor,
			   ConsoleManager *cm, InputManager *im,
			   SelectableObject *&selected, String text):
	SelectableObject { x, y, horizontalAlign, verticalAlign, backgroundColor,
					   textColor, maxWidth, maxHeight, selectedBackgroungColor,
					   selectedTextColor, cm, im, selected					   },
	m_text			 { text													   }
{}

Button::Button(Align horizontalAlign, Align verticalAlign,
			   ColorType backgroundColor, ColorType textColor,
			   int16_t maxWidth, int16_t maxHeight,
			   ColorType selectedBackgroungColor, ColorType selectedTextColor,
			   ConsoleManager *cm, InputManager *im,
			   SelectableObject *&selected, String text):
	SelectableObject { horizontalAlign, verticalAlign, backgroundColor,
					   textColor, maxWidth, maxHeight, selectedBackgroungColor,
					   selectedTextColor, cm, im, selected					   },
	m_text			 { text													   }
{}

void Button::Draw()
{
	if (!m_active)
		return;

	SetColor();

	DrawBackground();
	
	DrawContents();
}

void Button::CheckInput()
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
				if (m_upObject && m_upObject->IsSelectable())
					m_selectedObject = m_upObject;
				break;
			case ControlKeys::DownArrow:
				if (m_downObject && m_downObject->IsSelectable())
					m_selectedObject = m_downObject;
				break;
			case ControlKeys::LeftArrow:
				if (m_leftObject && m_leftObject->IsSelectable())
					m_selectedObject = m_leftObject;
				break;
			case ControlKeys::RightArrow:
				if (m_rightObject && m_rightObject->IsSelectable())
					m_selectedObject = m_rightObject;
				break;
			default:
				break;
		}
	}
}

void Button::DrawContents()
{
	m_cm->Write(m_text, m_upLeftCorner.X, m_upLeftCorner.Y,
		m_width, m_height, m_horizontalAlign, m_verticalAlign);
}
