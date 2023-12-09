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
	DWORD mode;
	GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), mode);
}

void ConsoleManager::SetConsoleFont(const WString fontName, int16_t width, int16_t height)
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = width;
	cfi.dwFontSize.Y = height;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, fontName.c_str());
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
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

void ConsoleManager::SetFullscreen()
{
	SetWindowLong(GetConsoleWindow(), GWL_STYLE, GetWindowLong(GetConsoleWindow(), GWL_STYLE) & ~WS_OVERLAPPEDWINDOW);
	ShowWindow(GetConsoleWindow(), SW_SHOWMAXIMIZED);
}

void ConsoleManager::SetWindowed()
{
	SetWindowLong(GetConsoleWindow(), GWL_STYLE, GetWindowLong(GetConsoleWindow(), GWL_STYLE) | WS_OVERLAPPEDWINDOW);
	ShowWindow(GetConsoleWindow(), SW_SHOWNORMAL);
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
			if (word.empty())
				word.push_back(' ');
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

std::vector<WString> SplitSentenceIntoWords(const WString& sentence)
{
	std::vector<WString> words;
	WString word;
	int i = 0;

	while (i < sentence.size())
	{
		if (sentence[i] == ' ')
		{
			words.push_back(word);
			word.clear();
		}
		else
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
		if (line.size() + word.size() <= width)
		{
			if (!line.empty() && line.back() != ' ')
				line.push_back(' ');

			line.append(word);
		} else
		if (word.size() > width) // The word is bigger than the width
		{
			if (!line.empty())
			{
				lines.push_back(line);
				line.clear();
			}

			int i{ 0 };
			while (i < word.size())
			{
				line.push_back(word[i]);

				++i;
				if (i % width == 0)
				{
					lines.push_back(line);
					line.clear();
				}
			}
		} else // The line is full
		{
			lines.push_back(line);
			line.clear();
			line = word;
		}
	}
	if (!line.empty())
		lines.push_back(line);

	for (int i = lines.size(); i > height; --i)
		lines.pop_back();

	switch (vertical)
	{
		case Align::Up:
			break;
		case Align::Center:
			y = y + height / 2 - lines.size() / 2;
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
				m_buffers[m_bufferIndex].Write(line, x, y);
				break;
			case Align::Center:
				m_buffers[m_bufferIndex].Write(line, x + width / 2 - line.size() / 2, y);
				break;
			case Align::Right:
				m_buffers[m_bufferIndex].Write(line, x + width - line.size(), y);
				break;
			default:
				break;
		}
		++y;
	}
}

void ConsoleManager::Write(const WString &sentence, int16_t x, int16_t y, int16_t width,
						   int16_t height, Align horizontal, Align vertical)
{
	std::vector<WString> words = SplitSentenceIntoWords(sentence);
	std::vector<WString> lines;

	WString line;

	for (const WString& word : words)
	{
		if (line.size() + word.size() < width)
		{
			if (!line.empty())
				line.push_back(' ');

			line.append(word);
		}
		else
			if (word.size() > width) // The word is bigger than the width
			{
				if (!line.empty())
				{
					lines.push_back(line);
					line.clear();
				}

				int i{ 0 };
				while (i < word.size())
				{
					line.push_back(word[i]);

					++i;
					if (i % width == 0)
					{
						lines.push_back(line);
						line.clear();
					}
				}
			}
			else // The line is full
			{
				lines.push_back(line);
				line.clear();
				line = word;
			}
	}
	if (!line.empty())
		lines.push_back(line);

	for (int i = lines.size(); i > height; --i)
		lines.pop_back();

	switch (vertical)
	{
	case Align::Up:
		break;
	case Align::Center:
		y = y + height / 2 - lines.size() / 2;
		break;
	case Align::Down:
		y = y + height - lines.size();
		break;
	default:
		break;
	}

	for (const WString& line : lines)
	{
		switch (horizontal)
		{
		case Align::Left:
			m_buffers[m_bufferIndex].Write(line, x, y);
			break;
		case Align::Center:
			m_buffers[m_bufferIndex].Write(line, x + width / 2 - line.size() / 2, y);
			break;
		case Align::Right:
			m_buffers[m_bufferIndex].Write(line, x + width - line.size(), y);
			break;
		default:
			break;
		}
		++y;
	}
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
