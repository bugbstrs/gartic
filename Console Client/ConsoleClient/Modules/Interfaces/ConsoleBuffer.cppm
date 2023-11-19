export module ConsoleBuffer;

export import <iostream>;
export import <string>;
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
	void SetBackgroundColor (ColorType color);
	void SetColor			(ColorType background, ColorType text);
	void SetTextColor		(ColorType color);

	// Output related
	void Clear();
	void Write(const String& sentence, int16_t x, int16_t y);

private:
	COORD	   m_bufferSize;
	HANDLE	   m_buffer;
	int16_t    m_height;
	int16_t	   m_width;
	PCHAR_INFO m_charInfoBuffer;
	SMALL_RECT m_writeRect;
	uint16_t   m_color;
};