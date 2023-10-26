#include <string>

#include "ConsoleManager.h"

HANDLE ConsoleManager::m_h;
int ConsoleManager::m_color;

void ConsoleManager::Initialize()
{
	m_h = GetStdHandle(STD_OUTPUT_HANDLE);
	m_color = 15;
}

void ConsoleManager::SetConsoleScale(int x, int y)
{
	std::string command = "mode " + std::to_string(x) + ',' + std::to_string(y);
	system(command.c_str());
}

void ConsoleManager::GoToXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(m_h, coord);
}

void ConsoleManager::SetBackgroundColor(ColorType color)
{
	m_color %= 16;
	m_color += 16 * color;
}

void ConsoleManager::SetTextColor(ColorType color)
{
	m_color = m_color / 16 * 16;
	m_color += color;
}

void ConsoleManager::SetColor(ColorType background, ColorType text)
{
	m_color = 16 * background + text;
}
