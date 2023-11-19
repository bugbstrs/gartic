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
	ConsoleBuffer(int16_t width, int16_t height);

	// Destructor
	~ConsoleBuffer();

	// Setters
	void SetColor(ColorType background, ColorType text);
	void SetTextColor(ColorType color);
	void SetBackgroundColor(ColorType color);

	// Output related
	void Clear();
	void Write(const String& sentence, int16_t x, int16_t y);

private:
	HANDLE m_buffer;
	uint16_t m_color;
	int16_t m_width;
	int16_t m_height;
	COORD m_bufferSize;
	SMALL_RECT m_writeRect;
	PCHAR_INFO m_charInfoBuffer;
};