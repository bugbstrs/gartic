module InputManager;

import <winuser.rh>;
import <conio.h>;
import <cctype>;

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

char InputManager::GetCurrentKeyboardInput()
{
	return m_lastKeyPressed;
}

bool InputManager::ClickPressed()
{
	return m_rightClickPressed;
}

COORD InputManager::GetCurrentCursorPosition()
{
	return m_cursorPosition;
}

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