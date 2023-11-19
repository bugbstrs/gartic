export module InputManager;

import <Windows.h>;
import <string>;

export import ControlKeys;

using String = std::string;

export class InputManager
{
public:
	// Constructors
	InputManager() = default;

	// Destructor
	~InputManager() = default;

	// Read
	void ReadInput();
	void UpdateString(String& text, int pos = -1, int maxLenght = -1);

	// Getters
	ControlKeys ControlKey();
	bool GetClickPressed();
	char GetCurrentKeyboardInput();
	COORD GetCurrentCursorPosition();

private:
	char m_lastKeyPressed;

	bool m_isArrowKey;
	bool m_rightClickPressed;
	
	COORD m_cursorPosition;

	bool IsCursorInConsole();
	
	COORD CursorPositionInConsole();
};
