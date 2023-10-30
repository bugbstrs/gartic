export module InputManager;

import <Windows.h>;
import <string>;

export class InputManager
{
public:
	static void UpdateString(std::string& text, int maxLenght = -1);
	static char GetCurrentKeyboardInput();
	static bool ClickPressed();
	static COORD GetCurrentCursorPosition();
	static void ReadInput();
private:
	static char m_lastKeyPressed;
	static bool m_isArrowKey;
	static bool m_rightClickPressed;
	static COORD m_cursorPosition;

	static bool IsCursorInConsole();
	static COORD CursorPositionInConsole();
};
