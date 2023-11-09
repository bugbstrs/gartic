module ConsoleManager;

import <string>;
import <iostream>;
import <Windows.h>;
import ColorType;

HANDLE ConsoleManager::m_h;
uint16_t ConsoleManager::m_color;

void ConsoleManager::Initialize()
{
	m_h = GetStdHandle(STD_OUTPUT_HANDLE);
	m_color = 15;
}

void ConsoleManager::ClearScreen()
{
	SetColor(ColorType::Black, ColorType::White);
	system("cls");
}

void ConsoleManager::SetConsoleScale(uint16_t x, uint16_t y)
{
	String command = "mode " + std::to_string(x) + ',' + std::to_string(y);
	system(command.c_str());
}

void ConsoleManager::SetCursor(uint16_t x, uint16_t y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(m_h, coord);
}

void ConsoleManager::SetBackgroundColor(ColorType color)
{
	m_color %= 16;
	m_color += 16 * (int)color;
	SetConsoleTextAttribute(m_h, m_color);
}

void ConsoleManager::SetTextColor(ColorType color)
{
	m_color = m_color / 16 * 16;
	m_color += (int)color;
	SetConsoleTextAttribute(m_h, m_color);
}

void ConsoleManager::SetColor(ColorType background, ColorType text)
{
	m_color = 16 * (int)background + (int)text;
	SetConsoleTextAttribute(m_h, m_color);
}

void ConsoleManager::WriteVertical(const String& sentence, uint16_t x, uint16_t y)
{
	for (int index = y - sentence.length() / 2; index <= y + (sentence.length() + 1) / 2; index++)
	{
		SetCursor(x, index);
		std::cout << sentence[index - y + sentence.length() / 2];
	}
}

void ConsoleManager::WriteHorizontal(const String& sentence, uint16_t x, uint16_t y)
{
	SetCursor(x - sentence.length() / 2, y);
	std::cout << sentence;
}