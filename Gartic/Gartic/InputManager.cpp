module InputManager;

import <winuser.rh>;
import <conio.h>;
import <cctype>;

import ControlKeys;

char InputManager::m_lastKeyPressed;
bool InputManager::m_isArrowKey;
bool InputManager::m_rightClickPressed;
COORD InputManager::m_cursorPosition;

void InputManager::ReadInput()
{
	if (IsCursorInConsole())
	{
		m_cursorPosition = CursorPositionInConsole();
		m_rightClickPressed = GetAsyncKeyState(VK_RBUTTON);
	}
	else
	{
		m_cursorPosition = { -1, -1 };
		m_rightClickPressed = false;
	}

	m_isArrowKey = false;
	
	if (!_kbhit())
	{
		m_lastKeyPressed = 0;
		return;
	}

	m_lastKeyPressed = _getch();
	
	if (m_lastKeyPressed == 224 || m_lastKeyPressed == -32) // 224/-32 is right before arrow keys keycode
	{
		m_isArrowKey = true;
		m_lastKeyPressed = _getch();
	}
}


void InputManager::UpdateString(String& text, int pos, int maxLength)
{
	if (m_isArrowKey)
		return;
	if (pos == -1)
		pos = text.size();
	if (m_lastKeyPressed == '\b' && text.size() > 0) // backspace
		if (pos == text.size())
			text.erase(pos - 1, 1);
		else
			text.erase(pos, 1);
	if (m_lastKeyPressed >= 32 && m_lastKeyPressed <= 126)
		if (maxLength == -1 || text.size() < maxLength)
			text.insert(pos, 1, m_lastKeyPressed);
}

ControlKeys InputManager::ControlKey()
{
	switch (m_lastKeyPressed)
	{
	case (int)ControlKeys::Enter:
		return ControlKeys::Enter;
	case (int)ControlKeys::UpArrow:
		if (m_isArrowKey)
			return ControlKeys::UpArrow;
	case (int)ControlKeys::DownArrow:
		if (m_isArrowKey)
			return ControlKeys::DownArrow;
	case (int)ControlKeys::LeftArrow:
		if (m_isArrowKey)
			return ControlKeys::LeftArrow;
	case (int)ControlKeys::RightArrow:
		if (m_isArrowKey)
			return ControlKeys::RightArrow;
	default:
		return ControlKeys::NotControl;
	};
}

bool InputManager::ClickPressed()
{
	return m_rightClickPressed;
}

char InputManager::GetCurrentKeyboardInput()
{
	return m_lastKeyPressed;
}

COORD InputManager::GetCurrentCursorPosition()
{
	return m_cursorPosition;
}

bool InputManager::IsCursorInConsole()
{
	HWND foregroundWindow = GetForegroundWindow();
	HWND consoleWindow = GetConsoleWindow();
	RECT consoleRect;
	POINT cursorPos;

	GetClientRect(consoleWindow, &consoleRect);
	GetCursorPos(&cursorPos);
	ScreenToClient(consoleWindow, &cursorPos);
	
	if (PtInRect(&consoleRect, cursorPos))
		if (foregroundWindow == consoleWindow)
			return true;
	
	return false;
}

COORD InputManager::CursorPositionInConsole()
{
	HWND consoleWindow = GetConsoleWindow();
	POINT cursorPos;
	COORD coord;
	
	GetCursorPos(&cursorPos);
	ScreenToClient(consoleWindow, &cursorPos);
	coord.X = cursorPos.x / 8;
	coord.Y = cursorPos.y / 16;
	
	return coord;
}