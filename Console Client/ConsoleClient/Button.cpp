module Button;

Button::Button(COORD upLeftCorner, Align align, ColorType backgroundColor, ColorType textColor,
			   int16_t maxWidth, int16_t maxHeight, ColorType selectedBackgroungColor,
			   ColorType selectedTextColor, ConsoleManager *cm, InputManager *im,
			   SelectableObject *&selected, String text) :
	SelectableObject { upLeftCorner, align, backgroundColor, textColor, maxWidth, maxHeight  ,
					   selectedBackgroungColor, selectedTextColor, cm, im, selected		    },
	m_text			 { text																	}
{}

Button::Button(int16_t x, int16_t y, Align align, ColorType backgroundColor, ColorType textColor,
			   int16_t maxWidth, int16_t maxHeight, ColorType selectedBackgroungColor,
			   ColorType selectedTextColor, ConsoleManager *cm, InputManager *im,
			   SelectableObject *&selected, String text):
	SelectableObject { x, y, align, backgroundColor, textColor, maxWidth, maxHeight  ,
					   selectedBackgroungColor, selectedTextColor, cm, im, selected },
	m_text			 { text															}
{}

Button::Button(Align align, ColorType backgroundColor, ColorType textColor,
			   int16_t maxWidth, int16_t maxHeight, ColorType selectedBackgroungColor,
			   ColorType selectedTextColor, ConsoleManager *cm, InputManager *im,
			   SelectableObject *&selected, String text):
	SelectableObject { align, backgroundColor, textColor, maxWidth, maxHeight		 ,
					   selectedBackgroungColor, selectedTextColor, cm, im, selected },
	m_text			 { text															}
{}

void Button::Draw()
{
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
				if (m_upObject)
					m_selectedObject = m_upObject;
				break;
			case ControlKeys::DownArrow:
				if (m_downObject)
					m_selectedObject = m_downObject;
				break;
			case ControlKeys::LeftArrow:
				if (m_leftObject)
					m_selectedObject = m_leftObject;
				break;
			case ControlKeys::RightArrow:
				if (m_rightObject)
					m_selectedObject = m_rightObject;
				break;
			default:
				break;
		}
	}
}

void Button::DrawContents()
{
	int index{0};
	while (index < m_text.size())
	{
		m_cm->Write(m_text[index], m_upLeftCorner.X + index % m_width,
					m_upLeftCorner.Y + index / m_width);
		++index;
	}
}
