module CheckBox;

CheckBox::CheckBox(COORD upLeftCorner,
			       ColorType backgroundColor, ColorType checkColor,
			       ColorType selectedColor, int16_t maxWidth, int16_t maxHeight,
			       ConsoleManager *cm, InputManager *im, SelectableObject *&selected) :
	SelectableObject { upLeftCorner, Align::Center, Align::Center,
					   backgroundColor, backgroundColor, maxWidth, maxHeight,
					   selectedColor, selectedColor, cm, im, selected		 },
	m_checkColor	 { checkColor											 },
	m_checked		 { false												 }
{
	m_function = [this]() {m_checked = !m_checked; };
}

CheckBox::CheckBox(int16_t x, int16_t y,
				   ColorType backgroundColor, ColorType checkColor,
				   ColorType selectedColor, int16_t maxWidth, int16_t maxHeight,
				   ConsoleManager *cm, InputManager *im, SelectableObject *&selected) :
	SelectableObject { x, y, Align::Center, Align::Center,
					   backgroundColor, backgroundColor, maxWidth, maxHeight,
					   selectedColor, selectedColor, cm, im, selected		 },
	m_checkColor	 { checkColor											 },
	m_checked		 { false												 }
{
	m_function = [this]() {m_checked = !m_checked; };
}

CheckBox::CheckBox(ColorType backgroundColor, ColorType checkColor,
				   ColorType selectedColor, int16_t maxWidth, int16_t maxHeight,
				   ConsoleManager *cm, InputManager *im, SelectableObject *&selected) :
	SelectableObject { Align::Center, Align::Center,
					   backgroundColor, backgroundColor, maxWidth, maxHeight,
					   selectedColor, selectedColor, cm, im, selected		 },
	m_checkColor	 { checkColor											 },
	m_checked		 { false												 }
{
	m_function = [this]() {m_checked = !m_checked; };
}

void CheckBox::Draw()
{
	if (!m_active)
		return;

	SetColor();

	DrawBackground();

	DrawContents();
}

void CheckBox::CheckInput()
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

void CheckBox::SetHoverColors(ColorType background, ColorType text)
{
	m_hoverBackgroundColor = m_hoverTextColor = background;
}

bool CheckBox::IsChecked()
{
	return m_checked;
}

void CheckBox::DrawContents()
{
	if (m_checked)
	{
		m_cm->SetColor(m_checkColor, m_checkColor);

		String s((m_width - 4) * (m_height - 2), ' ');
		COORD startPos{ m_upLeftCorner };
		startPos.X += 2;
		++startPos.Y;
		m_cm->Write(s, startPos.X, startPos.Y, m_width - 4, m_height - 2,
					Align::Center, Align::Center);
	}
}
