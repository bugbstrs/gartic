module ConsoleManager;

import <print>;
import <string>;
import <vector>;
import <format>;
import <iostream>;
import <Windows.h>;

import ColorType;

using Words = std::vector<std::string>;

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

Words SplitSentenceIntoWords(const String &sentence)
{
	Words words;
	String word;
	int i = 0;

	while (i < sentence.size())
	{
		if (sentence[i] == ' ')
		{
			words.push_back(word);
			word.clear();
		} else
			word.push_back(sentence[i]);
		++i;
	}
	if (!word.empty())
		words.push_back(word);

	return words;
}

void ConsoleManager::Write(const String &sentence, int16_t x, int16_t y, int16_t width,
						   int16_t height, Align horizontal, Align vertical)
{
	Words words = SplitSentenceIntoWords(sentence);
	Words lines;

	String line;

	for (const String &word : words)
	{
		if (line.size() + word.size() + 1 > width) // next word doesn't fit into the line.
		{
			lines.push_back(line);
			line.clear();
			line = word;
		} else
		{
			if (!line.empty())
			{
				line.append(" ");
			}
			line.append(word);
		}
	}

	for (int i = lines.size(); i > height; --i)
		lines.pop_back();

	switch (vertical)
	{
		case Align::Up:
			break;
		case Align::Center:
			y = (y + height) / 2 - lines.size() / 2;
			break;
		case Align::Down:
			y = y + height - lines.size();
			break;
		default:
			break;
	}

	for (const String &line : lines)
	{
		switch (horizontal)
		{
			case Align::Left:
				m_buffers[m_bufferIndex].Write(sentence, x, y);
				break;
			case Align::Center:
				m_buffers[m_bufferIndex].Write(sentence, (x + width) / 2 - sentence.size() / 2, y);
				break;
			case Align::Right:
				m_buffers[m_bufferIndex].Write(sentence, x + width - sentence.size(), y);
				break;
			default:
				break;
		}
	}
}

void ConsoleManager::Write(const WString &sentence, int16_t x, int16_t y, int16_t width,
						   int16_t height, Align horizontal, Align vertical)
{

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
