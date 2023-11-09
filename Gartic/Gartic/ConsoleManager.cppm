export module ConsoleManager;

import <string>;
import <iostream>;
import <Windows.h>;

export import ColorType;

using String = std::string;

export class ConsoleManager
{
public:
	// Console creation
	static void Initialize();

	// Setters
	static void SetConsoleScale(uint16_t x, uint16_t y);
	static void SetCursor(uint16_t x, uint16_t y);
	static void SetBackgroundColor(ColorType color);
	static void SetTextColor(ColorType color);
	static void SetColor(ColorType background, ColorType text);
	
	// Output related
	static void ClearScreen();
	static void WriteVertical(const String& sentence, uint16_t x, uint16_t y);
	static void WriteHorizontal(const String& sentence, uint16_t x, uint16_t y);

private:
	static HANDLE m_h;

	static uint16_t m_color;
};