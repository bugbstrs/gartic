module InputManager;

char InputManager::m_lastKeyPressed;
bool InputManager::m_isArrowKey;
bool InputManager::m_rightClickPressed;
COORD InputManager::m_cursorPosition;

void InputManager::UpdateString(std::string& text, int maxLenght)
{
	if (m_isArrowKey)
		return;
	if (isalnum(m_lastKeyPressed) || m_lastKeyPressed == ' ')
		if (maxLenght == -1 || text.length() < maxLenght)
			text += m_lastKeyPressed;
	if (m_lastKeyPressed == '\b' && text.length() > 0)//backspace
		text.pop_back();
}

ControlKeys InputManager::ControlKey()
{
	switch (m_lastKeyPressed)
	{
	case Enter:
		return Enter;
	case UpArrow:
		if (m_isArrowKey)
			return UpArrow;
	case DownArrow:
		if (m_isArrowKey)
			return DownArrow;
	case LeftArrow:
		if (m_isArrowKey)
			return LeftArrow;
	case RightArrow:
		if (m_isArrowKey)
			return RightArrow;
	default:
		return NotControl;
	};
}