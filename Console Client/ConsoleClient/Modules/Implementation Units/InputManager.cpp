module InputManager;

import <cctype>;
import <conio.h>;
import <Windows.h>;
import <winuser.rh>;

import ControlKeys;

void InputManager::ReadInput()
{
    if (IsCursorInConsole())
    {
        m_cursorPosition     = CursorPositionInConsole();
        m_clickHold          = GetAsyncKeyState(VK_RBUTTON) || GetAsyncKeyState(VK_LBUTTON);
        m_clickPressed       = m_previousClickState && !m_clickHold;
        m_previousClickState = m_clickHold;
    }
    else
    {
        m_cursorPosition    = { -1, -1 };
        m_clickPressed      = false;
        m_clickHold         = false;
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
        m_isArrowKey     = true;
        m_lastKeyPressed = _getch();
    }
}

void InputManager::UpdateString(String& text, int pos, int maxLength)
{
    if (m_isArrowKey) return;
    
    if (pos == -1) pos = text.size();

    if (m_lastKeyPressed == '\b' && pos > 0) // backspace
    {
        text.erase(pos - 1, 1);
    }

    if (m_lastKeyPressed >= 32 && m_lastKeyPressed <= 126)
    {
        if (maxLength == -1 || text.size() < maxLength)
            text.insert(pos, 1, m_lastKeyPressed);
    }
}

bool InputManager::GetClickHold()
{
    return m_clickHold;
}

bool InputManager::GetClickPressed()
{
    return m_clickPressed;
}

char InputManager::GetCurrentKeyboardInput()
{
    return m_lastKeyPressed;
}

ControlKeys InputManager::ControlKey()
{
    switch (m_lastKeyPressed)
    {
    case (int) ControlKeys::Enter:
        return ControlKeys::Enter;
    case (int) ControlKeys::UpArrow:
        if (m_isArrowKey)
            return ControlKeys::UpArrow;
    case (int) ControlKeys::DownArrow:
        if (m_isArrowKey)
            return ControlKeys::DownArrow;
    case (int) ControlKeys::LeftArrow:
        if (m_isArrowKey)
            return ControlKeys::LeftArrow;
    case (int) ControlKeys::RightArrow:
        if (m_isArrowKey)
            return ControlKeys::RightArrow;
    default:
        return ControlKeys::NotControl;
    };
}

COORD InputManager::GetCurrentCursorPosition()
{
    return m_cursorPosition;
}

bool InputManager::IsCursorInConsole()
{
    HWND  foregroundWindow = GetForegroundWindow();
    HWND  consoleWindow    = GetConsoleWindow();
    RECT  consoleRect;
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
    HWND  consoleWindow = GetConsoleWindow();
    POINT cursorPos;
    COORD coord;
    
    GetCursorPos(&cursorPos);
    ScreenToClient(consoleWindow, &cursorPos);
    
    COORD font{ GetFontSize() };

    coord.X = cursorPos.x / font.X;
    coord.Y = cursorPos.y / font.Y;
    
    return coord;
}

COORD InputManager::GetFontSize()
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    return cfi.dwFontSize;
}
