#include <Windows.h>

#include "ColorType.h"

#pragma once
class ConsoleManager
{
public:
	static void Initialize();
	static void SetConsoleScale(int x, int y);
	static void GoToXY(int x, int y);
	static void SetBackgroundColor(ColorType color);
	static void SetTextColor(ColorType color);
	static void SetColor(ColorType background, ColorType text);
private:
	static HANDLE m_h;
	static int m_color;
};
