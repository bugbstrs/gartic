module ConsoleManager;

import <string>;
import <iostream>;
import <Windows.h>;
import <print>;
import <format>;

import ColorType;

ConsoleManager::ConsoleManager()
{
	m_h = GetStdHandle(STD_OUTPUT_HANDLE);
	m_color = 15;
}

void ConsoleManager::SetConsoleScale(uint16_t x, uint16_t y)
{
	String command = std::format("mode {},{}", std::to_string(x), std::to_string(y));
	system(command.c_str());
}

void ConsoleManager::SetCursor(uint16_t x, uint16_t y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(m_h, coord);
}

void ConsoleManager::SetCursor(COORD coord)
{
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

void ConsoleManager::ClearScreen()
{
	SetColor(ColorType::Black, ColorType::White);
	system("cls");
}

void ConsoleManager::WriteVertical(const String& sentence, uint16_t x, uint16_t y)
{
	for (size_t index = y - sentence.length() / 2; index <= y + (sentence.length() + 1) / 2; index++)
	{
		SetCursor(x, index);
		std::print("{}", sentence[index - y + sentence.length() / 2]);
	}
}

void ConsoleManager::WriteHorizontal(const String& sentence, uint16_t x, uint16_t y)
{
	SetCursor(x - sentence.length() / 2, y);
	std::print("{}", sentence);
}