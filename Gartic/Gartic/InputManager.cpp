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
	if (m_lastKeyPressed == 224 || m_lastKeyPressed == -32)//224/-32 is right before arrow keys keycode
	{
		m_isArrowKey = true;
		m_lastKeyPressed = _getch();
	}
}


void InputManager::UpdateString(String& text, int maxLenght)
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
	GetClientRect(consoleWindow, &consoleRect);
	POINT cursorPos;
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
	GetCursorPos(&cursorPos);
	ScreenToClient(consoleWindow, &cursorPos);
	COORD coord;
	coord.X = cursorPos.x / 8;
	coord.Y = cursorPos.y / 16;
	return coord;
}