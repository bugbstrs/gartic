#include "ConsoleManager.h"

HANDLE ConsoleManager::m_h;
int ConsoleManager::m_color;

void ConsoleManager::Initialize()
{
	m_h = GetStdHandle(STD_OUTPUT_HANDLE);
	m_color = 15;
}

void ConsoleManager::ClearScreen()
{
	SetColor(Black, White);
	system("cls");
}

void ConsoleManager::SetConsoleScale(int x, int y)
{
	std::string command = "mode " + std::to_string(x) + ',' + std::to_string(y);
	system(command.c_str());
}

void ConsoleManager::SetCursor(int x, int y)
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
	SetConsoleTextAttribute(m_h, m_color);
}

void ConsoleManager::SetTextColor(ColorType color)
{
	m_color = m_color / 16 * 16;
	m_color += color;
	SetConsoleTextAttribute(m_h, m_color);
}

void ConsoleManager::SetColor(ColorType background, ColorType text)
{
	m_color = 16 * background + text;
	SetConsoleTextAttribute(m_h, m_color);
}

void ConsoleManager::WriteVertical(const std::string &sentence, int x, int y)
{
	for (int index = y - sentence.length() / 2; index <= y + (sentence.length() + 1) / 2; index++)
	{
		SetCursor(x, index);
		std::cout << sentence[index - y + sentence.length() / 2];
	}
}

void ConsoleManager::WriteHorizontal(const std::string &sentence, int x, int y)
{
	SetCursor(x - sentence.length() / 2, y);
	std::cout << sentence;
}
