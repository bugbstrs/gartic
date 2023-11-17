export module ConsoleBuffer;

export import <string>;
export import <iostream>;
export import <Windows.h>;

import ColorType;

using String = std::string;

export class ConsoleBuffer
{
public:
	// Constructors
	ConsoleBuffer();

	// Destructor
	~ConsoleBuffer();

	void Clear();
	void Write(const String& sentence, uint16_t x, uint16_t y);
	void SetConsoleScale(uint16_t x, uint16_t y);
	void SetColor(ColorType background, ColorType text);
	void SetTextColor(ColorType color);
	void SetBackgroundColor(ColorType color);
private:
	HANDLE m_h;
	uint16_t m_color;
	uint16_t m_width;
	uint16_t m_height;
	COORD m_bufferSize;
	SMALL_RECT m_writeRect;
	PCHAR_INFO m_infoBuffer;
};