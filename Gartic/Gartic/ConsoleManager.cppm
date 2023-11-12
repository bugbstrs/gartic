export module ConsoleManager;

import <string>;
import <iostream>;
import <Windows.h>;

export import ColorType;

using String = std::string;

export class ConsoleManager
{
public:
	// Constructors
	ConsoleManager();

	// Destructors
	~ConsoleManager();

	// Setters
	void SetConsoleScale(uint16_t x, uint16_t y);
	void SetCursor(uint16_t x, uint16_t y);
	void SetCursor(COORD coord);
	void SetBackgroundColor(ColorType color);
	void SetTextColor(ColorType color);
	void SetColor(ColorType background, ColorType text);
	
	// Output related
	void ClearScreen();
	void WriteVertical(const String& sentence, uint16_t x, uint16_t y);
	void WriteHorizontal(const String& sentence, uint16_t x, uint16_t y);

private:
	HANDLE m_h;
	uint16_t m_color;
};