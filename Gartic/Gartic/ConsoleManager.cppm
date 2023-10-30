export module ConsoleManager;

import <string>;
import <iostream>;
import <Windows.h>;

export import ColorType;

export class ConsoleManager
{
public:
	static void Initialize();
	static void ClearScreen();
	static void SetConsoleScale(uint16_t x, uint16_t y);
	static void SetCursor(uint16_t x, uint16_t y);
	static void SetBackgroundColor(ColorType color);
	static void SetTextColor(ColorType color);
	static void SetColor(ColorType background, ColorType text);
	static void WriteVertical(const std::string& sentence, uint16_t x, uint16_t y);
	static void WriteHorizontal(const std::string& sentence, uint16_t x, uint16_t y);
private:
	static HANDLE m_h;
	static uint16_t m_color;
};