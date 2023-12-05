export module InputManager;

import <string>;
import <Windows.h>;

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
    void ReadInput    ();
    void UpdateString (String& text, int pos = -1, int maxLength = -1);

    // Getters
    bool        GetClickPressed();
    char        GetCurrentKeyboardInput();
    ControlKeys ControlKey();
    COORD       GetCurrentCursorPosition();

private:
    bool m_isArrowKey;
    bool m_ClickPressed;
    char m_lastKeyPressed;

    bool  IsCursorInConsole();
    COORD CursorPositionInConsole();
    COORD GetFontSize();
    COORD m_cursorPosition;
};
