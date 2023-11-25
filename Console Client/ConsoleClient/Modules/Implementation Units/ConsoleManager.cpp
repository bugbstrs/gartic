module ConsoleManager;

import <string>;
import <iostream>;
import <Windows.h>;
import <print>;
import <format>;

import ColorType;

ConsoleManager::ConsoleManager()
{
	m_buffers = nullptr;
	m_bufferIndex = 0;
}

ConsoleManager::~ConsoleManager()
{
	if (m_buffers)
		delete[] m_buffers;
}

void ConsoleManager::NewConsole(const LPCWSTR title, int16_t width, int16_t height)
{
	if (m_buffers)
		delete[] m_buffers;

	m_bufferIndex = 0;
	m_buffers = new ConsoleBuffer[2]{
		ConsoleBuffer{ width,height },
		ConsoleBuffer{ width,height }
	};

	SetConsoleTitle(title);
}

void ConsoleManager::SetTextColor(ColorType color)
{
	m_buffers[m_bufferIndex].SetTextColor(color);
}

void ConsoleManager::SetBackgroundColor(ColorType color)
{
	m_buffers[m_bufferIndex].SetBackgroundColor(color);
}

void ConsoleManager::SetColor(ColorType background, ColorType text)
{
	m_buffers[m_bufferIndex].SetColor(background, text);
}

void ConsoleManager::SetCursor(bool visible, COORD coord)
{
	m_buffers[m_bufferIndex].SetCursor(visible, coord);
}

void ConsoleManager::SetCursor(bool visible, int16_t x, int16_t y)
{
	m_buffers[m_bufferIndex].SetCursor(visible, { x,y });
}

void ConsoleManager::WriteHorizontal(const String& sentence, int16_t x, int16_t y)
{
	m_buffers[m_bufferIndex].Write(sentence, x, y);
}

void ConsoleManager::WriteHorizontal(const WString& sentence, int16_t x, int16_t y)
{
	m_buffers[m_bufferIndex].Write(sentence, x, y);
}

void ConsoleManager::WriteVertical(const String& sentence, int16_t x, int16_t y)
{
	for (size_t index{ 0 }; index < sentence.size(); ++index)
		m_buffers[m_bufferIndex].Write(sentence[index], x, y + index);
}

void ConsoleManager::WriteVertical(const WString& sentence, int16_t x, int16_t y)
{
	for (size_t index{ 0 }; index < sentence.size(); ++index)
		m_buffers[m_bufferIndex].Write(sentence[index], x, y + index);
}

void ConsoleManager::Write(const char c, int16_t x, int16_t y)
{
	m_buffers[m_bufferIndex].Write(c, x, y);
}

void ConsoleManager::Write(const wchar_t c, int16_t x, int16_t y)
{
	m_buffers[m_bufferIndex].Write(c, x, y);
}

void ConsoleManager::UpdateConsole()
{
	m_buffers[m_bufferIndex].WriteBufferToConsole();
	m_bufferIndex = !m_bufferIndex;
	ClearBuffer();
}

void ConsoleManager::ClearBuffer()
{
	m_buffers[m_bufferIndex].Clear();
}
