#pragma once
import <string>;
import <iostream>;
import <Windows.h>;

#include "ColorType.h"

class ConsoleManager
{
public:
	static void Initialize();
	static void ClearScreen();
	static void SetConsoleScale(int x, int y);
	static void SetCursor(int x, int y);
	static void SetBackgroundColor(ColorType color);
	static void SetTextColor(ColorType color);
	static void SetColor(ColorType background, ColorType text);
	static void WriteVertical(const std::string& sentence, int x, int y);
	static void WriteHorizontal(const std::string& sentence, int x, int y);
private:
	static HANDLE m_h;
	static int m_color;
};