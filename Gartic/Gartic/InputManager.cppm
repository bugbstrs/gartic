export module InputManager;

import <Windows.h>;
import <string>;

export import ControlKeys;

using String = std::string;

export class InputManager
{
public:
	// Read
	static void ReadInput();
	static void UpdateString(String& text, int pos = -1, int maxLenght = -1);

	// Getters
	static char GetCurrentKeyboardInput();
	static COORD GetCurrentCursorPosition();
	static ControlKeys ControlKey();
	static bool ClickPressed();

private:
	static char m_lastKeyPressed;

	static bool m_isArrowKey;
	static bool m_rightClickPressed;
	
	static COORD m_cursorPosition;

	static bool IsCursorInConsole();
	
	static COORD CursorPositionInConsole();
};
